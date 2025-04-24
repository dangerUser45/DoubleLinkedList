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

    DtorListCommon (&list);
}
//--------------------------------------------------------------

