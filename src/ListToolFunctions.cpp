#include <stdlib.h>
#include <stdio.h>

#include <ListConsts.h>
#include <ListToolFunctions.h>
#include <ListGeneral.h>
#include <ListErrors.h>
#include <Color.h>


//--------------------------------------------------------------
LIST_ERROR CheckOverFlow (List* list)
{
    if ((((size_t) (list -> last_insert) / sizeof (list_node*))
       - ((size_t) (list -> node_array)  / sizeof (list_node*)))
       >= list -> capacity)
        {
            DBG(printf ("Realloc\n");)
            list_node* new_node_array = (list_node*) realloc (list -> node_array, (size_t) list -> capacity * INCREASE_COEFFICIENT);

            if (new_node_array == NULL)
            {
                fprintf (stderr, RED "ERROR in %s, %d CheckOverFlow(): new_node_array = null\n" RESET, __FILE__, __LINE__);
                return OVERFLOW_NODE_ARRAY;
            }

            list -> node_array = new_node_array;
            list -> capacity *= INCREASE_COEFFICIENT;
        }

    return NO_ERROR;
}
//--------------------------------------------------------------
LIST_ERROR InsertHead (List* list, TYPE_DATA data)
{
    //CheckOverFlow (list);
    list -> last_insert++;

    list_node* last_insert = list -> last_insert;
    list_node* head = list -> head;

    last_insert -> data = data;
    last_insert -> next = head;

    head -> prev = last_insert;

    list -> head = last_insert;

    return NO_ERROR;
}
//--------------------------------------------------------------
LIST_ERROR InsertTail (List* list, TYPE_DATA data)
{
    CheckOverFlow (list);
    list -> last_insert++;

    list_node* last_insert = list -> last_insert;
    list_node* tail = list -> tail;

    last_insert -> data = data;
    last_insert -> prev = tail;

    tail -> next = last_insert;

    list -> tail = last_insert;

    return NO_ERROR;
}
//--------------------------------------------------------------
LIST_ERROR InsertAfter (List* list, TYPE_DATA data, list_node* node)
{
    CheckOverFlow (list);
    list -> last_insert++;

    list_node* last_insert = list -> last_insert;

    last_insert -> next = node -> next;
    last_insert -> data = data;
    last_insert -> prev = node;

    node -> next -> prev = last_insert;
    node -> next = last_insert;

    return NO_ERROR;
}
//--------------------------------------------------------------
LIST_ERROR InsertBelow (List* list, TYPE_DATA data, list_node* node)
{
    CheckOverFlow (list);
    list -> last_insert++;

    list_node* last_insert = list -> last_insert;

    last_insert -> next = node;
    last_insert -> data = data;
    last_insert -> prev = node -> prev;

    node -> prev -> next = last_insert;
    node -> prev = last_insert;

    return NO_ERROR;
}
//--------------------------------------------------------------
LIST_ERROR InsertData (list_node* node, TYPE_DATA data)
{
    if (node == NULL)
    {
        fprintf (stderr, RED "ERROR in %s %d InsertData (): node = NULL\n" RESET, __FILE__, __LINE__);
        return NODE_NULL;
    }
    node -> data = data;

    return NO_ERROR;
}
//--------------------------------------------------------------
