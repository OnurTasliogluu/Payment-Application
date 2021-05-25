#ifndef OT_CLIENT_H
#define OT_CLIENT_H

typedef struct {
    
} ot_client_t;

ot_client_t *ot_client_create();
void ot_client_init(ot_client_t *this);
void ot_client_deinit(ot_client_t *this);
void ot_client_destroy(ot_client_t *this);
void ot_client_test();

#endif