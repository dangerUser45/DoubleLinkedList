#include <ListGeneral.h>
#include <ListCtorDtor.h>
#include <ListToolFunctions.h>
#include <ListDump.h>

#include <stdio.h>

//--------------------------------------------------------------
int main ()
{
    DBG(printf ("check\n");)
    List list = {}; CtorListCommon (&list);
    ListDump (&list);

    InsertHead (&list, 777);
    InsertHead (&list, 666);
    InsertHead (&list, 555);

    ListDump (&list);

//     InsertHead (&list, 444);
//     InsertHead (&list, 333);
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

