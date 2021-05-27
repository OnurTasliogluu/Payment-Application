#ifndef OT_TCP_CLIENT_H
#define OT_TCP_CLIENT_H

#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h>
#include <stdint.h>

#include "ot_common.h"

#define PORT 1234

typedef struct {
    int32_t sock_fd;
    uint8_t hostname[NORMAL_STRING_SIZE];
    int32_t session_id;
} ot_tcp_client_t;

typedef enum {
    LOGIN,
    LOGIN_ACCEPT,
    LOGIN_REJECT,
    GET_USER_INFORMATION,
    SEND_BANK_and_BALANCED,
    EXIT
} ot_payment_protocol_e;

ot_tcp_client_t *ot_tcp_client_create();
void ot_tcp_client_init(ot_tcp_client_t *this);
void ot_tcp_client_deinit(ot_tcp_client_t *this);
void ot_tcp_client_destroy(ot_tcp_client_t *this);
void ot_tcp_client_loop(ot_tcp_client_t *this);
void ot_tcp_client_test();

#endif