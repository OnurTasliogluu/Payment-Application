#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ot_tcp_client.h"

static void ot_tcp_client_parsing_data(int8_t *data);

typedef struct {
    uint32_t op_code;
    uint8_t username[NORMAL_STRING_SIZE];
    uint8_t surname[NORMAL_STRING_SIZE];
    uint8_t password[NORMAL_STRING_SIZE];
} ot_login_data_t;

typedef struct {
    uint32_t op_code;
    uint8_t bank_name[NORMAL_STRING_SIZE];
    uint8_t balance[NORMAL_STRING_SIZE];
} ot_user_bank_information_t;

static int32_t ot_tcp_client_send(ot_tcp_client_t *this, void *data, uint32_t size) {
    if (send(this->sock_fd, data, size, 0) == -1) {
        printf("error send socket");
        return -1;
    }

    return 0;
}

static int32_t ot_tcp_client_recv(ot_tcp_client_t *this) {
    int8_t data[1024];
    if (recv(this->sock_fd, data, sizeof(data), 0) == -1) {
        printf("error recv socket");
        return -1;
    }
    printf("Received = %s \n", data);
    data[1024] = '\0';
    ot_tcp_client_parsing_data(data);
    return 0;
}

static void ot_tcp_client_parsing_data(int8_t *data) {
    // Login Accept 
    // Login Reject
}

static void f_ot_tcp_client_fill_login_data(ot_tcp_client_t *this) {
    ot_login_data_t login_data;
    login_data.op_code = LOGIN;
    printf("Username: ");
    fgets(login_data.username, sizeof(login_data.username), stdin);
    printf("\n");
    printf("Surname: ");
    fgets(login_data.surname, sizeof(login_data.surname), stdin);
    printf("\n");
    printf("Password: ");
    fgets(login_data.password, sizeof(login_data.password), stdin);
    printf("\n");

    //memcpy(&login_data, data, sizeof(login_data));
    ot_tcp_client_send(this, (void*)&login_data, sizeof(login_data));
}

static void f_ot_tcp_client_fill_get_user_information_data(ot_tcp_client_t *this) {
    int8_t data[1];
    data[0] = GET_USER_INFORMATION;
    ot_tcp_client_send(this, (void*)&data, sizeof(data));
}

static void f_ot_tcp_client_fill_send_money_transfer_between_bank(ot_tcp_client_t *this) {
    int8_t data[1];
    data[0] = SEND_BANK_and_BALANCED;
    ot_tcp_client_send(this, (void*)&data, sizeof(data));
}

static void f_ot_tcp_client_exit_program(ot_tcp_client_t *this) {
    int8_t data[1];
    data[0] = EXIT;
    ot_tcp_client_send(this, (void*)&data, sizeof(data));
}

static void (*command_function_list[4])() = {f_ot_tcp_client_fill_login_data,
                                             f_ot_tcp_client_fill_get_user_information_data,
                                             f_ot_tcp_client_fill_send_money_transfer_between_bank,
                                             f_ot_tcp_client_exit_program};

static int32_t ot_tcp_client_command(ot_tcp_client_t *this) {
    int8_t select[8];

    // get command from user with keyboard
    printf("1: Login\n");
    printf("2: Get Bank Information\n");
    printf("3: Money Transfer Between Bank\n");
    printf("4: Exit\n");
    fgets(select, sizeof(select), stdin);
    int32_t command = strtol(select,NULL,10)-1;
    command_function_list[command](this);

    return command;
}

static int32_t ot_tcp_client_socket_create(ot_tcp_client_t *this) {
    struct hostent *he;
    struct sockaddr_in sock_addr;

    if ((he=gethostbyname(this->hostname)) == NULL) {
        return -1;
    }

    if ((this->sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        return -1;
    }

    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(PORT);
    sock_addr.sin_addr = *((struct in_addr *)he->h_addr);
    bzero(&(sock_addr.sin_zero), 8);

    if (connect(this->sock_fd, (struct sockaddr *)&sock_addr, sizeof(struct sockaddr)) == -1) {
        return -1;
    }
}

void ot_tcp_client_loop(ot_tcp_client_t *this) {
    ot_tcp_client_socket_create(this);
    int32_t result;
    
    for (;;) {
        result = ot_tcp_client_command(this);
        if(result == 4)
            break;
	}
}

ot_tcp_client_t *ot_tcp_client_create() {
    ot_tcp_client_t *this = malloc(sizeof(ot_tcp_client_t));

    if(this == NULL) {
        // error log ...
        return NULL;
    }

    return this;
}

void ot_tcp_client_init(ot_tcp_client_t *this) {
    strcpy(this->hostname, "localhost");
    ot_tcp_client_socket_create(this);
}

void ot_tcp_client_deinit(ot_tcp_client_t *this) {
    close(this->sock_fd);
}

void ot_tcp_client_destroy(ot_tcp_client_t *this){
    ot_tcp_client_deinit(this);
    free(this);
}

void ot_tcp_client_test() {
    ot_tcp_client_t *this = ot_tcp_client_create();
    ot_tcp_client_init(this);
    ot_tcp_client_destroy(this);
}