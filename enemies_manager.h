#pragma once

#include <raylib.h>
#include <vector>
#include "rutils.h"
#include "sprite_sheet.h"
#include "flower.h"

const float EXPLOSION_RADIUS = wr_y(5);

class EnemiesManager
{
public:
    void init();
    void stop();

    void update(Flower &flower, int &game_phase, float frame_time);
    void draw(SpriteSheet &enemy_sprite);
    void draw_phase(int game_phase);
    // TODO: rename
    void remove_clicked_enemies(Vector2 mouse_pos);

private:
    std::vector<Rectangle> m_list;

    float m_move_speed;
    float m_spawn_timeout;

    Timer m_spawn_timer;
    Timer m_damage_timer;
    Timer m_phase_change_timer;

    void _damage_flower(Flower &flower, float frame_time);
};