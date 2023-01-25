#ifndef PIXEL_ECS_H
#define PIXEL_ECS_H
#include <stdio.h>
#include "pixel/pixel.h"
#include "flecs/flecs.h"

// Componentes globales
typedef struct
{
    char *name;
    int64_t id;
} ComponentInfo;

typedef struct
{
    transform_t transform;
} ComponentSceneTransform;

// func
void pEcs_Init(void);
void pEcs_Progress(void);

ecs_entity_t pEcs_EntityLookupByName(const char *id_name);
ecs_query_t *pEcs_Query(const ecs_query_desc_t *query);
void pEcs_QueryFree(ecs_query_t *query_t);
ecs_iter_t pEcs_QueryIter(ecs_query_t *query_t);
bool pEcs_QueryIterNext(ecs_iter_t *it);

ecs_entity_t pEcs_EntityRoot(void);
ecs_entity_t pEcs_EntityNew(void);
ecs_entity_t pEcs_EntityEmptyNew(void);
ecs_entity_t pEcs_EntityClone(ecs_entity_t entity);
void pEcs_EntityDelete(ecs_entity_t entity);

void pEcs_EntitySetParent(ecs_entity_t parent, ecs_entity_t entity);
ecs_entity_t pEcs_EntityGetParent(ecs_entity_t entity);
bool pEcs_EntityHasDisabled(ecs_entity_t entity);
bool pEcs_EntityIsValid(ecs_entity_t entity);
bool pEcs_EntityIsParent(ecs_entity_t entity);

ecs_iter_t pEcs_EntityGetChildren(ecs_entity_t entity);
bool pEcs_EntityChildrenNext(ecs_iter_t *it);

void pEcs_EntitySetName(ecs_entity_t entity, const char *name);
const char *pEcs_EntityGetName(ecs_entity_t entity);

const void *pEcs_ComponentGetByName(ecs_entity_t entity, const char *component);

#endif // PIXEL_ECS_H