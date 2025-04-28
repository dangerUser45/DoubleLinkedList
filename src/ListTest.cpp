#include <ListGeneral.h>
#include <ListCtorDtor.h>
#include <ListToolFunctions.h>
#include <ListDump.h>

extern FILE* list_log_file;
//--------------------------------------------------------------
int main ()
{
    List* list = CtorListCommon ();
    ListDump (list);
    ListGraphDump (list);

    ListInsertTail (list, 111); ListDump (list);ListGraphDump (list);
    ListInsertTail (list, 222); ListDump (list); ListGraphDump (list);
    ListInsertTail (list, 333); ListDump (list); ListGraphDump (list);
    ListInsertTail (list, 443); ListDump (list); ListGraphDump (list);
    ListInsertData (list, 0, 10);

    ListInsertTail (list, 555); ListDump (list); ListGraphDump (list);

    ListInsertAfter (list, 2,  400); ListDump (list);  ListGraphDump (list);
    ListInsertBelow (list, 0, -999); ListDump (list); ListGraphDump (list);

    ListInsertBelow (list, 6, 777); ListDump (list); ListGraphDump (list);
    ListInsertData  (list, 7, 888); ListDump (list); ListGraphDump (list);
    ListInsertTail (list, 5410);ListDump (list); ListGraphDump (list);

    DtorListCommon (list);
}
//--------------------------------------------------------------
