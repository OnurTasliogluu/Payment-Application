#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ot_client.h"

ot_client_t *ot_client_create() {
    ot_client_t *this = malloc(sizeof(ot_client_t));

    if(this == NULL) {
        // error log ...
        return NULL;
    }

    return this;
}

void ot_client_init(ot_client_t *this) {

}

void ot_client_deinit(ot_client_t *this) {

}

void ot_client_destroy(ot_client_t *this){
    ot_client_deinit(this);
}

void ot_client_test() {
    ot_client_t *this = ot_client_create();
    ot_client_init(this);
    ot_client_destroy(this);
}