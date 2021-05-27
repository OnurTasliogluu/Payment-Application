#ifndef OT_DATABASE_H
#define OT_DATABASE_H

#include "ot_common.h"
#include <json-c/json.h>

#define DEFAULT_FILE_PATH "/home/squeezy/Desktop/my_test_area/user_database.json"

// uint8_t *json_general_information_list[] = {
//     "count"
// };

typedef enum {
    COUNT,
    JSON_GENERAL_INFORMATION_SIZE
} json_general_information_e;

typedef struct
{
    uint8_t file_path[128];
    struct json_object *parsed_json_file;
    void *data;
    const char *keys[256];
    int key_counter;

} ot_database_t;

ot_database_t *ot_database_create();
void ot_database_init(ot_database_t *this, uint8_t *file_path);
void ot_database_parsed_json_file_set(ot_database_t *this);
void ot_database_set_keys(ot_database_t *this, const char *keys[]);
void ot_database_set_data(ot_database_t *this);
void ot_database_set_data_helper(ot_database_t *this, struct json_object *object);
void data_type_control(ot_database_t *this, struct json_object *object);

void json_file_null_type(ot_database_t *this, struct json_object *object);
void json_file_boolean_type(ot_database_t *this, struct json_object *object);
void json_file_double_type(ot_database_t *this, struct json_object *object);
void json_file_string_type(ot_database_t *this, struct json_object *object);
void json_file_integer_type(ot_database_t *this, struct json_object *object);
void json_file_object_type(ot_database_t *this, struct json_object *object);
void json_file_array_type(ot_database_t *this, struct json_object *object);


void *ot_database_get_data(ot_database_t *this);


void ot_database_deinit(ot_database_t *this);
void ot_database_destroy(ot_database_t *this);
void ot_database_test();

#endif
