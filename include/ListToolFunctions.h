#pragma once

#include <ListGeneral.h>
#include <ListErrors.h>

//--------------------------------------------------------------
LIST_ERROR ListCheckOverFlow (List* list);

LIST_ERROR ListInsertHead  (List* list, TYPE_DATA data);
LIST_ERROR ListInsertTail  (List* list, TYPE_DATA data);

LIST_ERROR ListInsertAfter (List* list, TYPE_DATA data, list_node* node);
LIST_ERROR ListInsertBelow (List* list, TYPE_DATA data, list_node* node);

LIST_ERROR ListInsertData  (List* list, list_node* node, TYPE_DATA data);

LIST_ERROR ListFindData (List* list, TYPE_DATA data, list_node** dest);
LIST_ERROR ListFindIndex   (List* list, list_node* searched_node, size_t* dest);
LIST_ERROR ListFindNode (List* list, size_t index, list_node** dest);

