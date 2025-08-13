#pragma once

#include <raylib.h>
#include <vector>
#include "rutils.h"
#include "sprite_sheet.h"

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
    void check_mouse_click(Vector2 mouse_pos);
};