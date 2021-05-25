#include <stdio.h>
#include <stdlib.h>

#include "ot_hash_table.h"

ot_hash_table_t *ot_hash_table_create()
{
    ot_hash_table_t *this = malloc(sizeof(ot_hash_table_t));

    if (this == NULL)
    {
        printf("Allocation Error!\n");
    }

    return this;
}

void ot_hash_table_init(ot_hash_table_t *this, int table_size)
{
    this->table_size = table_size;
    this->table_list = malloc(sizeof(void*)*table_size);
    for (size_t i = 0; i < this->table_size; i++)
    {
        this->table_list[i] = NULL;
    }
}

void ot_hash_table_deinit(ot_hash_table_t *this)
{
    this->table_size = 0;

    for(size_t i=0; i<this->table_size; i++)
    {
        if (this->table_list[i])
        {
            free(this->table_list[i]);
        }
    }
}

void ot_hash_table_destroy(ot_hash_table_t *this)
{
    ot_hash_table_deinit(this);
    free(this->table_list);
    free(this);
}

int ot_hash_table_get_table_size(ot_hash_table_t *this)
{
    return this->table_size;
}

int ot_hash_table_calculater(ot_hash_table_t *this, int key)
{
    return key % this->table_size;
}

int ot_hash_table_add(ot_hash_table_t *this, void *data, int key)
{
    int index = ot_hash_table_calculater(this, key);
    if (this->table_list[index] == NULL)
    {
        this->table_list[index] = data;
        return 0;
    }

    return -1;
}

void *ot_hash_table_general_get_data(ot_hash_table_t *this, int key)
{
    int index = ot_hash_table_calculater(this, key);
    return this->table_list[index];
}

void ot_hash_table_delete(ot_hash_table_t *this, void *data, int key)
{
    int index = ot_hash_table_calculater(this, key);
    free(this->table_list[index]);
}

void ot_hash_table_test()
{
    ot_hash_table_t *this = ot_hash_table_create();
    ot_hash_table_init(this, 10);
    ot_hash_table_destroy(this);
}
