#ifndef OT_USER_INFORMATION_H
#define OT_USER_INFORMATION_H

#include "ot_common.h"

typedef struct {
    uint8_t bank_name[NORMAL_STRING_SIZE];
    uint32_t balance;
} ot_user_bank_information_t;

typedef struct {
    uint8_t username[NORMAL_STRING_SIZE];
    uint8_t surname[NORMAL_STRING_SIZE];
    uint8_t password[NORMAL_STRING_SIZE];
    uint8_t account_id[NORMAL_STRING_SIZE];
    ot_user_bank_information_t bank_informations[16];
} ot_user_information_t;


ot_user_information_t *ot_user_information_create();
void ot_user_information_init(ot_user_information_t *this);
void ot_user_information_display_users(void *user);
int ot_user_information_compare_users(void *user_1, void *user_2);
int ot_user_information_hash_key_calculater(ot_user_information_t *this);
void ot_user_information_deinit(ot_user_information_t *this);
void ot_user_information_destroy(ot_user_information_t *this);
void ot_user_information_test();

void ot_user_information_set_username(ot_user_information_t *this, uint8_t *username);
uint8_t *ot_user_information_get_username(ot_user_information_t *this);

void ot_user_information_set_surname(ot_user_information_t *this, uint8_t *surname);
uint8_t *ot_user_information_get_surname(ot_user_information_t *this);

void ot_user_information_set_password(ot_user_information_t *this, uint8_t *password);
uint8_t *ot_user_information_get_password(ot_user_information_t *this);

void ot_user_information_set_account_id(ot_user_information_t *this, uint8_t *password);
uint8_t *ot_user_information_get_account_id(ot_user_information_t *this);

void ot_user_bank_information_set_bank_name(ot_user_information_t *this, uint8_t *bank_name, int index);
uint8_t *ot_user_bank_information_get_bank_name(ot_user_information_t *this, int index);

void ot_user_bank_information_set_balance(ot_user_information_t *this, uint32_t balance, int index);
uint32_t ot_user_bank_information_get_balance(ot_user_information_t *this, int index);

#endif
