#include <stdlib.h>
#include <stdio.h>

#include <ListConsts.h>
#include <ListToolFunctions.h>
#include <ListGeneral.h>
#include <ListErrors.h>
#include <Color.h>

extern FILE*      log_file;
extern FILE* graphviz_file;

//--------------------------------------------------------------
#define CHECK_NULL_POINTERS(list, node, ... ) \
{\
    unsigned char errors = 1; \
\
    if (list == NULL) \
    { \
        fprintf (stderr, RED "ERROR in %s: %d line: InsertData (): list = NULL\n" RESET, __FILE__, __LINE__); \
        fflush (stdout); \
        errors = errors << 1; \
    } \
\
    if (node == NULL) \
    { \
        fprintf (stderr, RED "ERROR in %s: %d line: InsertData (): node = NULL\n" RESET, __FILE__, __LINE__); \
        fflush (stdout); \
        errors = errors << 2; \
    } \
\
    if (errors & 2) \
        return LIST_PTR_NULL; \
    else if (errors & 4) \
        return NODE_PTR_NULL; \
}
//--------------------------------------------------------------
#define CHECK_INVALID_ADDRESS(node, ...) \
{ \
    if (node > list -> last_insert) \
    { \
        fprintf (stderr, RED "ERROR in %s: %d line: InsertData (): node there are in unallocated memory\n" RESET, __FILE__, __LINE__); \
        fflush (stdout); \
        return NODE_UNALLOCATED; \
    } \
}
//--------------------------------------------------------------

LIST_ERROR CheckOverFlow (List* list)
{
    if (list -> last_insert == list -> node_array && list -> last_insert -> next == 0)
    {
        list -> last_insert--;
        return NO_ERROR;
    }

    size_t delta = ( (size_t)(list -> last_insert) - (size_t)(list -> node_array) ) / sizeof (list_node);
    printf ("delta = %zu\n", delta);

    // -1 for that worked correct
    if (delta >= list -> capacity - 1)
    {
        DBG(printf ("Realloc\n");)
        size_t head_offset        = (size_t)list -> head - (size_t)list -> node_array;
        size_t tail_offset        = (size_t)list -> tail - (size_t)list -> node_array;
        size_t last_insert_offset = (size_t)list -> last_insert - (size_t)list -> node_array;

        list_node* new_node_array = (list_node*) realloc (list -> node_array, (size_t) list -> capacity * INCREASE_COEFFICIENT);

        if (new_node_array == NULL)
        {
            fprintf (stderr, RED "ERROR in %s, %d CheckOverFlow(): new_node_array = null\n" RESET, __FILE__, __LINE__);
            fflush (stdout);
            free (list -> node_array);
            return OVERFLOW_NODE_ARRAY;
        }

        list -> head        = (list_node*) ((size_t )new_node_array + head_offset);
        list -> tail        = (list_node*) ((size_t )new_node_array + tail_offset);
        list -> last_insert = (list_node*) ((size_t )new_node_array + last_insert_offset);

        list -> node_array = new_node_array;
        list -> capacity  *= INCREASE_COEFFICIENT;
    }

    return NO_ERROR;
}
//--------------------------------------------------------------
LIST_ERROR InsertHead (List* list, TYPE_DATA data)
{
    CHECK_NULL_POINTERS(list, (list_node*)1 );
    CheckOverFlow (list);
    list -> last_insert++;

    list_node* last_insert = list -> last_insert;
    list_node* head = list -> head;

    last_insert -> data = data;
    last_insert -> next = head;
    last_insert -> prev = list -> tail;

    head -> prev = last_insert;

    list -> head = last_insert;
    list -> tail -> next = last_insert;

    return NO_ERROR;
}
//--------------------------------------------------------------
LIST_ERROR InsertTail (List* list, TYPE_DATA data)
{
    CHECK_NULL_POINTERS(list, (list_node*) 1);
    CheckOverFlow     (list);
    list -> last_insert++;

    list_node* last_insert = list -> last_insert;
    list_node* tail = list -> tail;

    last_insert -> data = data;
    last_insert -> prev = tail;
    last_insert -> next = list -> head;

    tail -> next = last_insert;

    list -> tail = last_insert;
    list -> head -> prev = last_insert;

    return NO_ERROR;
}
//--------------------------------------------------------------
LIST_ERROR InsertAfter (List* list, TYPE_DATA data, list_node* node)
{
    CHECK_NULL_POINTERS(list, node);
    CHECK_INVALID_ADDRESS(node);
    CheckOverFlow     (list);

    list -> last_insert++;

    list_node* last_insert = list -> last_insert;

    last_insert -> next = node -> next;
    last_insert -> data = data;
    last_insert -> prev = node;

    node -> next -> prev = last_insert;
    node -> next = last_insert;

    if (node == list -> tail)
        list -> tail = list -> last_insert;

    return NO_ERROR;
}
//--------------------------------------------------------------
LIST_ERROR InsertBelow (List* list, TYPE_DATA data, list_node* node)
{
    CHECK_NULL_POINTERS(list, node);
    CHECK_INVALID_ADDRESS(node);
    CheckOverFlow (list);

    list -> last_insert++;

    list_node* last_insert = list -> last_insert;

    last_insert -> next = node;
    last_insert -> data = data;
    last_insert -> prev = node -> prev;

    node -> prev -> next = last_insert;
    node -> prev = last_insert;

    if (node == list -> head)
        list -> head = list -> last_insert;

    return NO_ERROR;
}
//--------------------------------------------------------------
LIST_ERROR InsertData (List* list, list_node* node, TYPE_DATA data)
{
    CHECK_NULL_POINTERS(list, node);
    CHECK_INVALID_ADDRESS(node);

    node -> data = data;

    return NO_ERROR;
}
//--------------------------------------------------------------
list_node* FindData (List* list, TYPE_DATA data)
{
    size_t capacity = list -> capacity;
    list_node* node = list -> head;

    for (size_t i = 0; i < capacity; ++i)
    {
        if (node -> data == data)
            return node;

        node = node -> next;
    }

    return 0;
}
//--------------------------------------------------------------
