#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "raylib.h"
#include <string>
class Button
{
private:
    Rectangle m_bounds;
    std::string m_label;
    // bool is_Hovered;
    // bool is_Pressed;

public:
    Color color;
    Color label_color;

    Button(Rectangle bounds, Color color, Color text_color, const std::string &btn_label);

    void draw();
    bool mouse_hover(Vector2 mouse_pos);
    bool mouse_click(Vector2 mouse_pos);

    // ~Button();
};

#endif