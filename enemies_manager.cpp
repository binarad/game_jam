#include <raylib.h>
#include <vector>
#include "rutils.h"
#include "pallete.h"
#include "enemies_manager.h"
#include "sprite_sheet.h"
#include "flower.h"
#include <iostream>

const float ENEMIES_MOVE_SPEED = wr_y(2);
const float ENEMIES_SPAWN_TIMEOUT = 1.0;
const float ENEMIES_SPAWN_MIN_RANGE = wr_y(40);
const float ENEMIES_SPAWN_MAX_RANGE = wr_y(45);
const Vector2 ENEMY_SIZE = {wr_x(3), wr_x(3)};

const float ENEMIES_DAMAGE_SPEED = 1.0f;

void EnemiesManager::start_spawning()
{
    m_list.reserve(1024);
    m_spawn_timer = timer_start(ENEMIES_SPAWN_TIMEOUT);
    m_damage_timer = timer_start(ENEMIES_DAMAGE_SPEED);
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
        // TODO: what is x, y 50 ?
        if (enemy_rect.x > wr_x(50))
            enemy_sprite.draw_flipped(0, enemy_rect, WHITE, true, false);

        if (enemy_rect.x < wr_x(50))
            enemy_sprite.draw(0, enemy_rect, WHITE);
        // DrawRectangleRec(enemy_rect, COLOR_YELLOW);
    }
}

void EnemiesManager::remove_clicked_enemies(Vector2 mouse_pos)
{
    for (size_t index = 0; index < m_list.size(); index++)
    {
        if (CheckCollisionCircleRec(mouse_pos, EXPLOSION_RADIUS, m_list[index]))
        {
            m_list.erase(m_list.begin() + index);
        }
    }
}

void EnemiesManager::damage_flower(Flower &flower)
{
    for (auto enemy : m_list)
    {
        // TODO: Add timer to this func
        timer_update(m_damage_timer, GetFrameTime());

        if(CheckCollisionRecs(enemy, flower.flower_bounds))
        {
            // std::cout << "TIMER IS IN PROGRESS: " << timer_is_in_progress(m_damage_timer) << std::endl;
            if (timer_is_finished(m_damage_timer))
            {
                m_damage_timer = timer_start(ENEMIES_DAMAGE_SPEED);
                flower.set_hp(flower.get_hp() - 10.0f);
                std::cout << "Damage applied. FLOWER HP: " << flower.get_hp() << std::endl;
            }   

            break;
        }
    }
}