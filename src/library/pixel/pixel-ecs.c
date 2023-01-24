
/**
 *
 * pixelEcs
 *
 * Se basa en flecs-ecs, pixelEcs solo hace que sea
 * mas facil de utilizar dique!
 *
 *
 */

#include "pixel-ecs.h"
#include "string_fn.h"

static struct PixelEcs
{
    ecs_entity_t root;
    ecs_world_t *world;
} pixel;

/***
 *
 *  PixelEcs
 *
 */

ECS_COMPONENT_DECLARE(ComponentSceneTransform);
ECS_COMPONENT_DECLARE(ComponentInfo);

void pEcs_Init(void)
{
    pixel.world = ecs_init();

    ECS_COMPONENT_DEFINE(pixel.world, ComponentSceneTransform);
    ECS_COMPONENT_DEFINE(pixel.world, ComponentInfo);

    // Unico Root en la escena
    pixel.root = pEcs_EntityNew();
    ecs_set_name(pixel.world, pixel.root, "Root");
    pEcs_EntitySetName(pixel.root, "Root");
}

void pEcs_Progress(void)
{
    ecs_progress(pixel.world, 0);
}

/***
 *
 *  PixelQuery
 *
 */

ecs_entity_t pEcs_EntityLookupByName(const char *id_name)
{
    return ecs_lookup(pixel.world, id_name);
}

ecs_query_t *pEcs_Query(const ecs_query_desc_t *query)
{
    return ecs_query_init(pixel.world, query);
}

void pEcs_QueryFree(ecs_query_t *query_t)
{
    ecs_query_fini(query_t);
}

ecs_iter_t pEcs_QueryIter(ecs_query_t *query_t)
{
    return ecs_query_iter(pixel.world, query_t);
}

bool pEcs_QueryIterNext(ecs_iter_t *it)
{
    return ecs_query_next(it);
}

/***
 *
 *  PixelEntity
 *
 */

ecs_entity_t pEcs_EntityNew(void)
{
    ecs_entity_t e = pEcs_EntityEmptyNew();
    ecs_set(pixel.world, e, ComponentInfo, {.name = StringPrintf("Entity%u", e)});
    ecs_set(pixel.world, e, ComponentSceneTransform, {.transform = {0}});

    return e;
}

ecs_entity_t pEcs_EntityEmptyNew(void)
{
    return ecs_new_id(pixel.world);
}

ecs_entity_t pEcs_EntityClone(ecs_entity_t entity)
{
    ecs_entity_t clone = ecs_clone(pixel.world, 0, entity, true);
    pEcs_EntitySetName(clone, StringPrintf("Entity%u_%u+", entity, clone));

    // Verificamos si es padre para copiar los hijos
    if (pEcs_EntityIsParent(entity))
    {
        ecs_query_t *query = pEcs_Query(&(ecs_query_desc_t){
            .filter.terms = {
                {.id = ecs_id(ComponentSceneTransform), .inout = EcsIn},
                {.id = pEcs_EntityGetParent(entity)},
                {.id = EcsDisabled, .oper = EcsOptional},
            },
        });

        ecs_iter_t it = pEcs_QueryIter(query);
        while (pEcs_QueryIterNext(&it))
        {
            for (int i = 0; i < it.count; i++)
            {
                ecs_entity_t child_clone = pEcs_EntityClone(it.entities[i]);
                pEcs_EntitySetParent(clone, child_clone);
            }
        }
        pEcs_QueryFree(query);
    }

    return clone;
}

void pEcs_EntityDelete(ecs_entity_t entity)
{
    if (pEcs_EntityIsValid(entity))
    {
        ecs_delete(pixel.world, entity);
    }
}

void pEcs_Set(ecs_entity_t entity)
{
}

ecs_entity_t pEcs_EntityRoot(void)
{
    return pixel.root;
}

void pEcs_EntitySetParent(ecs_entity_t parent, ecs_entity_t entity)
{
    ecs_add_pair(pixel.world, entity, EcsChildOf, parent);
}

ecs_entity_t pEcs_EntityGetParent(ecs_entity_t entity)
{
    return ecs_childof(entity);
}

bool pEcs_EntityHasDisabled(ecs_entity_t entity)
{
    return ecs_has_id(pixel.world, entity, EcsDisabled);
}

bool pEcs_EntityIsValid(ecs_entity_t entity)
{
    return ecs_is_valid(pixel.world, entity);
}

bool pEcs_EntityIsParent(ecs_entity_t entity)
{
    return ecs_count_id(pixel.world, ecs_pair(EcsChildOf, entity)) > 0 ? true : false;
}

// Las entidades tienen nombres unicos, no existe una entidad
// con el mismo nombre. Pero vamos a crear un component para
// guardar ese tipo de dato para que podamos tener entidades
// sin nombres y guardamos esos datos en un componente.
void pEcs_EntitySetName(ecs_entity_t entity, const char *name)
{
    ComponentInfo *info = ecs_get(pixel.world, entity, ComponentInfo);
    info->name = StringDup(name);
}

const char *pEcs_EntityGetName(ecs_entity_t entity)
{
    ComponentInfo *info = ecs_get(pixel.world, entity, ComponentInfo);
    return StringDup(info->name);
}

/***
 *
 *  PixelEntityComponent
 *
 */

ecs_entity_t pEcs_ComponentInit(ecs_entity_t entity_component)
{
    ecs_entity_t component;

    component = ecs_component_init(pixel.world,
                                   &(ecs_component_desc_t){
                                       .entity = entity_component,
                                   });

    return component;
}

const void *pEcs_ComponentGetByName(ecs_entity_t entity, const char *component)
{
    return ecs_get_id(pixel.world, entity, pEcs_EntityLookupByName(component));
}
