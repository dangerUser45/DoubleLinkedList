#pragma once

#include <ListGeneral.h>
#include <ListErrors.h>

LIST_ERROR ListDump (List* list);
LIST_ERROR ListGraphDump (List* list);

LIST_ERROR ListCreateDotText (List* list);

LIST_ERROR ListWriteIntro ();
LIST_ERROR ListWriteSort (List* list);
LIST_ERROR ListWriteUnsort (List* list);
LIST_ERROR ListWriteStructList (List* list);

LIST_ERROR CheckSysRetVal ();

LIST_ERROR ListPrintHtmlIntro ();
LIST_ERROR ListAddImages ();

