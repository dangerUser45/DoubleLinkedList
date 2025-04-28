#pragma once

#include <stddef.h>

#ifdef _DEBUG
    #define DBG( ... ) __VA_ARGS__
#else
    #define DBG(...)
#endif

#include <stdlib.h>

#ifdef ASSERT_ON
    #define assert(pointer); if (pointer == NULL)\
                             {\
                            fprintf(stderr, RED "ASSERTION FAILED: %s:%d: (" #pointer ") = (null)\n" RESET, __FILE__, __LINE__);\
                            exit (0);\
                             }
#else
    #define assert(pointer);
#endif


typedef char* TYPE_DATA;
#define TYPE_SPECIFIER "s"

struct list_node
{
    list_node* next;
    list_node* prev;
    TYPE_DATA  data;
};

struct List
{
    size_t capacity;

    list_node* node_array;
    list_node* head;
    list_node* tail;
    list_node* last_insert;
};
