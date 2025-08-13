#include <raylib.h>
#include <vector>
#include "rutils.h"
#include "pallete.h"
#include "enemies_manager.h"
#include "sprite_sheet.h"

const float ENEMIES_MOVE_SPEED = wr_y(2);
const float ENEMIES_SPAWN_TIMEOUT = 1.0;
const float ENEMIES_SPAWN_MIN_RANGE = wr_y(40);
const float ENEMIES_SPAWN_MAX_RANGE = wr_y(45);
const Vector2 ENEMY_SIZE = {wr_x(3), wr_x(3)};

void EnemiesManager::start_spawning()
{
    m_list.reserve(1024);
    m_spawn_timer = timer_start(ENEMIES_SPAWN_TIMEOUT);
}

void EnemiesManager::stop()
{
    // DO WE NEED THIS ?
}

void EnemiesManager::update()
{
    auto frame_time = GetFrameTime();
    timer_update(m_spawn_timer, frame_time);
    // spawn
    if (timer_is_finished(m_spawn_timer))
    {
        auto pos = rand_coord_in_range(wr_vec2({50, 50}), ENEMIES_SPAWN_MIN_RANGE, ENEMIES_SPAWN_MAX_RANGE);
        m_list.push_back({pos.x, pos.y, ENEMY_SIZE.x, ENEMY_SIZE.y});

        m_spawn_timer = timer_start(ENEMIES_SPAWN_TIMEOUT);
    }

    for (auto &enemy_rect : m_list)
    {
        rect_move_towards_pos(enemy_rect, wr_vec2({50, 50}), ENEMIES_MOVE_SPEED, frame_time);
    }
}

void EnemiesManager::draw(SpriteSheet &enemy_sprite)
{
    for (auto enemy_rect : m_list)
    {
        if (enemy_rect.x > wr_x(50))
            enemy_sprite.draw_flipped(0, enemy_rect, WHITE, true, false);

        if (enemy_rect.x < wr_x(50))
            enemy_sprite.draw(0, enemy_rect, WHITE);
        // DrawRectangleRec(enemy_rect, COLOR_YELLOW);
    }
}

void EnemiesManager::check_mouse_click(Vector2 mouse_pos)
{
    for (size_t index = 0; index < m_list.size(); index++)
    {
        if (CheckCollisionPointRec(mouse_pos, m_list[index]) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            m_list.erase(m_list.begin() + index);
    }
}