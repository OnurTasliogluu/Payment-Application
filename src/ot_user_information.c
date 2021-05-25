#include "ot_user_information.h"

uint8_t *ot_user_information_get_username(ot_user_information_t *this) {
    return this->username;
}

void ot_user_information_set_username(ot_user_information_t *this, uint8_t *username) {

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

void ot_user_information_init(ot_user_information_t *this) {

}

void ot_user_information_deinit(ot_user_information_t *this) {

}

void ot_user_information_destroy(ot_user_information_t *this) {
    ot_user_information_deinit(this);
    free(this);
}

void ot_user_information_test() {

}

ot_user_information_t *ot_user_information_create() {
    ot_user_information_t *this = malloc(sizeof(ot_user_information_t));

    if(this == NULL) {
        // error log ...
        return NULL;
    }

    return this;
}