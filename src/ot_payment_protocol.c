#include "ot_payment_protocol.h"

static void ot_payment_protocol_receive(void *this, void *data);

static void ot_payment_protocol_receive(void *self, void *data) {
    printf("PACKET RECEIVE\n");
    uint8_t *test_data = "NEW HELLO WORLD!";
    ot_tcp_server_t *this = self;
    ot_tcp_server_send_packet(this, (void*)test_data, 15);
    //ot_payment_protocol_data_parser(data);
}

static void ot_payment_protocol_send(void *data) {
    
}

static void f_login(ot_payment_data_t *data) {
    printf("LOGIN");
}

static void f_login_accept(ot_payment_data_t *data) {
    printf("ACCEPT");
}

static void f_login_reject(ot_payment_data_t *data) {
    printf("REJECT");
}

static void f_get_user_information(ot_payment_data_t *data) {
    printf("INFORMATION");
}

static void f_send_bank_and_balanced(ot_payment_data_t *data) {
    printf("BALANCE");
}

static void (*parser_function_list[5])() = {f_login, f_login_accept, f_login_reject, f_get_user_information, f_send_bank_and_balanced};

static void ot_payment_protocol_data_parser(void *data) {
    ot_payment_data_t *p_data = data;
    parser_function_list[p_data->op_code](data);
}

void ot_payment_protocol_data_fill_bank_and_balance(ot_payment_protocol_t* this, void *data) {

}

void ot_payment_protocol_init(ot_payment_protocol_t *this) {
    this->tcp_server = ot_tcp_server_create();
    ot_tcp_server_init(this->tcp_server);
    this->tcp_server->ot_tcp_server_receive_packet = &ot_payment_protocol_receive;
}

void ot_payment_protocol_deinit(ot_payment_protocol_t *this) {

}

void ot_payment_protocol_destroy(ot_payment_protocol_t *this) {
    ot_payment_protocol_deinit(this);
    ot_tcp_server_destroy(this);
    free(this);
}

void ot_payment_protocol_test() {

}

void ot_payment_protocol_loop(ot_payment_protocol_t *this) {
    ot_tcp_server_loop(this->tcp_server);
}

ot_payment_protocol_t *ot_payment_protocol_create(){
    ot_payment_protocol_t *this = malloc(sizeof(ot_payment_protocol_t));

    if(this == NULL) {
        // error log ...
        return NULL;
    }

    return this;
}