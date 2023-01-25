#ifndef SINGLE_FILE_H
#define SINGLE_FILE_H
#include <stdio.h>
#include "pixel/pixel-ecs.h"

#define MAX_MULTI_ENTITY_SELECTED 1

typedef struct {
    ecs_entity_t entity_selected;
}EditorSingleFile;

void eSingleFile_Init(void);
void eSingleFile_Shutdown(void);

EditorSingleFile *eSingleFile_Get(void);

#endif // SINGLE_FILE_H