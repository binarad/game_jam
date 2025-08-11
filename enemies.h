#pragma once

#include <raylib.h>
#include <vector>
#include "rutils.h"

class EnemiesManager
{
private:
    std::vector<Rectangle> m_list;
    Timer m_spawn_timer;
public:
    void start_spawning();
    void stop();

    void update();
    void draw();
};