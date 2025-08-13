#include "sprite_sheet.h"
#include <assert.h>

void SpriteSheet::load(const char *texture_filename, float sprite_width)
{
    m_texture = LoadTexture(texture_filename);
    m_sprite_width = sprite_width;
}

void SpriteSheet::unload()
{
    UnloadTexture(m_texture);
}

void SpriteSheet::draw(int sprite_index, Rectangle dest_rect, Color tint_color)
{
    float sprite_index_f = static_cast<float>(sprite_index);
    float texture_height_f = static_cast<float>(m_texture.height);
    Rectangle sprite_src_rect = {
        sprite_index_f * m_sprite_width, 
        0,
        m_sprite_width, 
        texture_height_f,
    };
    // assert(sprite_src_rect.x <= m_texture.width);

    DrawTexturePro(m_texture, sprite_src_rect, dest_rect, {0, 0}, 0, tint_color);
}

void SpriteSheet::draw_flipped(int sprite_index, Rectangle dest_rect, Color tint_color, bool flip_x, bool flip_y)
{
    float sprite_index_f = static_cast<float>(sprite_index);
    float texture_height_f = static_cast<float>(m_texture.height);
    Rectangle sprite_src_rect = {
        sprite_index_f * m_sprite_width, 
        0,
        flip_x ? -m_sprite_width : m_sprite_width, 
        flip_y ? - texture_height_f : texture_height_f,
    };
    // assert(sprite_src_rect.x <= m_texture.width);

    DrawTexturePro(m_texture, sprite_src_rect, dest_rect, {0, 0}, 0, tint_color);
}