#include "ui-docked-hierarchy.h"
#include "pixel/pixel.h"
#include "pixel/pixel-ecs.h"
#include "single-file.h"

struct hierarchy
{
    ecs_entity_t drag_entity;

    struct
    {
        ecs_entity_t scene_transform;
    } component;
    bool broot_has_entity;
    bool bmenu_context_open;

} hierarchy;

static EditorSingleFile *single;

// TreeNode SelectedFrags
static ImGuiTreeNodeFlags flag_selected_default = ImGuiSelectableFlags_None | ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_FramePadding;

static void hierarchy_other_draw(const char *name, ecs_entity_t e);
static void hierarchy_show_entitys_world(ecs_entity_t t);
static void hierarchy_popup_menu_open_with_mouse_button_an_entity(const char *name, ecs_entity_t e);
static void hierarchy_popup_menu_open_button_pluss(void);
static void hierarchy_drag_and_drop(ecs_entity_t entity);
static void hierarchy_entity_selected_duplicate(void);
static void hierarchy_entity_selected_remove(void);
static void hierarchy_entity_add(void);

void editor_gui_hierarchy_init(void)
{
    hierarchy.component.scene_transform = pEcs_LookupByName("ComponentSceneTransform");

    // -------------------------------------------
    // Single-File: Comparte dantos unicos entre modulos
    // -------------------------------------------
    single = eSingleFile_Get();

    // -------------------------------------------
    // Seleccionamos el entity-root por defecto
    // -------------------------------------------
    // single->entity_selected = pEcs_EntityRoot();
}

void editor_gui_hierarchy_draw(void)
{
    if (igBegin("Scene Hierarchy", false, ImGuiWindowFlags_NoMove))
    {
        igSameLine(0, 0);
        if (igSmallButton("+"))
        {
            // igOpenPopup_Str("hierarchy-pme-button-pluss", 0);
            hierarchy_entity_add();
        }
        if (single->entity_selected != pEcs_EntityRoot())
        {
            igSameLine(0, 5);
            if (igSmallButton("Duplicate"))
            {
                hierarchy_entity_selected_duplicate();
            }
            igSameLine(0, 5);
            if (igSmallButton("Delete"))
            {
                hierarchy_entity_selected_remove();
            }
        }

        igSeparator();

        /**
         *
         * Cargamos la lista de entidades que se encuentran en el root-entity
         */
        hierarchy_show_entitys_world(pEcs_EntityRoot());

        /**
         *
         * Cargamos la lista de entidades que se encuentran en el root-entity
         */
        hierarchy_popup_menu_open_button_pluss();
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

        bool bentity_selected = single->entity_selected == entity ? true : false;
        bool bIsParent = pEcs_EntityIsParent(entity);

        hierarchy.broot_has_entity = pEcs_EntityRoot() == entity;

        if (bIsParent == false)
        {
            igPushID_Int((int)entity);
            {
                if (igSelectable_Bool(entity_name, bentity_selected, flag_selected_default, (ImVec2){0}))
                {
                    single->entity_selected = entity;
                }
                hierarchy_other_draw(entity_name, entity);
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

            igPushID_Int((int)entity);
            bool bopened_treenode = igTreeNodeEx_Str(entity_name, flags);
            {
                if (igIsItemClicked(ImGuiMouseButton_Left))
                {
                    single->entity_selected = entity;
                }

                hierarchy_other_draw(entity_name, entity);

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
            igPopID();
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
 * hierarchy_popup_menu_open_button_pluss
 *
 * Al presionar el boton '+ Entity', mostramos este popups
 *
 */
void hierarchy_popup_menu_open_button_pluss(void)
{
    if (igBeginPopupContextItem("hierarchy-pme-button-pluss", ImGuiPopupFlags_MouseButtonRight))
    {
        if (igSelectable_Bool("+ Entity", false, 0, (ImVec2){0, 0}))
        {
            ecs_entity_t t = pEcs_EntityNew();
            ecs_entity_t parent = (single->entity_selected > 0 ? single->entity_selected : pEcs_EntityRoot());
            pEcs_EntitySetParent(parent, t);
        }
        igSeparator();
        // if (igBeginMenu("2D", true))
        {
            if (igSelectable_Bool("Sprite", false, 0, (ImVec2){0, 0}))
            {
            }
            if (igSelectable_Bool("Animated Sprite", false, 0, (ImVec2){0, 0}))
            {
            }
            // igEndMenu();
        }
        igEndPopup();
    }
}

/**
 *
 * hierarchy_popup_menu_open_with_mouse_button_an_entity
 *
 * Al presionar clic derecho arriba de una entity
 *
 */
void hierarchy_popup_menu_open_with_mouse_button_an_entity(const char *name, ecs_entity_t e)
{
    if (igIsItemClicked(ImGuiMouseButton_Right))
    {
        igOpenPopup_Str("hierarchy-pmes", 0);
    }

    if (igBeginPopupContextItem("hierarchy-pmes", ImGuiPopupFlags_MouseButtonRight))
    {
        single->entity_selected = e;

        if (igSelectable_Bool("+ New Entity", false, 0, (ImVec2){0, 0}))
        {
        }

        igSeparator();
        if (igSelectable_Bool("+ Add Component", false, 0, (ImVec2){0, 0}))
        {
        }

        if (single->entity_selected > 0 && !hierarchy.broot_has_entity)
        {
            igSeparator();
            if (igSelectable_Bool("Duplicate", false, 0, (ImVec2){0, 0}))
            {
                hierarchy_entity_selected_duplicate();
            }
            igSeparator();
            if (igSelectable_Bool("Delete", false, 0, (ImVec2){0, 0}))
            {
                hierarchy_entity_selected_remove();
            }
        }
        igEndPopup();
    }
}

void hierarchy_other_draw(const char *name, ecs_entity_t e)
{
    hierarchy_drag_and_drop(e);
    hierarchy_popup_menu_open_with_mouse_button_an_entity(name, e);
}

void hierarchy_entity_selected_duplicate(void)
{
    if (pEcs_EntityIsValid(single->entity_selected))
    {
        pEcs_EntityClone(single->entity_selected);
    }
}

void hierarchy_entity_selected_remove(void)
{
    if (pEcs_EntityIsValid(single->entity_selected))
    {
        pEcs_EntityDelete(single->entity_selected);
        single->entity_selected = pEcs_EntityRoot();
    }
}

void hierarchy_entity_add(void)
{
    ecs_entity_t t = pEcs_EntityNew();
    ecs_entity_t parent = (single->entity_selected > 0 ? single->entity_selected : pEcs_EntityRoot());
    pEcs_EntitySetParent(parent, t);
}
