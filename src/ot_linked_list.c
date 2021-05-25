#include <stdio.h>
#include <stdlib.h>

#include "ot_linked_list.h"

ot_linked_list_t *ot_linked_list_create()
{
    ot_linked_list_t *this = malloc(sizeof(ot_linked_list_t));

    if (this == NULL)
    {
        printf("Allocation Error!\n");
    }

    return this;
}

void ot_linked_list_init(ot_linked_list_t *this, int max_list_size)
{
    this->max_list_size = max_list_size;
    this->ot_linked_list_general_display = NULL;
    this->root = NULL;
}

void ot_linked_list_add_node(ot_linked_list_t *this, void *data)
{
    node_t *root = this->root;
    node_t *temp = NULL;

    temp = malloc(sizeof(node_t));
    temp->data = data;
    temp->next = NULL;

    if (this->root == NULL)
    {
        this->root = temp;
        return;
    }

    while (root->next != NULL)
    {
        root = root->next;
    }

    root->next = temp;
}

node_t *ot_linked_list_search_node(ot_linked_list_t *this, void *data)
{
    node_t *temp = this->root;

    while (temp != NULL)
    {
        if(!this->ot_linked_list_general_compare(temp->data, data))
        {
            return temp;
            break;
        }
        temp = temp->next;
    }

    return NULL;
}

void ot_linked_list_delete_all_node(ot_linked_list_t *this)
{
    node_t *temp = this->root;
    node_t *next = NULL;

    while (temp != NULL)
    {
        this->ot_linked_list_general_destroy(temp->data);
        next = temp->next;
        free(temp);
        temp = next;
    }
    this->root = NULL;
}

int ot_linked_list_get_max_list_size(ot_linked_list_t *this)
{
    return this->max_list_size;
}

void ot_linked_list_display(ot_linked_list_t *this)
{
    node_t *temp = this->root;
    while (temp != NULL)
    {
        printf("DISPLAY\n");
        this->ot_linked_list_general_display(temp->data);
        temp = temp->next;
    }
}

void ot_linked_list_set_compare_function(ot_linked_list_t *this, int (*compare)(void*, void*))
{
    this->ot_linked_list_general_compare = compare;
}

void ot_linked_list_set_display_function(ot_linked_list_t *this, void (*display)(void*))
{
    this->ot_linked_list_general_display = display;
}

void ot_linked_list_set_destroy_function(ot_linked_list_t *this, void (*destroy)(void*))
{
    this->ot_linked_list_general_destroy = destroy;
}

void ot_linked_list_deinit(ot_linked_list_t *this)
{
    this->max_list_size = 0;
    this->ot_linked_list_general_display = NULL;
    // first delete all node
    ot_linked_list_delete_all_node(this);
    this->root = NULL;
}

void ot_linked_list_destroy(ot_linked_list_t *this)
{
    ot_linked_list_deinit(this);
    free(this);
}

void ot_linked_list_test()
{
    ot_linked_list_t *this = ot_linked_list_create();
    ot_linked_list_init(this, 10);
    printf("max_list_size=%d\n", ot_linked_list_get_max_list_size(this));
    ot_linked_list_deinit(this);
    ot_linked_list_destroy(this);
}
