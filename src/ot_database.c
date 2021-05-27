#include "ot_database.h"

void ot_database_init(ot_database_t *this, uint8_t *file_path) {

    if(file_path == NULL) {
        memcpy(this->file_path, DEFAULT_FILE_PATH, strlen(DEFAULT_FILE_PATH));
    }
    else {
        if(strlen(file_path) < BIG_STRING_SIZE) {
            memcpy(this->file_path, file_path, strlen(file_path));
        }
        else {
            // error big file size
            memcpy(this->file_path, DEFAULT_FILE_PATH, strlen(DEFAULT_FILE_PATH));
        }
    }

    this->key_counter = 0;

    printf(">> OT Database Init Test\n");
    printf(">>> FILE PATH : %s\n", this->file_path);

    // Json file Read
    // Get card information size
    // malloc user list

}

void ot_database_parsed_json_file_set(ot_database_t *this)
{
    printf(">> Json File Parsed Json File Set Test\n");
    FILE *fp;
	char buffer[2048];

    fp = fopen(this->file_path,"r");
	fread(buffer, 2048, 1, fp);
	fclose(fp);

    this->parsed_json_file = json_tokener_parse(buffer);
}

void ot_database_set_keys(ot_database_t *this, const char *keys[])
{
    printf(">> Test Set Keys\n");

    memcpy(this->keys, keys, 24); // BURASI DEGISMELI ! 24 YERINE KEYS SIZE YAZILMALI FAKAT HATA VERIYOR !
}

void ot_database_set_data(ot_database_t *this)
{
    printf(">> Json File Get Any Object Test\n");

    struct json_object *object = this->parsed_json_file;

    ot_database_set_data_helper(this, object);

    // int i = this->key_counter;
    //
    // for(; this->keys[i] != NULL; i++)
    // {
    //     ot_database_set_data_helper(this, object);
    // }

}

void ot_database_set_data_helper(ot_database_t *this, struct json_object *object)
{
    for(; this->keys[this->key_counter] != NULL; this->key_counter++)
    {
        object = json_object_object_get(object, this->keys[this->key_counter]);
        data_type_control(this, object);
    }

    printf("OBJECT : %s\n", json_object_to_json_string(object));
}

void data_type_control(ot_database_t *this, struct json_object *object)
{
    int i=0;
    json_type types[7] = {json_type_null, json_type_boolean, json_type_double, json_type_string, json_type_int, json_type_object, json_type_array};
    void (*funcs[7])() = {json_file_null_type, json_file_boolean_type, json_file_double_type, json_file_string_type, json_file_integer_type, json_file_object_type, json_file_array_type};

    printf("sizeof(types) : %ld\n", sizeof(types));

    for(; types[i] < sizeof(types); i++)
    {
        printf("%d\n", i);
        if( json_object_get_type(object) == types[i])
        {
            (*funcs[i])(this, object);
            break;
        }
    }
}

void json_file_null_type(ot_database_t *this, struct json_object *object)
{
    printf("NULL !!!\n");

}

void json_file_boolean_type(ot_database_t *this, struct json_object *object)
{
    printf("BOOLEAN !\n");

    this->data = json_object_get_boolean(object);
}

void json_file_double_type(ot_database_t *this, struct json_object *object)
{
    printf("DOUBLE !\n");
    printf("DOUBLE : %f\n", json_object_get_double(object));

    // this->data = json_object_get_double(object);
}

void json_file_string_type(ot_database_t *this, struct json_object *object)
{
    printf("!!TEST!!\n");
    printf("STRING !\n");
    printf("STRING : %s\n", json_object_get_string(object));

    this->data = json_object_get_string(object);
}
void json_file_integer_type(ot_database_t *this, struct json_object *object)
{
    printf("INTEGER !\n");
    printf("INTEGER : %d\n", json_object_get_int(object));

    this->data = json_object_get_int(object);

}

void json_file_object_type(ot_database_t *this, struct json_object *object)
{
    printf("OBJECT !\n");
}

void json_file_array_type(ot_database_t *this, struct json_object *object)
{
    printf("ARRAY !\n");

    size_t i = 0;
    size_t array_size = json_object_array_length(object);

    object = json_object_array_get_idx(object, i);
    this->key_counter++;
    ot_database_set_data_helper(this, object);

}

void *ot_database_get_data(ot_database_t *this)
{
    return this->data;
}

void ot_database_deinit(ot_database_t *this)
{

}

void ot_database_destroy(ot_database_t *this)
{
    printf(">> Destroy Test\n");
    ot_database_deinit(this);
    free(this);
}

void ot_database_test()
{
    ot_database_t *test = ot_database_create();
    ot_database_init(test, NULL);
    ot_database_parsed_json_file_set(test);

    const char *keys[] = {"tester", NULL};
    printf("KEYS SIZE : %ld\n", sizeof(keys));

    ot_database_set_keys(test, keys);
    printf("TEST KEYS SIZE : %ld\n", sizeof(test->keys));

    for (size_t i = 0; i < 24; i++) {
        printf("KEYS : %s\n", test->keys[i]);
    }
    ot_database_set_data(test);

    int *temp;
    temp = ot_database_get_data(test);

    printf("TEMP : %d\n", temp);

    ot_database_destroy(test);
}

ot_database_t *ot_database_create() {
    ot_database_t *this = malloc(sizeof(ot_database_t));

    if(this == NULL) {
        // error log ...
        return NULL;
    }

    printf(">> OT Database Create Test\n");

    return this;
}
