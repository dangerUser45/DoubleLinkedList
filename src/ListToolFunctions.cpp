#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include <ListConsts.h>
#include <ListToolFunctions.h>
#include <ListGeneral.h>
#include <ListErrors.h>
#include <Color.h>

extern FILE* list_log_file;

//--------------------------------------------------------------
#define LIST_CHECK_NULL_POINTERS(list, node, ... ) \
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
#define LIST_CHECK_INVALID_ADDRESS(node, ...) \
{ \
    if (node > list -> last_insert) \
    { \
        fprintf (stderr, RED "ERROR in %s: %d line: InsertData (): node there are in unallocated memory\n" RESET, __FILE__, __LINE__); \
        fflush (stdout); \
        return NODE_UNALLOCATED; \
    } \
}
//--------------------------------------------------------------
#define LIST_CHECK_INDEX(list, index)\
{\
    size_t delta_elem = ( ( (size_t)(list -> last_insert) - (size_t)(list -> node_array) ) / sizeof (list_node) ) + 1;\
    if (index > delta_elem - 1)\
    {\
        fprintf (stderr, RED "ERROR in %s: %d line: InsertData (): invalid index in node array\n" RESET, __FILE__, __LINE__); \
        return INVALID_INDEX;\
    }\
}
//--------------------------------------------------------------
LIST_ERROR ListCheckOverFlow (List* list)
{
    if (list -> last_insert == list -> node_array && list -> last_insert -> next == 0)
    {
        list -> last_insert--;
        return NO_ERROR;
    }

    size_t delta_elem = ( ( (size_t)(list -> last_insert) - (size_t)(list -> node_array) ) / sizeof (list_node) ) + 1;

    if (delta_elem + 1 > list -> capacity)
    {
        LIST_ERROR error = ListIncreaseNodeArray (list, delta_elem);
        return error;
    }

    return NO_ERROR;
}
//--------------------------------------------------------------
LIST_ERROR ListIncreaseNodeArray (List* list, size_t delta_elem)
{
    list_node* old_node_array = list -> node_array;
    list_node* new_node_array = (list_node*) calloc (list -> capacity * INCREASE_COEFFICIENT, sizeof (list_node));

    if (new_node_array == NULL)
    {
        fprintf (stderr, RED "ERROR in %s, %d CheckOverFlow(): new_node_array = null\n" RESET, __FILE__, __LINE__);
        fflush (stdout);
        free (old_node_array);
        return OVERFLOW_NODE_ARRAY;
    }

    size_t delta_address = (size_t)(new_node_array) - (size_t)(old_node_array);

    for (size_t i = 0; i <= delta_elem - 1; ++i)
    {
        new_node_array[i].data = old_node_array[i].data;
        new_node_array[i].next = (list_node*) ( (size_t)(old_node_array[i].next) + delta_address );
        new_node_array[i].prev = (list_node*) ( (size_t)(old_node_array[i].prev) + delta_address );
    }

    list -> head        = (list_node*) ( (size_t)(list -> head)        + delta_address);
    list -> tail        = (list_node*) ( (size_t)(list -> tail)        + delta_address);
    list -> last_insert = (list_node*) ( (size_t)(list -> last_insert) + delta_address);

    list -> node_array  = new_node_array;
    list -> capacity   *= INCREASE_COEFFICIENT;

    free (old_node_array);

    return NO_ERROR;
}
//--------------------------------------------------------------
LIST_ERROR ListInsertHead (List* list, TYPE_DATA data)
{
    LIST_CHECK_NULL_POINTERS(list, (list_node*)1 );
    ListCheckOverFlow (list);
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
LIST_ERROR ListInsertTail (List* list, TYPE_DATA data)
{
    LIST_CHECK_NULL_POINTERS(list, (list_node*) 1);
    ListCheckOverFlow     (list);
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
LIST_ERROR ListInsertAfter (List* list, size_t index, TYPE_DATA data)
{
    LIST_CHECK_NULL_POINTERS(list, (list_node*)1);
    LIST_CHECK_INDEX(list, index);
    ListCheckOverFlow     (list);

    list -> last_insert++;

    list_node* last_insert = list -> last_insert;
    list_node* node = 0;
    ListFindNode (list, index, &node);

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
LIST_ERROR ListInsertBelow (List* list, size_t index, TYPE_DATA data)
{
    LIST_CHECK_NULL_POINTERS(list, (list_node*)1);
    LIST_CHECK_INDEX(list, index);
    ListCheckOverFlow (list);

    list -> last_insert++;

    list_node* last_insert = list -> last_insert;
    list_node* node = 0;
    ListFindNode (list, index, &node);

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
LIST_ERROR ListInsertData (List* list, size_t index, TYPE_DATA data)
{
    LIST_CHECK_NULL_POINTERS   (list, (list_node*)1);
    LIST_CHECK_INDEX(list, index)

    list_node* node = 0;
    ListFindNode (list, index, &node);

    node -> data = data;

    return NO_ERROR;
}
//--------------------------------------------------------------
LIST_ERROR ListFindData (List* list, TYPE_DATA data, list_node** dest)
{
    size_t delta = ( (size_t)(list -> last_insert) - (size_t)(list -> node_array) ) / sizeof (list_node);
    list_node* node = list -> head;

    for (size_t i = 0; i < delta + 1; ++i)
    {
        if (node -> data == data)
        {
            *dest = node;
            return NO_ERROR;
        }

        node = node -> next;
    }

    return NODE_NOT_FOUND;
}
//--------------------------------------------------------------
LIST_ERROR ListFindIndex (List* list, list_node* searched_node, size_t* dest)
{
    LIST_CHECK_NULL_POINTERS(list, searched_node);
    LIST_CHECK_INVALID_ADDRESS(searched_node);

    list_node* node = list -> head;
    size_t delta = ( (size_t)(list -> last_insert) - (size_t)(list -> node_array) ) / sizeof (list_node);

    for (size_t i = 0; i < delta + 1; ++i)
    {
        if (node == searched_node)
        {
            *dest = i;
            return NO_ERROR;
        }

        node = node -> next;
    }

    return NODE_NOT_FOUND;
}
//--------------------------------------------------------------
LIST_ERROR ListFindNode (List* list, size_t index, list_node** dest)
{
    LIST_CHECK_NULL_POINTERS(list, (list_node*) 1);

    list_node* node = list -> head;
    for (size_t i = 0; i < index; ++i)
        node = node -> next;

    *dest = node;

    return NO_ERROR;
}
//--------------------------------------------------------------
LIST_ERROR ListDelete (List* list, size_t index)
{
    list_node* node = 0;
    ListFindNode(list, index, &node);

    node -> next -> prev = node -> prev;
    node -> prev -> next = node -> next;

    return NO_ERROR;
}
//--------------------------------------------------------------
//TODO

/*---                                               ---*\
;   Сделать функцию реалокации вниз
;
;   Изменить алгоритм так, чтобы в структуре хранились
;   не сами адреса, а индексы для отдельного массива с
;   адресами всех элементов
\*---                                               ---*/
