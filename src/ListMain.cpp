#include <ListGeneral.h>
#include <ListCtorDtor.h>
#include <ListToolFunctions.h>
#include <ListDump.h>

extern FILE* list_log_file;
//--------------------------------------------------------------
int main ()
{
    List list = {}; CtorListCommon (&list);
    ListGraphDump (&list);

    ListInsertTail (&list, 111); ListGraphDump (&list);
    ListInsertTail (&list, 222); ListGraphDump (&list);
    ListInsertTail (&list, 333); ListDump (&list); ListGraphDump (&list);
    ListInsertTail (&list, 443); ListDump (&list); ListGraphDump (&list);

    ListInsertTail (&list, 555); ListGraphDump (&list);

    ListInsertAfter (&list, 400, &(list.node_array[2])); ListGraphDump (&list);
    ListInsertBelow (&list, -999, list.head); ListGraphDump (&list);

//     ListInsertData (&list, &(list.node_array[0]), 51); ListGraphDump (&list);

//     list_node* dest_find_data = 0;
//     ListFindData (&list, 443, &dest_find_data);
//
//     size_t index = 0;
//     ListFindIndex (&list, list.tail, &index);
//
//     list_node* dest_find_node = 0;
//     ListFindNode (&list, index, &dest_find_node);
//
//     printf ("dest_find_data = %p\n"
//             "index = %zu\n"
//             "dest_find_node = %p\n", dest_find_data, index, dest_find_node);

    //InsertAfter (&list, 600, &(list.node_array[0])); ListDump (&list);
//     InsertTail (&list, 222); ListDump (&list);

//     InsertHead (&list, 222);
//     InsertHead (&list, 111);
//
//     //ListGraphDump();
//
//     InsertTail (&list, 1);
//     InsertTail (&list, 2);
//     InsertTail (&list, 3);
//     InsertTail (&list, 4);
//     InsertTail (&list, 5);
//     InsertTail (&list, 6);
//     InsertTail (&list, 7);
//     InsertTail (&list, 8);
//     InsertTail (&list, 9);
//     InsertTail (&list, 10);
//     InsertTail (&list, 11);
//     InsertTail (&list, 12);

    DtorListCommon (&list);
}
//--------------------------------------------------------------

