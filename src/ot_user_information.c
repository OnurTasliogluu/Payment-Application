#include "ot_user_information.h"

void ot_user_information_set_username(ot_user_information_t *this, uint8_t *username)
{

    if(username != NULL) {
        if(strlen(username) < NORMAL_STRING_SIZE) {
            memcpy(this->username, username, strlen(username));
        }
        else {
            // log: username has big size;
        }
    }
    else {
        // log: username is NULL;
    }

}

uint8_t *ot_user_information_get_username(ot_user_information_t *this)
{
    return this->username;
}

void ot_user_information_set_surname(ot_user_information_t *this, uint8_t *surname)
{

    if(surname != NULL) {
        if(strlen(surname) < NORMAL_STRING_SIZE) {
            memcpy(this->surname, surname, strlen(surname));
        }
        else {
            // log: surname has big size;
        }
    }
    else {
        // log: surname is NULL;
    }

}

uint8_t *ot_user_information_get_surname(ot_user_information_t *this)
{
    return this->surname;
}

void ot_user_information_set_password(ot_user_information_t *this, uint8_t *password)
{

    if(password != NULL) {
        if(strlen(password) < NORMAL_STRING_SIZE) {
            memcpy(this->password, password, strlen(password));
        }
        else {
            // log: password has big size;
        }
    }
    else {
        // log: password is NULL;
    }

}

uint8_t *ot_user_information_get_password(ot_user_information_t *this)
{
    return this->password;
}

void ot_user_information_set_account_id(ot_user_information_t *this, uint8_t *account_id)
{

    if(account_id != NULL) {
        if(strlen(account_id) < NORMAL_STRING_SIZE) {
            memcpy(this->account_id, account_id, strlen(account_id));
        }
        else {
            // log: account_id has big size;
        }
    }
    else {
        // log: account_id is NULL;
    }

}

uint8_t *ot_user_information_get_account_id(ot_user_information_t *this)
{
    return this->account_id;
}

void ot_user_bank_information_set_bank_name(ot_user_information_t *this, uint8_t *bank_name, int index)
{
    if(bank_name != NULL) {
        if(strlen(bank_name) < NORMAL_STRING_SIZE) {
            memcpy(this->bank_informations[index].bank_name, bank_name, strlen(bank_name));
        }
        else {
            // log: bank_informations has big size;
        }
    }
    else {
        // log: bank_informations is NULL;
    }
}

uint8_t *ot_user_bank_information_get_bank_name(ot_user_information_t *this, int index)
{
    return this->bank_informations[index].bank_name;
}

void ot_user_bank_information_set_balance(ot_user_information_t *this, uint32_t balance, int index)
{
    if(balance > 0)
    {
        this->bank_informations[index].balance = balance;
    }
    else {
        // log: balance is negative;
    }
}

uint32_t ot_user_bank_information_get_balance(ot_user_information_t *this, int index)
{
    return this->bank_informations[index].balance;
}

void ot_user_information_init(ot_user_information_t *this)
{
    printf("INIT TEST\n");
    memset(this->username,'\0',sizeof(this->username));
    memset(this->surname,'\0',sizeof(this->surname));
    memset(this->password,'\0',sizeof(this->password));
    memset(this->account_id,'\0',sizeof(this->account_id));
    // this->bank_informations->bank_name
}

int ot_user_information_compare_users(void *user_1, void *user_surname)
{
    printf("USERS COMPARE TEST ! \n");
    if (!strcmp(ot_user_information_get_surname(user_1), user_surname))
    {
        printf("Users Equal\n");
        return 0;
    }
    return -1;
}

int ot_user_information_hash_key_calculater(ot_user_information_t *this)
{
    int key = 0;
    char *surname = ot_user_information_get_surname(this);

    for (size_t i = 0; i < strlen(ot_user_information_get_surname(this)); i++)
    {
        key += surname[i];
    }

    return key;
}


void ot_user_information_deinit(ot_user_information_t *this)
{
    printf("DEINIT TEST\n");
    memset(this->username,'\0',sizeof(this->username));
    memset(this->surname,'\0',sizeof(this->surname));
    memset(this->password,'\0',sizeof(this->password));
    memset(this->account_id,'\0',sizeof(this->account_id));

}

void ot_user_information_destroy(ot_user_information_t *this)
{
    printf("DESTROY TEST\n");
    ot_user_information_deinit(this);
    free(this);
}

void ot_user_information_test()
{
    ot_user_information_t *test = ot_user_information_create();
    ot_user_information_init(test);


    ot_user_information_set_username(test, "Samet");
    printf("Username : %s\n", ot_user_information_get_username(test));

    ot_user_information_set_surname(test, "Tas");
    printf("Surname : %s\n", ot_user_information_get_surname(test));

    ot_user_information_set_password(test, "1234");
    printf("Password : %s\n", ot_user_information_get_password(test));

    ot_user_information_set_account_id(test, "1");
    printf("Account ID : %s\n", ot_user_information_get_account_id(test));

    ot_user_bank_information_set_bank_name(test, "AKBANK", 0);
    printf("Bank Name : %s\n", ot_user_bank_information_get_bank_name(test, 0));

    ot_user_bank_information_set_balance(test, 2, 0);
    printf("Balance : %d\n", ot_user_bank_information_get_balance(test, 0));

    ot_user_information_destroy(test);
}

ot_user_information_t *ot_user_information_create()
{
    ot_user_information_t *this = malloc(sizeof(ot_user_information_t));

    if(this == NULL)
    {
        // error log ...
        return NULL;
    }

    return this;
}
