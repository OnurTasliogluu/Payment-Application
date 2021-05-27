#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define PORT 1234
#define SA struct sockaddr

#include "ot_tcp_server.h"

void ot_tcp_server_send_packet(ot_tcp_server_t* this, void *data, uint32_t size, uint32_t i) {
    int result = write(this->ot_epoll->events[i].data.fd, data, size);
}

void ot_tcp_server_socket_create(ot_tcp_server_t* this)
{
    struct sockaddr_in servaddr;
    this->server_socket_descripter = socket(AF_INET, SOCK_STREAM, 0); 
    if (this->server_socket_descripter == -1)
    { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created..\n"); 
    bzero(&servaddr, sizeof(servaddr)); 
 
    printf("ot_tcp_server_socket_create-3\n");
    // assign IP, PORT 
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    servaddr.sin_port = htons(PORT); 

    printf("ot_tcp_server_socket_create-4\n");
    if ((bind(this->server_socket_descripter, (SA*)&servaddr, sizeof(servaddr))) != 0)
    { 
        printf("socket bind failed...\n"); 
        exit(0); 
    } 
    else
    {
        printf("Socket successfully binded..\n");
    }

    if ((listen(this->server_socket_descripter, 5)) != 0)
    { 
        printf("Listen failed...\n"); 
        exit(0); 
    }
}

void ot_tcp_server_loop(ot_tcp_server_t* this)
{
    printf("ot_tcp_server_loop LOOP\n");
    uint32_t i;
    int32_t result;
    char input[100];
    char data[4096];
    int32_t ret;
    char hello[] = "hello world!\n";
    epoll_event_t ev;
    for (;;)
    {
        ret = epoll_wait(this->ot_epoll->epoll_poll_fd, this->ot_epoll->events, CLIENT_SIZE, -1);
        if (ret < 0)
        {
            continue;
        }

        for (i = 0; i < ret; ++i)
        {
            if ((this->ot_epoll->events[i].events & EPOLLERR) || (this->ot_epoll->events[i].events & EPOLLHUP)
                    || (!this->ot_epoll->events[i].events & EPOLLIN))
            {
                printf("ot_epoll events error!\n");
                close(this->ot_epoll->events[i].data.fd);
                continue;
            }
            else if (this->server_socket_descripter == this->ot_epoll->events[i].data.fd)
            {
                int connfd = -1;
                if (0 > (connfd = accept(this->server_socket_descripter, NULL, NULL)))
                {
                    printf("accpet failed!\n");
                    close(this->server_socket_descripter);
                }
                memset(&ev, 0, sizeof(struct epoll_event));
                ev.data.fd = connfd;
                ev.events = EPOLLIN;
                if (0 != epoll_ctl(this->ot_epoll->epoll_poll_fd, EPOLL_CTL_ADD, connfd, &ev))
                {
                    printf("epoll add connfd error!\n");
                    continue;
                }
            }
            else if (this->ot_epoll->events[i].events & EPOLLIN)
            {
                result = read(this->ot_epoll->events[i].data.fd ,data, sizeof(data));
                data[result] = '\0';
                if(result <= 0)
                {
                    if (0 != epoll_ctl(this->ot_epoll->epoll_poll_fd, EPOLL_CTL_DEL, this->ot_epoll->events[i].data.fd, NULL))
                    {
                        printf("epoll add connfd error[%m]!\n");
                        continue;
                    }
                }
                printf("data=%s\n",data);
                this->ot_tcp_server_receive_packet((void*)this, (void*)data, i);
            }
        }
    }
}

ot_tcp_server_t *ot_tcp_server_create() {
    ot_tcp_server_t *this = malloc(sizeof(ot_tcp_server_t));

    if(this == NULL) {
        // error log ...
        return NULL;
    }

    this->ot_epoll = ot_epoll_create();

    return this;
}

void ot_tcp_server_init(ot_tcp_server_t *this) {
    this->server_socket_descripter = -1;
    this->client_size = CLIENT_SIZE;
    ot_epoll_init(this->ot_epoll, 32);
    ot_tcp_server_socket_create(this);
    epoll_event_t ev;
    memset(&ev, 0, sizeof(struct epoll_event));
    ev.data.fd = this->server_socket_descripter;
    ev.events = EPOLLIN;
    if (0 != epoll_ctl(this->ot_epoll->epoll_poll_fd, EPOLL_CTL_ADD, this->server_socket_descripter, &ev))
    {
        printf("epoll add connfd error!\n");
    }

    this->ot_tcp_server_send_packet = &ot_tcp_server_send_packet;
}

void ot_tcp_server_deinit(ot_tcp_server_t *this) {
    if (this->server_socket_descripter > 0)
    {
        printf("CLOSE\n");
        close(this->server_socket_descripter);
    }
}

void ot_tcp_server_destroy(ot_tcp_server_t *this) {
    ot_tcp_server_deinit(this);
    free(this);
}

void ot_tcp_server_test() {
    ot_tcp_server_t *this = ot_tcp_server_create();
    ot_tcp_server_init(this);
    ot_tcp_server_destroy(this);
}