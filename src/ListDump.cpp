#include <stdlib.h>
#include <stdio.h>

#include <ListGeneral.h>
#include <ListConsts.h>
#include <ListErrors.h>
#include <ListDump.h>

#include <Color.h>

//--------------------------------------------------------------
#define DumpPart(text) \
{ \
\
    if (list -> text == NULL)\
    {\
        fprintf (stderr, RED "ERROR in %s %d: ListDump()\n" RESET, __FILE__, __LINE__);\
    }\
\
    fprintf (stdout,  BLUE "list -> " #text "         = " RESET "%p\n",   list -> text);                              \
    fprintf (stdout,  BLUE "list -> " #text " -> data = " RESET "%" TYPE_SPECIFIER "\n", list -> text -> data); \
    fprintf (stdout,  BLUE "list -> " #text " -> next = " RESET "%p\n", list -> text -> next);                  \
    fprintf (stdout,  BLUE "list -> " #text " -> prev = " RESET "%p\n\n", list -> text -> prev);                \
}
//--------------------------------------------------------------
LIST_ERROR ListDump (List* list)
{
    if (list == NULL)
    {
        fprintf (stderr, RED "ERROR: %s %d ListDump(): list = NULL" RESET, __FILE__, __LINE__);
        return NODE_ARRAY_NULL;
    }

    fprintf (stdout, YELLOW "------------D U M P--------------\n" RESET);

    fprintf (stdout,  BLUE "list pointer  = " RESET "%p\n", list);
    fprintf (stdout,  BLUE "list capacity = " RESET "%zu\n\n", list -> capacity);

    DumpPart(head);
    DumpPart(tail);
    DumpPart(last_insert);

    list_node* node_array = list -> node_array;

    fprintf (stdout, GREEN "\n\t\tNode array\n" RESET);
    for (size_t i = 0; i < list -> capacity; ++i)
    {
        fprintf (stdout, "#%zu \nAddress Node array[%zu] = %p\n",i , i, node_array + i);
        fprintf (stdout, "Node_array[%zu] -> next = %p\n", i, node_array[i].next);
        fprintf (stdout, "Node_array[%zu] -> prev = %p\n", i, node_array[i].prev);
        fprintf (stdout, "Node_array[%zu] -> data = %" TYPE_SPECIFIER "\n\n", i, node_array[i].data);
    }

    fprintf (stdout, YELLOW "---------------------------------\n" RESET);
    return NO_ERROR;
}
//--------------------------------------------------------------
LIST_ERROR ListGraphDump ()
{

    return NO_ERROR;
}
//--------------------------------------------------------------

