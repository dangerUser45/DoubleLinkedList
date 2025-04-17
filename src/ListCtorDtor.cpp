#include <ListGeneral.h>
#include <ListCtorDtor.h>
#include <ListConsts.h>

#include <stdlib.h>
#include <stdio.h>

#include <Color.h>

//--------------------------------------------------------------
LIST_ERROR CtorListCommon (List* list)
{
    list_node* node_array = (list_node*) calloc (START_SIZE_NODE_ARRAY, sizeof(list_node));
    if (node_array == NULL)
        {
            fprintf (stderr, RED "ERROR: %s %d CtorListCommon(): node_array == NULL" RESET, __FILE__, __LINE__);
            return NODE_ARRAY_NULL;
        }

    list -> node_array = node_array;
    list -> head = list -> tail = list -> last_insert = &(list -> node_array[0]);
    list -> capacity = START_SIZE_NODE_ARRAY;

    // DBG
    // (
    //    FILE* Graphviz_file = OpenFile ();
    // )

    return NO_ERROR;
}
//--------------------------------------------------------------
LIST_ERROR DtorListCommon (List* list)
{
    free (list -> node_array); list -> node_array = NULL;

    return NO_ERROR;
}
//--------------------------------------------------------------
FILE* OpenFile (const char *__restrict filename, const char *__restrict modes)
{
    FILE* file_ptr = fopen ( filename, modes);

    if (file_ptr == NULL)
    {
        fprintf (stderr, RED "ERROR in %s %d: OpenFile()" RESET, __FILE__, __LINE__);
        return NULL;
    }
    return file_ptr;
}
//--------------------------------------------------------------

