#include <ListGeneral.h>
#include <ListErrors.h>

//--------------------------------------------------------------
LIST_ERROR CheckOverFlow (List* list);

LIST_ERROR InsertHead (List* list, TYPE_DATA data);
LIST_ERROR InsertTail (List* list, TYPE_DATA data);

LIST_ERROR InsertAfter (List* list, TYPE_DATA data, list_node* node);
LIST_ERROR InsertBelow (List* list, TYPE_DATA data, list_node* node);

LIST_ERROR InsertData (List* list, list_node* node, TYPE_DATA data);
