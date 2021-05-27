#include <stdio.h>
#include <stdlib.h>

#include "ot_tcp_client.h"



int main(int argc, char *argv[]) {
    ot_tcp_client_t *test = ot_tcp_client_create();
    ot_tcp_client_init(test);
    ot_tcp_client_loop(test);
    ot_tcp_client_destroy(test);

    // test command list
    // f_login
    // f_login_accept
    // f_login_reject
    // f_get_user_information
    // f_send_bank_and_balanced

    //ot_tcp_client_loop(test);


}