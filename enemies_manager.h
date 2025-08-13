#pragma once

#include <raylib.h>
#include <vector>
#include "rutils.h"
#include "sprite_sheet.h"

const float EXPLOSION_RADIUS = wr_y(5);

class EnemiesManager
{
private:
    std::vector<Rectangle> m_list;
    Timer m_spawn_timer;

public:
    void start_spawning();
    void stop();

    void update();
    void draw(SpriteSheet &enemy_sprite);
    // TODO: rename
    void check_mouse_click(Vector2 mouse_pos);
};