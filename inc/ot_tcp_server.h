#ifndef OT_TCP_SERVER_H
#define OT_TCP_SERVER_H

#include "ot_epoll.h"

#define CLIENT_SIZE 75000

typedef struct {
    ot_epoll_t *ot_epoll;

    int32_t server_socket_descripter;
    int32_t client_size;
    void (*ot_tcp_server_receive_packet)(void*, void*, uint32_t);
    void (*ot_tcp_server_send_packet)(void*, void*, uint32_t);
} ot_tcp_server_t;

typedef enum
{
    TCP_CONNECT,
} ot_tcp_server_e;

ot_tcp_server_t *ot_tcp_server_create();
void ot_tcp_server_init(ot_tcp_server_t *this);
void ot_tcp_server_deinit(ot_tcp_server_t *this);
void ot_tcp_server_destroy(ot_tcp_server_t *this);
void ot_tcp_server_test();

void ot_tcp_server_loop(ot_tcp_server_t* this);

#endif