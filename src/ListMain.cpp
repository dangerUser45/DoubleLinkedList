#include <ListGeneral.h>
#include <ListCtorDtor.h>
#include <ListToolFunctions.h>
#include <ListDump.h>

#include <stdio.h>

//--------------------------------------------------------------
int main ()
{
    List list = {}; CtorListCommon (&list);
    ListDump (&list); getchar ();

    InsertTail (&list, 777); ListDump (&list);
    InsertTail (&list, 666); ListDump (&list);
    InsertTail (&list, 555); ListDump (&list);
    //InsertTail (&list, 444); ListDump (&list);
    //InsertTail (&list, 333); ListDump (&list);

    InsertData (&list, &(list.node_array[0]), 51); ListDump (&list);
    InsertData (&list, &(list.node_array[1]), 61); ListDump (&list);
    InsertData (&list, &(list.node_array[2]), 71); ListDump (&list);
    InsertData (&list, &(list.node_array[3]), 81); ListDump (&list);
    InsertData (&list, &(list.node_array[9000]), 91); ListDump (&list); getchar ();

    InsertAfter (&list, 123, &(list.node_array[2])); ListDump (&list);
    ListGraphDump (&list);

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

