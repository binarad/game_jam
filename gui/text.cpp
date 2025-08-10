#include "gui_private.h"
#include <cmath>

void text_draw(const Text &text) {
    Font font = _get_font(text.font_size);
    DrawTextEx(font, text.str.c_str(), text.pos, static_cast<float>(font.baseSize),
               FONTS_SPACING, text.color);
}

bool _is_eq_alignment(TextAlignment alignment, TextAlignment flag) {
    unsigned int align_val = static_cast<unsigned int>(alignment);
    unsigned int flag_val  = static_cast<unsigned int>(flag);
    return (align_val & flag_val) == flag_val;
}


void text_init_pos_by_alignment(Text &text, const Rectangle &bounds, TextAlignment alignment) {
    Font font = _get_font(text.font_size);
    Vector2 text_size = MeasureTextEx(font, text.str.c_str(),
                                      static_cast<float>(font.baseSize), FONTS_SPACING);

    Vector2 text_pos = rect_calc_center(bounds);
    text_pos.x -= text_size.x / 2;
    text_pos.y -= text_size.y / 2;

    if (_is_eq_alignment(alignment, TextAlignment::Right)) {
        text_pos.x = bounds.x + bounds.width - text_size.x;
    } else if (_is_eq_alignment(alignment, TextAlignment::Left)) {
        text_pos.x = bounds.x;
    }

    if (_is_eq_alignment(alignment, TextAlignment::Top)) {
        text_pos.y = bounds.y;
    } else if (_is_eq_alignment(alignment, TextAlignment::Bottom)) {
        text_pos.y = bounds.y + bounds.height - text_size.y;
    }

    text.pos = text_pos;
}

Text text_init(const std::string &str, FontSize font_size, Color color, Vector2 pos) {
    return {str, font_size, color, pos};
}

void text_draw_aligned(const std::string &str, FontSize font_size, Color color,
                       const Rectangle &bounds, TextAlignment alignment) {
    Text text{str, font_size, color, {0, 0}};
    text_init_pos_by_alignment(text, bounds, alignment);
    text_draw(text);
}

