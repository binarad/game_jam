#include "button.h"
#include "raylib.h"
#include "rutils.h"
#include "gui/gui.h"
Button::Button(Rectangle btn_bounds, Color btn_color, Color text_color, const std::string &btn_label) : m_bounds(btn_bounds), color(btn_color), label_color(text_color), m_label(btn_label)
{
}

void Button::Draw()
{
    DrawRectangleRec(wr_rect(m_bounds), color);
    text_draw_aligned(m_label, FontSize::Medium, label_color, wr_rect(m_bounds), TextAlignment::AllCenter);
}
bool Button::Hover(Vector2 mouse_pos)
{
    if (CheckCollisionPointRec(mouse_pos, wr_rect(m_bounds)))
    {
        return true;
        // is_Hovered = true;
    }
    return false;
    // is_Hovered = false;
}

bool Button::Click(Vector2 mouse_pos)
{
    if (CheckCollisionPointRec(mouse_pos, m_bounds) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        return true;
        // is_Pressed = true;
    }

    return false;
    // is_Pressed = false;
}