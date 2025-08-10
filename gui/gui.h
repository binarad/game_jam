#ifndef _GUI_H_
#define _GUI_H_

#include "raylib.h"
#include "../rutils.h" 
#include <map>
#include <string>

void gui_init();
void gui_deinit();


enum class FontSize {
    VerySmall,
    Small,
    Medium,
    Big,
    Bigger,
    HUGE
};

// Debug draw all font sizes
void fonts_debug_draw();


enum class TextAlignment {
    AllCenter = 0,
    Right     = 1,
    Left      = 2,
    Top       = 4,
    Bottom    = 8
};

inline TextAlignment operator|(TextAlignment a, TextAlignment b) {
    return static_cast<TextAlignment>(
        static_cast<unsigned int>(a) | static_cast<unsigned int>(b)
    );
}

inline TextAlignment operator&(TextAlignment a, TextAlignment b) {
    return static_cast<TextAlignment>(
        static_cast<unsigned int>(a) & static_cast<unsigned int>(b)
    );
}

struct Text {
    std::string str;
    FontSize font_size;
    Color color;
    Vector2 pos;
};

// Draw text using its font and position
void text_draw(const Text &text);

// Set text position inside bounds based on alignment flags
void text_init_pos_by_alignment(Text &text, const Rectangle &bounds, TextAlignment alignment);

// Quick helper to make a Text struct
Text text_init(const std::string &str, FontSize font_size, Color color, Vector2 pos);

// Draw text inside bounds with alignment
void text_draw_aligned(const std::string &str, FontSize font_size, Color color,
                       const Rectangle &bounds, TextAlignment alignment);


#endif