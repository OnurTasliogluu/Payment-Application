#ifndef OT_HASH_TABLE_H
#define OT_HASH_TABLE_H

typedef struct
{
    int table_size;
    void **table_list;

    int (*ot_hash_table_general_key_calculater)(void*);
} ot_hash_table_t;

// General Functions
ot_hash_table_t *ot_hash_table_create();
void ot_hash_table_init(ot_hash_table_t *this, int table_size);
void ot_hash_table_deinit(ot_hash_table_t *this);
void ot_hash_table_destroy(ot_hash_table_t *this);
void ot_hash_table_test();

int ot_hash_table_add(ot_hash_table_t *this, void *data, int index);
void *ot_hash_table_general_get_data(ot_hash_table_t *this, int index);
void ot_hash_table_delete(ot_hash_table_t *this, void *data, int index);

// Parameters Functions
int ot_hash_table_get_table_size(ot_hash_table_t *this);
int ot_hash_table_calculater(ot_hash_table_t *this, int key);

#endif