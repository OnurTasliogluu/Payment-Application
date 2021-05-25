#ifndef OT_DATABASE_H
#define OT_DATABASE_H

#include "ot_common.h"

#define DEFAULT_FILE_PATH "/home/x/Desktop/piton_application/database/user_database.json"

uint8_t *json_general_information_list[] = {
    "count"
};

typedef enum {
    COUNT,
    JSON_GENERAL_INFORMATION_SIZE
} json_general_information_e;

typedef struct {
    char file_path[BIG_STRING_SIZE];
    void *data;
} ot_database_t;

ot_database_t *ot_database_create();
void ot_database_init(ot_database_t *this, uint8_t *file_path);
void ot_database_deinit(ot_database_t *this);
void ot_database_destroy(ot_database_t *this);
void ot_database_test();

#endif