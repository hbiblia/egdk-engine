#ifndef _PIXEL_GUI_H
#define _PIXEL_GUI_H
#include "pixel.h"

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui/cimgui.h"

#define MAX_INPUT_TEXT 32

#define pgInputText(label, buffer) igInputText(label, buffer, MAX_INPUT_TEXT, 0, NULL, NULL)
#define pgButton(label, width, height) igButton(label, (ImVec2){width, height})
#define pgButtonImage(id, texture, size_w, size_h) igImageButton(id, (void*)texture, (const ImVec2){size_w, size_h}, (ImVec2){0, 0}, (ImVec2){1, 1}, (ImVec4){0, 0, 0, 0}, (ImVec4){1, 1, 1, 1.0f})
#define pgSeparator() igSeparator()
#define pgBeginViewList(id, columnCount) igBeginTable(id, columnCount, ImGuiTableFlags_ScrollY, (ImVec2){0, 0}, 0.0f)
#define pgEndViewList() igEndTable()
#define pgBeginChildViewList(id) \
    igTableNextColumn();         \
    igPushID_Str(id)
#define pgEndChildViewList() igPopID()
#define pgTextWrap(...) igTextWrapped(__VA_ARGS__)

#define pgStyleColor(id, r, g, b, a) igPushStyleColor_Vec4(id, (ImVec4){r, g, b, a})
#define pgStyleColorClear igPopStyleColor

#endif