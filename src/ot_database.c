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

    // Json file Read
    // Get card information size
    // malloc user list
    
}

void ot_database_deinit(ot_database_t *this) {

}

void ot_database_destroy(ot_database_t *this) {
    ot_database_deinit(this);
}

void ot_database_test() {
    ot_database_t *this = ot_database_create();
    ot_database_init(this, NULL);
    ot_database_destroy(this);
}

ot_database_t *ot_database_create() {
    ot_database_t *this = malloc(sizeof(ot_database_t));

    if(this == NULL) {
        // error log ...
        return NULL;
    }

    return this;
}