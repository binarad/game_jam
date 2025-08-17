#pragma once

#include <raylib.h>
#include <vector>
#include <array>
#include "rutils.h"
#include "sprite_sheet.h"
#include "flower.h"
#include "enemy.h"

const float EXPLOSION_RADIUS = wr_y(5);

class EnemiesManager
{
public:
    void init();
    void stop();

    void update(Flower &flower, int &game_phase, float frame_time);
    void draw();
    void draw_phase(int game_phase);
    void remove_clicked_enemies(Vector2 mouse_pos);
    void load_enemy_textures();
    void unload_enemy_textures();

private:
    std::vector<Enemy> m_list;

    float m_move_speed;
    float m_spawn_timeout;

    Timer m_spawn_timer;
    Timer m_damage_timer;
    Timer m_phase_change_timer;

    std::array<SpriteSheet, 9> m_enemy_textures;

    void _damage_flower(Flower &flower, float frame_time);
};