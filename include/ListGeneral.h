#pragma once

#include <stddef.h>

#ifdef _DEBUG
    #define DBG( ... ) __VA_ARGS__
#else
    #define DBG(...)
#endif

typedef int TYPE_DATA;
#define TYPE_SPECIFIER "d"

struct list_node
{
    list_node* next;
    list_node* prev;
    TYPE_DATA data;
};

struct List
{
    size_t capacity;

    list_node* node_array;
    list_node* head;
    list_node* tail;
    list_node* last_insert;
};
