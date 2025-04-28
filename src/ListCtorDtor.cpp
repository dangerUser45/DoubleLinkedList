#include <stdlib.h>
#include <stdio.h>

#include <ListGeneral.h>
#include <ListCtorDtor.h>
#include <ListConsts.h>

#include <Color.h>

FILE* list_log_file      = 0;
FILE* list_graphviz_file = 0;

static size_t file_counter = 0;

//--------------------------------------------------------------
List* CtorListCommon ()
{
    List* list = (List*) calloc (1, sizeof(List));
    if (list == NULL)
    {
        fprintf (stderr, RED "ERROR: %s %d CtorListCommon(): list = (null)\n" RESET, __FILE__, __LINE__);
        return (List*)LIST_PTR_NULL;
    }

    list_node* node_array = (list_node*) calloc (START_SIZE_NODE_ARRAY, sizeof(list_node));
    if (node_array == NULL)
    {
        fprintf (stderr, RED "ERROR: %s %d CtorListCommon(): node_array = (null)\n" RESET, __FILE__, __LINE__);
        return (List*)NODE_ARRAY_NULL;
    }

    list -> node_array = node_array;
    list -> head = list -> tail = list -> last_insert = &(list -> node_array[0]);
    list -> capacity = START_SIZE_NODE_ARRAY;

    if (file_counter == 0)
    {
        list_log_file      = OpenFile (NAME_LIST_LOG_FILE,      "w");
        list_graphviz_file = OpenFile (NAME_LIST_GRAPHVIZ_FILE, "w");
        ++file_counter;
    }

    return list;
}
//--------------------------------------------------------------
LIST_ERROR DtorListCommon (List* list)
{
    free (list -> node_array); list -> node_array = NULL;

    if (file_counter == 1)
    {
        CloseFile (list_log_file);
        CloseFile (list_graphviz_file);
        --file_counter;
    }

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
