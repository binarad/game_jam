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
    void start_spawning();
    void stop();

    void update();
    void draw(SpriteSheet &enemy_sprite);
    // TODO: rename
    void remove_clicked_enemies(Vector2 mouse_pos);

    void damage_flower(Flower &flower);
private:
    std::vector<Rectangle> m_list;

    float m_move_speed;
    float m_spawn_timeout;

    Timer m_spawn_timer;
    Timer m_damage_timer;
    Timer m_phase_change_timer;
};