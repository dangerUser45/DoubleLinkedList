#pragma once

#include <ListGeneral.h>
#include <ListErrors.h>

LIST_ERROR ListDump (List* list);
LIST_ERROR ListGraphDump (List* list);
LIST_ERROR ListCreateDotText (List* list);
