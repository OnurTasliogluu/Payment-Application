#ifndef OT_LINKED_LIST_H
#define OT_LINKED_LIST_H

struct node
{
    void *data;
    struct node *next;
};

typedef struct node node_t;

typedef struct
{
    int max_list_size;
    node_t *root;
    void (*ot_linked_list_general_display)(void*);
    int (*ot_linked_list_general_compare)(void*, void*);
    void (*ot_linked_list_general_destroy)(void*);
} ot_linked_list_t;

ot_linked_list_t *ot_linked_list_create();
void ot_linked_list_init(ot_linked_list_t *this, int max_list_size);
void ot_linked_list_add_node(ot_linked_list_t *this, void *data);
void ot_linked_list_display(ot_linked_list_t *this);
node_t *ot_linked_list_search_node(ot_linked_list_t *this, void *data);
void ot_linked_list_delete_all_node(ot_linked_list_t *this);
int ot_linked_list_get_max_list_size(ot_linked_list_t *this);
void ot_linked_list_deinit(ot_linked_list_t *this);
void ot_linked_list_destroy(ot_linked_list_t *this);
void ot_linked_list_test();

// Function list
void ot_linked_list_set_display_function(ot_linked_list_t *this, void (*display)(void*));
void ot_linked_list_set_compare_function(ot_linked_list_t *this, int (*compare)(void*, void*));
void ot_linked_list_set_destroy_function(ot_linked_list_t *this, void (*destroy)(void*));

#endif
