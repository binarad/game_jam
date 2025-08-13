#ifndef _SPRITE_SHEET_H_
#define _SPRITE_SHEET_H_

#include <raylib.h>
#include <string>

// Sprite sheet in single row
class SpriteSheet {
public:
    void load(const char *texture_filename, float sprite_width);
    void unload();

    void draw(int sprite_index, Rectangle dest_rect, Color tint_color);
    void draw_flipped(int sprite_index, Rectangle dest_rect, Color tint_color, bool flip_x, bool flip_y);

private:
    Texture2D m_texture;
    float m_sprite_width;
};

#endif