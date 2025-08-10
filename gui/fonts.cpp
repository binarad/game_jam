// gui.cpp
#include "gui.h"
#include "gui_private.h"
#include <cassert>


std::map<FontSize, Font> _fonts;

// Map from FontSize to % of screen height
const std::map<FontSize, float> _font_to_percent = {
    {FontSize::VerySmall, 2.5f},
    {FontSize::Small,     3.0f},
    {FontSize::Medium,    4.0f},
    {FontSize::Big,       5.26f},
    {FontSize::Bigger,    7.0f},
    {FontSize::HUGE,      15.0f}
};

void _load_fonts() {
    _fonts.clear();
    _load_font(FontSize::VerySmall);
    _load_font(FontSize::Small);
    _load_font(FontSize::Medium);
    _load_font(FontSize::Big);
    _load_font(FontSize::Bigger);
    _load_font(FontSize::HUGE);
}

void _unload_fonts() {
    for (auto &kv : _fonts) {
        UnloadFont(kv.second);
    }
    _fonts.clear();
}

Font _get_font(FontSize size) {
    auto it = _fonts.find(size);
    assert(it != _fonts.end() && "Font not loaded");
    return it->second;
}

void _load_font(FontSize size) {
    int font_height = static_cast<int>(wr_y(_font_to_percent.at(size)));
    Font font = LoadFontEx("fonts/Rajdhani-SemiBold.ttf", font_height, nullptr, 0);
    SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);
    _fonts[size] = font;
}

void fonts_debug_draw() {
    Vector2 pos = {0, 0};

    DrawTextEx(_get_font(FontSize::VerySmall), "Very Small", pos, wr_y(_font_to_percent.at(FontSize::VerySmall)), FONTS_SPACING, GREEN);
    pos.y += 10;

    DrawTextEx(_get_font(FontSize::Small), "Small", pos, wr_y(_font_to_percent.at(FontSize::Small)), FONTS_SPACING, GREEN);
    pos.y += 15;

    DrawTextEx(_get_font(FontSize::Medium), "Medium", pos, wr_y(_font_to_percent.at(FontSize::Medium)), FONTS_SPACING, GREEN);
    pos.y += 20;

    DrawTextEx(_get_font(FontSize::Big), "Big", pos, wr_y(_font_to_percent.at(FontSize::Big)), FONTS_SPACING, GREEN);
    pos.y += 25;

    DrawTextEx(_get_font(FontSize::Bigger), "Bigger", pos, wr_y(_font_to_percent.at(FontSize::Bigger)), FONTS_SPACING, GREEN);
    pos.y += 30;

    DrawTextEx(_get_font(FontSize::HUGE), "HUGE", pos, wr_y(_font_to_percent.at(FontSize::HUGE)), FONTS_SPACING, GREEN);
    pos.y += 30;
}

