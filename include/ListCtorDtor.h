#pragma once

#include <stdio.h>

#include <ListGeneral.h>
#include <ListErrors.h>

LIST_ERROR CtorListCommon (List* list);
LIST_ERROR DtorListCommon (List* list);

FILE* OpenFile (const char *__restrict filename, const char *__restrict modes);
LIST_ERROR CloseFile (FILE* file);
