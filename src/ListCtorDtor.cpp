#include <ListGeneral.h>
#include <ListCtorDtor.h>
#include <ListConsts.h>

#include <stdlib.h>
#include <stdio.h>

#include <Color.h>

FILE* list_log_file      = 0;
FILE* list_graphviz_file = 0;

//--------------------------------------------------------------
LIST_ERROR CtorListCommon (List* list)
{
    list_node* node_array = (list_node*) calloc (START_SIZE_NODE_ARRAY, sizeof(list_node));
    if (node_array == NULL)
        {
            fprintf (stderr, RED "ERROR: %s %d CtorListCommon(): node_array == NULL\n" RESET, __FILE__, __LINE__);
            return NODE_ARRAY_NULL;
        }

    list -> node_array = node_array;
    list -> head = list -> tail = list -> last_insert = &(list -> node_array[0]);
    list -> capacity = START_SIZE_NODE_ARRAY;

    list_log_file      = OpenFile (NAME_LIST_LOG_FILE, "w");
    list_graphviz_file = OpenFile (NAME_LIST_GRAPHVIZ_FILE, "w");

    return NO_ERROR;
}
//--------------------------------------------------------------
LIST_ERROR DtorListCommon (List* list)
{
    free (list -> node_array); list -> node_array = NULL;
    CloseFile (list_log_file);
    CloseFile (list_graphviz_file);

    return NO_ERROR;
}
//--------------------------------------------------------------
FILE* OpenFile (const char *__restrict filename, const char *__restrict modes)
{
    FILE* file_ptr = fopen ( filename, modes);

    if (file_ptr == NULL)
    {
        fprintf (stderr, RED "ERROR in %s %d: OpenFile()\n" RESET, __FILE__, __LINE__);
        return NULL;
    }
    return file_ptr;
}
//--------------------------------------------------------------
LIST_ERROR CloseFile (FILE* file)
{
    if (fclose (file) != 0)
    {
        fprintf (stdout, RED "ERROR in %s: %d line: file didn't close\n" RESET, __FILE__, __LINE__);
        return FILE_NOT_CLOSE;
    }

    return NO_ERROR;
}
//--------------------------------------------------------------
