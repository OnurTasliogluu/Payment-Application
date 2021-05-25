#include <stdio.h>
#include <stdlib.h>

#include "ot_payment_protocol.h"

// thread

int main(int argc, char *argv[]) {
    ot_payment_protocol_t *test = ot_payment_protocol_create();
    ot_payment_protocol_init(test);
    ot_payment_protocol_loop(test);
    return 0;
}