#ifndef PIXEL_ECS_H
#define PIXEL_ECS_H
#include <stdio.h>
#include "flecs/flecs.h"
#include "pixel/pixel.h"
#include "pixel/pixel-meta-struct.h"

#define pEcs_EntitySet(entity, component, ...) \
    ecs_set_id(pEcs_World(), entity, component_id(component), sizeof(component), &(component)__VA_ARGS__)

#define pEcs_EntityGet(entity, component) \
    ecs_get_id(pEcs_World(), entity, component_id(component));

// func
void pEcs_Init(void);
void pEcs_Progress(void);

ecs_world_t *pEcs_World(void);

ecs_entity_t pEcs_LookupByName(const char *id_name);
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
void pEcs_EntitySetParentUnSafe(ecs_entity_t parent, ecs_entity_t entity);
ecs_entity_t pEcs_EntityGetParent(ecs_entity_t entity);
bool pEcs_EntityHasDisabled(ecs_entity_t entity);
bool pEcs_EntityIsValid(ecs_entity_t entity);
bool pEcs_EntityIsParent(ecs_entity_t entity);
const ecs_type_t *pEcs_EntityGetType(ecs_entity_t entity);

ecs_iter_t pEcs_EntityGetChildren(ecs_entity_t entity);
bool pEcs_EntityChildrenNext(ecs_iter_t *it);

void pEcs_EntitySetName(ecs_entity_t entity, const char *name);
const char *pEcs_EntityGetName(ecs_entity_t entity);

const void *pEcs_ComponentGetByName(ecs_entity_t entity, const char *component);
void pEcsComponent_SetEmptyByString(ecs_entity_t entity, const char *component);

#endif // PIXEL_ECS_H