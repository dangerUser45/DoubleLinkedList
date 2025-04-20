#include <stdlib.h>
#include <stdio.h>

#include <ListGeneral.h>
#include <ListConsts.h>
#include <ListErrors.h>
#include <ListDump.h>

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
    ListCreateDotText (list);

    int result = system ("dot -Tsvg dump/Graphviz_dot/ListGraphviz.txt -o dump/Graphviz_dot/images/img1.svg");
    if (result != 0)
    {
        fprintf (stdout, RED "ERROR in %s: %d line: system (): code error = %d\n" RESET, __FILE__, __LINE__, result);
        fflush (stdout);
    }

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

    fprintf (list_log_file, ""
    "<img src = \"../dump/Graphviz_dot/images/img1.svg\" class = \"center-horizontally\">\n"
    );

    return NO_ERROR;
}
//--------------------------------------------------------------
LIST_ERROR ListCreateDotText (List* list)
{
    fprintf (list_graphviz_file, ""

    "digraph\n"
    "{\n\t"
        "rankdir = LR;\n\n\t"

        "bgcolor   = \"" BACKGROUND_COLOR "\";  // Цвет фона - светло-синий\n\t"
        "fontcolor = \"black\";    // Цвет текста\n\n\t"

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
                "{\n\t\t\t"
                    "node_%zu_sort [label = \"address = %p | next: %p | data: %" TYPE_SPECIFIER " | prev: %p\"];\n\t\t\t"
                    "label = \"%zu\";\n\t\t"
                "}\n\n\t\t", i, i, node, node -> next, node -> data, node -> prev, i);

                node = node -> next;
            }

            fprintf (list_graphviz_file,""
            "fontsize = \"20\";\n\t\t"
            "fontcolor = black;\n\t\t"
            "label = \"Node array sort\";\n\t\t"
            "color =  \"" BACKGROUND_COLOR "\";\n\t\t");

            for (size_t i = 0; i < delta; ++i)
                fprintf (list_graphviz_file, "node_%zu_sort -> node_%zu_sort;\n\t\t", i, i + 1);

            fprintf (list_graphviz_file, "node_%zu_sort -> node_%zu_sort;\n\n\t\t", delta, (size_t)0);

            fprintf (list_graphviz_file,""
            "edge [color = red];\n\t\t");

            for (size_t i = delta, j = 0; j < capacity - 1; --i, ++j)
                fprintf (list_graphviz_file, "node_%zu_sort -> node_%zu_sort;", i, i - 1);

            fprintf (list_graphviz_file, "node_%zu_sort -> node_%zu_sort;\n\n\t\t", (size_t)0, delta);

    fprintf (list_graphviz_file, "\n\t}\n\n\t"
    "//------------------------------------------------------------------------------------------------------------------\n\t"
        "subgraph cluster_node_array_unsort\n\t" //NOTE do in an unsorted array, mapping as in a node array located in memory
        "{\n\t\t"
            "node [shape = Mrecord, style = filled, color = black, fillcolor = \"" NODE_ARRAY_COLOR "\"];\n\t\t"
            "edge [color = black];\n\t\t"
            "color = \"" BACKGROUND_COLOR "\";\n\n\t\t"

            "subgraph cluster_node_1\n\t\t"
            "{\n\t\t\t"
                "node_1 [label = \"\\n\\nUNINITIALISED  DATA\\n\\n\\n\\n\", style = \"filled\", fillcolor = white, color = black, fontcolor = black]\n\t\t\t"
                "//node_1 [label = \"address = 0x1232131233 | next: 0x12321323 | data: 666 | prev: 0x3324324\"];\n\t\t\t"
                "label = \"1\";\n\t\t"
            "}\n\n\t\t"

            "subgraph cluster_node_2\n\t\t"
            "{\n\t\t\t"
                "node_2 [label = \"address = 0x1232131233 | next: 0x12321323 | data: 777 | prev: 0x3324324\"];\n\t\t\t"
                "label = \"2\";\n\t\t"
            "}\n\n\t\t"

            "subgraph cluster_node_3\n\t\t"
            "{\n\t\t\t"
                "node_3 [label = \"address = 0x1232131233 | next: 0x12321323 | data: 888 | prev: 0x3324324\"];\n\t\t\t"
                "label = \"3\";\n\t\t"
            "}\n\n\t\t"

            "subgraph cluster_node_4\n\t\t"
            "{\n\t\t\t"
                "node_4 [label = \"address = 0x1232131233 | next: 0x12321323 | data: 999 | prev: 0x3324324\"];\n\t\t\t"
                "label = \"4\";\n\t\t"
            "}\n\n\t\t"

            "subgraph cluster_node_5\n\t\t"
            "{\n\t\t\t"
                "node_5 [label = \"address = 0x1232131233 | next: 0x12321323 | data: 000 | prev: 0x3324324\"];\n\t\t\t"
                "label = \"5\";\n\t\t"
            "}\n\n\t\t"

            "fontsize = \"20\";\n\t\t"
            "fontcolor = black;"
            "label = \"Node array\";"
            "color = \"" BACKGROUND_COLOR "\";\n\t\t"
            "node_1 -> node_2 -> node_3 -> node_4 -> node_5;\n\t"
        "}\n\n\t");
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

            "data [label = \"list pointer = %p | list capacity = %zu | list node array = %p\"]\n\n\t\t"

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
            "label = \"                                           Struct List\";\n\n\t\t"

            "data -> head -> tail -> last_insert;\n\t"
        "}\n\t"
    "//------------------------------------------------------------------------------------------------------------------\n"
    "}\n", list -> head, list -> head -> next, list -> head -> data, list -> head -> prev,
           list -> tail, list -> tail -> next, list -> tail -> data, list -> tail -> prev,
           list -> last_insert, list -> last_insert -> next, list -> last_insert -> data, list -> last_insert -> prev,
           list, list -> capacity, list -> node_array);
    fflush (list_graphviz_file);

    return NO_ERROR;
}
//--------------------------------------------------------------
