#include <stdlib.h>
#include <stdio.h>

#include <ListGeneral.h>
#include <ListConsts.h>
#include <ListErrors.h>
#include <ListDump.h>
#include <ListToolFunctions.h>

#include <Color.h>

extern FILE* list_log_file;
extern FILE* list_graphviz_file;

//--------------------------------------------------------------
#define DumpPart(text) \
{ \
\
    if (list -> text == NULL)\
    {\
        fprintf (stderr, RED "ERROR in %s %d: ListDump()\n" RESET, __FILE__, __LINE__);\
    }\
\
    fprintf (stdout,  BLUE "list -> " #text "         = " RESET "%p\n",   list -> text);                        \
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
        fflush (stdout);
        return NODE_ARRAY_NULL;
    }

    fprintf (stdout, YELLOW "------------D U M P--------------\n" RESET);

    fprintf (stdout,  BLUE "list pointer  = " RESET "%p\n", list);
    fprintf (stdout,  BLUE "list capacity = " RESET "%zu\n\n", list -> capacity);
    fflush (stdout);

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
        fflush  (stdout);
    }

    fprintf (stdout, YELLOW "---------------------------------\n" RESET);
    fflush (stdout);
    return NO_ERROR;
}
//--------------------------------------------------------------
LIST_ERROR ListGraphDump (List* list)
{
    setvbuf      (list_log_file, NULL, _IONBF, 0);  // Отключение буферизации
    setvbuf (list_graphviz_file, NULL, _IONBF, 0);  // Отключение буферизации

    ListCreateDotText (list);

    CheckSysRetVal ();
    ListPrintHtmlIntro ();

    ListAddImages ();

    setvbuf     (list_log_file,  NULL, _IOFBF, BUFSIZ);  // Полная буферизация
    setvbuf (list_graphviz_file, NULL, _IOFBF, BUFSIZ);  // Полная буферизация

    return NO_ERROR;
}
//--------------------------------------------------------------
LIST_ERROR CheckSysRetVal ()
{
    int result = system ("dot -Tsvg dump/Graphviz_dot/ListGraphviz.txt -o dump/Graphviz_dot/images/img1.svg");
    if (result != 0)
    {
        fprintf (stderr, RED "ERROR in %s: %d line: system (): code error = %d\n" RESET, __FILE__, __LINE__, result);
        fflush (stdout);
    }

    return NO_ERROR;
}
//--------------------------------------------------------------
LIST_ERROR ListPrintHtmlIntro ()
{
    fprintf (list_log_file, ""
    "<pre>\n\t"
	    "<font size = 20, color = red>\n\t\t"
            "<div style = \"text-align: center;\">\n"
                "DUMP\n\t\t"
            "</div>\n\t"
	    "</font>\n"
    "</pre>\n\n"

    "<style>\n"
    ".center-horizontally\n"
    "{\n\t"
        "display: block;\n\t"
        "margin-left: auto;\n\t"
        "margin-right: auto;\n\t"
        "width: 30%%;\n\t"
        "height: auto;\n"
    "}\n"
    "</style>\n\n"
    );

    return NO_ERROR;
}
//--------------------------------------------------------------
LIST_ERROR ListAddImages ()
{
    fprintf (list_log_file, ""
    "<img src = \"../dump/Graphviz_dot/images/img1.svg\" class = \"center-horizontally\">\n"
    );

    return NO_ERROR;
}
//--------------------------------------------------------------
LIST_ERROR ListCreateDotText (List* list)
{
    ListWriteIntro ();
    ListWriteSort (list);
    ListWriteUnsort (list);
    ListWriteStructList (list);

    return NO_ERROR;
}
//--------------------------------------------------------------
LIST_ERROR ListWriteIntro ()
{
    fprintf (list_graphviz_file, ""

    "digraph\n"
    "{\n\t"
        "rankdir  = LR;                         // Горизонтальная ориентация\n\t"
	    "newrank  = true;                       // Улучшенный алгоритм ранжирования\n\t"
        "compound = true;                       // Разрешить сложные связи\n\n\t"

        "nodesep  = 0.5;                        // Расстояние между узлами\n\t"
        "ranksep  = 1.0;                        // Расстояние между уровнями\n\n\t"

        "graph [fontname=\"Helvetica\"];        // Шрифт для всего графа\n\n\t"

        "bgcolor   = \"" BACKGROUND_COLOR "\";  // Цвет фона - светло-синий\n\t"
        "fontcolor = \"black\";                 // Цвет текста\n\n\t");

    return NO_ERROR;
}
//--------------------------------------------------------------
LIST_ERROR ListWriteSort (List* list)
{
    fprintf (list_graphviz_file, ""

    "//------------------------------------------------------------------------------------------------------------------\n\t"
        "subgraph cluster_node_array_sort\n\t"
        "{\n\t\t"
            "node [shape = Mrecord, style = filled, color= black, fillcolor = \"" NODE_ARRAY_COLOR "\"]; // цвет - светло-зелёный\n\t\t"
            "edge [color = black];\n\t\t"
            "color = \"" BACKGROUND_COLOR "\";\n\n\t\t");

            list_node* node = list -> head;
            size_t delta = ( (size_t)(list -> last_insert) - (size_t)(list -> node_array) ) / sizeof (list_node);

            for (size_t i = 0; i < delta + 1; ++i)
            {
                fprintf (list_graphviz_file,""
                "subgraph cluster_node_%zu_sort\n\t\t"
                "{\n\t\t\t", i);

                fprintf (list_graphviz_file, ""
                    "node_%zu_sort [", i);

                if (node == list -> last_insert)
                    fprintf (list_graphviz_file, "fillcolor = \"" LAST_INSERT_COLOR "\"");

                fprintf (list_graphviz_file,""
                    "label = \"address = %p | next: %p | data: %" TYPE_SPECIFIER " | prev: %p\"];\n\t\t\t"
                    "label = \"%zu\";\n\t\t"
                "}\n\n\t\t",  node, node -> next, node -> data, node -> prev, i);

                node = node -> next;
            }

            fprintf (list_graphviz_file,""
            "fontsize = \"20\";\n\t\t"
            "fontcolor = black;\n\t\t"
            "label = \"Node array sort\";\n\t\t"
            "color =  \"" BACKGROUND_COLOR "\";\n\n\t\t");

            for (size_t i = 0; i < delta; ++i)
                fprintf (list_graphviz_file, "node_%zu_sort -> node_%zu_sort;\n\t\t", i, i + 1);

            fprintf (list_graphviz_file, "node_%zu_sort -> node_%zu_sort;\n\n\t\t", delta, (size_t)0);

            fprintf (list_graphviz_file,""
            "edge [color = red];\n\t\t");

            for (size_t i = 0, j = delta; i < delta; ++i, --j)
                fprintf (list_graphviz_file, "node_%zu_sort -> node_%zu_sort;\n\t\t", j, j - 1);

            fprintf (list_graphviz_file, "node_%zu_sort -> node_%zu_sort;\n\t"
            "}\n\n\t", (size_t)0, delta);

    return NO_ERROR;
}
//--------------------------------------------------------------
LIST_ERROR ListWriteUnsort (List* list)
{
    fprintf (list_graphviz_file, ""

    "//------------------------------------------------------------------------------------------------------------------\n\t"
        "subgraph cluster_node_array_unsort\n\t"
        "{\n\t\t"
            "node [shape = Mrecord, style = filled, color = black, fillcolor = \"" NODE_ARRAY_COLOR "\"];\n\t\t"
            "edge [color = black];\n\t\t"
            "color = \"" BACKGROUND_COLOR "\";\n\n\t\t");

            size_t delta = ( (size_t)(list -> last_insert) - (size_t)(list -> node_array) ) / sizeof (list_node);
            list_node* node_array = list -> node_array;

            for (size_t i = 0; i < delta + 1; ++i)
            {
                fprintf (list_graphviz_file,""
                "subgraph cluster_node_%zu_unsort\n\t\t"
                "{\n\t\t\t", i);

                fprintf (list_graphviz_file, ""
                    "node_%zu_unsort [", i);

                size_t index = 0;
                FindIndex (list, node_array, &index);

                if (node_array == list -> last_insert)
                    fprintf (list_graphviz_file, "fillcolor = \"" LAST_INSERT_COLOR "\"");

                fprintf (list_graphviz_file,""
                    "label = \"index in node array: %zu | address = %p | next: %p | data: %" TYPE_SPECIFIER " | prev: %p\"];\n\t\t"
                    "label = \"%zu\";\n\t\t"
                "}\n\n\t\t",  i, node_array, node_array -> next, node_array -> data, node_array -> prev, index);  //FIXME label != 1 !!!!

                ++node_array;
            }

            fprintf (list_graphviz_file, ""
            "fontsize = \"20\";\n\t\t"
            "fontcolor = black;"
            "label = \"Node array\";"
            "color = \"" BACKGROUND_COLOR "\";\n\n\t\t"

            "edge [color = black];\n\n\t\t");

            for (size_t i = 0; i < delta; ++i)
                fprintf (list_graphviz_file, ""
                "node_%zu_unsort -> node_%zu_unsort;\n\t\t", i, i + 1);

        fprintf (list_graphviz_file, "\n\t}\n\n\t");

    return NO_ERROR;
}
//--------------------------------------------------------------
LIST_ERROR ListWriteStructList (List* list)
{
    static size_t graph_dump_counter = 0;
                ++graph_dump_counter;

    fprintf (list_graphviz_file, ""
    "//-----------------------------------------------------------------------------------------------------------------\n\t"
        "subgraph cluster_struct_list\n\t"
        "{\n\t\t"
            "node [shape = Mrecord, style = filled, color = black, fillcolor = \"" STRUCT_DATA_COLOR "\"];\n\t\t"
            "edge [color = \"" BACKGROUND_COLOR "\"];\n\t\t"
            "color = \"" BACKGROUND_COLOR "\";\n\n\t\t"

            "head [label = \"address = %p | next: %p | data: %" TYPE_SPECIFIER " | prev: %p \"]\n\t\t"
            "tail [label = \"address = %p | next: %p | data: %" TYPE_SPECIFIER " | prev: %p \"]\n\t\t"
            "last_insert [label = \"address = %p | next: %p | data: %" TYPE_SPECIFIER " | prev: %p \"]\n\n\t\t"

            "data [label = \"list pointer = %p | list capacity = %zu | start: list node array = %p \\nend:    list node array = %p\"]\n\n\t\t"

            "subgraph cluster_node_list_data\n\t\t"
            "{\n\t\t\t"
                "data;\n\t\t\t"
                "label = \"Data\";\n\t\t\t"
                "color = \"" BACKGROUND_COLOR "\";\n\t\t"
            "}\n\n\t\t"

            "subgraph cluster_head\n\t\t"
            "{\n\t\t\t"
                "head;\n\t\t\t"
                "label = \"Head\"\n\t\t\t"
                "color = \"" BACKGROUND_COLOR "\";\n\t\t"
            "}\n\n\t\t"

            "subgraph cluster_tail\n\t\t"
            "{\n\t\t\t"
                "tail;\n\t\t\t"
                "label = \"Tail\";\n\t\t\t"
                "color = \"" BACKGROUND_COLOR "\";\n\t\t"
            "}\n\n\t\t"

            "subgraph cluster_last_insert\n\t\t"
            "{\n\t\t\t"
                "last_insert;\n\t\t\t"
                "label = \"Last insert\";\n\t\t\t"
                "color = \"" BACKGROUND_COLOR "\";\n\t\t"
            "}\n\n\t\t"

            "fontsize = 20;\n\t\t"
            "fontcolor = black;\n\t\t"
            "label = \"Struct List   #%zu\";\n\n\t\t"

            "data -> head -> tail -> last_insert;\n\t"
        "}\n\t"
    "//------------------------------------------------------------------------------------------------------------------\n"
    "}\n", list -> head, list -> head -> next, list -> head -> data, list -> head -> prev,
           list -> tail, list -> tail -> next, list -> tail -> data, list -> tail -> prev,
           list -> last_insert, list -> last_insert -> next, list -> last_insert -> data, list -> last_insert -> prev,
           list, list -> capacity, list -> node_array, list -> node_array + list -> capacity - 1, graph_dump_counter);

    return NO_ERROR;
}
//--------------------------------------------------------------
