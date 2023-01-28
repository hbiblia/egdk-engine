
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
#include "pixel/pixel-components.h"
#include "utility/string_fn.h"

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

void pEcs_Init(void)
{
    pixel.world = ecs_init();

    pEscMetaStruct_Init(pixel.world);
    pEcsComponent_Init();

    // Unico Root en la escena
    pixel.root = pEcs_EntityNew();
    ecs_set_name(pixel.world, pixel.root, "Root");
    pEcs_EntitySetName(pixel.root, "Root");
}

void pEcs_Progress(void)
{
    ecs_progress(pixel.world, pWindow_DeltaTime());
}

ecs_world_t *pEcs_World(void)
{
    return pixel.world;
}

/***
 *
 *  PixelQuery
 *
 */

ecs_entity_t pEcs_LookupByName(const char *id_name)
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

    pEcs_EntitySet(e, entity_info_t, {
                                         .enable = true,
                                         .name = String("New Entity"),
                                         .scale = {1, 1},
                                         .rotation = 0,
                                         .position = {0, 0},
                                     });

    return e;
}

ecs_entity_t pEcs_EntityEmptyNew(void)
{
    return ecs_new_id(pixel.world);
}

void pEcs_EntitySetEnable(ecs_entity_t entity, bool enable)
{
    ecs_enable(pixel.world, entity, enable);
}

ecs_entity_t pEcs_EntityClone(ecs_entity_t entity)
{
    ecs_entity_t clone = ecs_clone(pixel.world, 0, entity, true);

    // FIX
    pEcs_EntitySetName(clone, pEcs_EntityGetName(entity));

    // ---------------------------------
    // Copiamos los hijos si tiene
    // ---------------------------------
    ecs_iter_t it = pEcs_EntityGetChildren(entity);
    while (pEcs_EntityChildrenNext(&it))
    {
        for (int i = 0; i < it.count; i++)
        {
            if (ecs_is_alive(pixel.world, it.entities[i]))
            {
                ecs_entity_t child_clone = pEcs_EntityClone(it.entities[i]);
                ecs_add_pair(pixel.world, child_clone, EcsChildOf, clone);
            }
        }
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

ecs_entity_t pEcs_EntityRoot(void)
{
    return pixel.root;
}

static bool pEcs_EntityHasParentTree(ecs_entity_t entity, ecs_entity_t parent)
{
    ecs_iter_t it = pEcs_EntityGetChildren(entity);
    while (pEcs_EntityChildrenNext(&it))
    {
        for (int i = 0; i < it.count; i++)
        {
            if (it.entities[i] == parent)
            {
                return true;
            }
            else
            {
                if (pEcs_EntityIsParent(it.entities[i]))
                {
                    return pEcs_EntityHasParentTree(it.entities[i], parent);
                }
            }
        }
    }
    return false;
}

void pEcs_EntitySetParentUnSafe(ecs_entity_t parent, ecs_entity_t entity)
{
    ecs_add_pair(pixel.world, entity, EcsChildOf, parent);
}

void pEcs_EntitySetParent(ecs_entity_t parent, ecs_entity_t entity)
{
    if (!pEcs_EntityHasParentTree(entity, parent))
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
    return (ecs_count_id(pixel.world, ecs_pair(EcsChildOf, entity)) > 0);
}

const ecs_type_t *pEcs_EntityGetType(ecs_entity_t entity)
{
    return ecs_get_type(pixel.world, entity);
}

ecs_iter_t pEcs_EntityGetChildren(ecs_entity_t entity)
{
    return ecs_children(pixel.world, entity);
}

bool pEcs_EntityChildrenNext(ecs_iter_t *it)
{
    return ecs_children_next(it);
}

void pEcs_EntitySetName(ecs_entity_t entity, const char *name)
{
    entity_info_t *info = pEcs_EntityGet(entity, entity_info_t);
    free(info->name);
    info->name = String(name);
}

const char *pEcs_EntityGetName(ecs_entity_t entity)
{
    entity_info_t info = *(entity_info_t *)pEcs_EntityGet(entity, entity_info_t);
    return String(info.name);
}

/***
 *
 *  PixelEntityComponent
 *
 */

const void *pEcs_ComponentGetByName(ecs_entity_t entity, const char *component)
{
    return ecs_get_id(pixel.world, entity, pEcs_LookupByName(component));
}

void pEcsComponent_SetEmptyByString(ecs_entity_t entity, const char *component)
{
    ecs_add_id(pEcs_World(), entity, pEcs_LookupByName(component));
}