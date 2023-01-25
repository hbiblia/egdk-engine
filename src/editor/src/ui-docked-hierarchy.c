#include "ui-docked-hierarchy.h"
#include "pixel/pixel.h"
#include "pixel/pixel-ecs.h"

struct hierarchy
{
    ecs_entity_t selected_entity;
    ecs_entity_t drag_entity;

    struct
    {
        ecs_entity_t scene_transform;
    } component;
    bool broot_has_entity;

} hierarchy;

// Test Test

// TreeNode SelectedFrags
static ImGuiTreeNodeFlags flag_selected_default = ImGuiSelectableFlags_None | ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_FramePadding;

static void hierarchy_menu_context_open(const char *name, ecs_entity_t e);
static void hierarchy_show_entitys_world(ecs_entity_t t);

void editor_gui_hierarchy_init(void)
{
    hierarchy.component.scene_transform = pEcs_EntityLookupByName("ComponentSceneTransform");
}

void editor_gui_hierarchy_draw(void)
{
    if (igBegin("Scene Hierarchy", false, ImGuiWindowFlags_NoMove))
    {
        igSameLine(0, 0);
        if (igSmallButton("New entity"))
        {
            ecs_entity_t t = pEcs_EntityNew();

            ecs_entity_t parent = (hierarchy.selected_entity > 0 ? hierarchy.selected_entity : pEcs_EntityRoot());
            pEcs_EntitySetParent(parent, t);
        }
        igSeparator();

        /**
         *
         * Cargamos la lista de entidades que se encuentran en el root-entity
         */
        hierarchy_show_entitys_world(pEcs_EntityRoot());
    }
    igEnd();
}

/**
 *
 * Cargamos la lista de entidades que se encuentran en el root-entity
 */
void hierarchy_show_entitys_world(ecs_entity_t entity)
{
    if (pEcs_EntityIsValid(entity))
    {
        const char *entity_name = pEcs_EntityGetName(entity);

        bool bentity_selected = hierarchy.selected_entity == entity ? true : false;
        bool bIsParent = pEcs_EntityIsParent(entity);

        hierarchy.broot_has_entity = pEcs_EntityRoot() == entity;

        if (bIsParent == false)
        {
            igPushID_Int((int)entity);
            {
                if (igSelectable_Bool(entity_name, bentity_selected, flag_selected_default, (ImVec2){0}))
                {
                    hierarchy.selected_entity = entity;
                }
                hierarchy_menu_context_open(entity_name, entity);
            }
            igPopID();
        }
        else
        {
            ImGuiTreeNodeFlags flags = flag_selected_default;
            flags |= bentity_selected ? ImGuiTreeNodeFlags_Selected : ImGuiTreeNodeFlags_OpenOnArrow;

            // Siempre que sea el Root estara abrido.
            if (hierarchy.broot_has_entity)
                flags |= ImGuiTreeNodeFlags_DefaultOpen;

            bool bopened_treenode = igTreeNodeEx_Str(entity_name, flags);
            {
                if (igIsItemClicked(ImGuiMouseButton_Left))
                {
                    hierarchy.selected_entity = entity;
                }

                hierarchy_menu_context_open(entity_name, entity);

                if (bopened_treenode)
                {
                    ecs_iter_t it = pEcs_EntityGetChildren(entity);
                    while (pEcs_EntityChildrenNext(&it))
                    {
                        for (int i = 0; i < it.count; i++)
                        {
                            hierarchy_show_entitys_world(it.entities[i]);
                        }
                    }
                    igTreePop();
                }
            }
        }
    }
}

/**
 *
 * MenuContext
 *
 * Cuando tenemos una entidad seleccionada podemos abrir este menuContext.
 *
 */
void hierarchy_drag_and_drop(ecs_entity_t entity)
{
    // --------------------------------------------
    // root no se puede draggear
    // hierarchy.broot_has_entity == false
    // --------------------------------------------
    if (hierarchy.broot_has_entity == false && igBeginDragDropSource(0))
    {
        hierarchy.drag_entity = entity;
        igSetDragDropPayload("hierarchy_entity_drag", NULL, 0, 0);
        igEndDragDropSource();
    }

    if (igBeginDragDropTarget())
    {
        ImGuiPayload *pay = igAcceptDragDropPayload("hierarchy_entity_drag", ImGuiDragDropFlags_SourceNoDisableHover);
        if (pay)
        {
            pEcs_EntitySetParent(entity, hierarchy.drag_entity);
            igEndDragDropTarget();
        }
    }
}

/**
 *
 * MenuContext
 *
 * Cuando tenemos una entidad seleccionada podemos abrir este menuContext.
 *
 */
void hierarchy_menu_context_open(const char *name, ecs_entity_t e)
{
    hierarchy_drag_and_drop(e);

    if (igIsItemClicked(ImGuiMouseButton_Right))
    {
        igOpenPopup_Str("hierarchy-menu-context", 0);
    }

    if (igBeginPopupContextItem("hierarchy-menu-context", ImGuiPopupFlags_MouseButtonRight))
    {
        hierarchy.selected_entity = e;

        if (igSelectable_Bool("+ New Entity", false, 0, (ImVec2){0, 0}))
        {
        }

        igSeparator();
        if (igSelectable_Bool("+ Add Component", false, 0, (ImVec2){0, 0}))
        {
        }

        if (hierarchy.selected_entity > 0 && !hierarchy.broot_has_entity)
        {
            igSeparator();
            if (igSelectable_Bool("Duplicate", false, 0, (ImVec2){0, 0}))
            {
                pEcs_EntityClone(hierarchy.selected_entity);
            }
            igSeparator();
            if (igSelectable_Bool("Delete", false, 0, (ImVec2){0, 0}))
            {
                pEcs_EntityDelete(hierarchy.selected_entity);
                hierarchy.selected_entity = pEcs_EntityRoot();
            }
        }
        igEndPopup();
    }
}