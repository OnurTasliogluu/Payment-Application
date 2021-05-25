#ifndef OT_PAYMENT_PROTOCOL_H
#define OT_PAYMENT_PROTOCOL_H

#include "ot_common.h"
#include "ot_tcp_server.h"

typedef struct {
    uint32_t op_code;
    uint8_t username[NORMAL_STRING_SIZE];
    uint8_t surname[NORMAL_STRING_SIZE];
    uint8_t password[NORMAL_STRING_SIZE];
    uint8_t user_number[NORMAL_STRING_SIZE];
} ot_payment_data_t;

typedef struct {
    ot_tcp_server_t *tcp_server;
} ot_payment_protocol_t;

typedef enum {
    LOGIN,
    LOGIN_ACCEPT,
    LOGIN_REJECT,
    GET_USER_INFORMATION,
    SEND_BANK_and_BALANCED,
} ot_payment_protocol_e;


ot_payment_protocol_t *ot_payment_protocol_create();
void ot_payment_protocol_init(ot_payment_protocol_t *this);
void ot_payment_protocol_deinit(ot_payment_protocol_t *this);
void ot_payment_protocol_destroy(ot_payment_protocol_t *this);
void ot_payment_protocol_test();

void ot_payment_protocol_data_parser(ot_payment_protocol_t *this, void *data);
void ot_payment_protocol_data_fill_bank_and_balance(ot_payment_protocol_t *this, void *data);
void ot_payment_protocol_loop(ot_payment_protocol_t *this);

#endif