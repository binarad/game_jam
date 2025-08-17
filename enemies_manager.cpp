#include <raylib.h>
#include <vector>
#include "rutils.h"
#include "pallete.h"
#include "enemies_manager.h"
#include "sprite_sheet.h"
#include "flower.h"
#include <iostream>

const float ENEMIES_PHASE_CHANGE_TIMEOUT = 1.0;

// how much move speed increase on phase change
const float ENEMIES_PHASE_MOVE_SPEED_INCREASE_MUL = 1.5;
// how much spawn timeout decrease on phase change
const float ENEMIES_PHASE_SPAWN_TIMEOUT_DECREASE_MUL = 1.5;

const float ENEMIES_DEFAULT_MOVE_SPEED = wr_y(2);

const float ENEMIES_DEFAULT_SPAWN_TIMEOUT = 1.0;

const float ENEMIES_SPAWN_MIN_RANGE = wr_y(40);
const float ENEMIES_SPAWN_MAX_RANGE = wr_y(45);
const Vector2 ENEMY_SIZE = {wr_x(3), wr_x(3)};

const float ENEMIES_DAMAGE_SPEED = 1.0f;

void EnemiesManager::start_spawning()
{
    m_list.reserve(10240);

    m_spawn_timeout = ENEMIES_DEFAULT_SPAWN_TIMEOUT;
    m_move_speed = ENEMIES_DEFAULT_MOVE_SPEED;

    m_phase_change_timer = timer_start(ENEMIES_PHASE_CHANGE_TIMEOUT);
    m_spawn_timer = timer_start(m_spawn_timeout);
    m_damage_timer = timer_start(ENEMIES_DAMAGE_SPEED);
}

void EnemiesManager::stop()
{
    // DO WE NEED THIS ?
}

void EnemiesManager::update(Flower &flower)
{
    auto frame_time = GetFrameTime();

    // phase change
    timer_update(m_phase_change_timer, frame_time);
    if (timer_is_finished(m_phase_change_timer)) 
    {
        timer_restart(m_phase_change_timer);

        m_spawn_timeout /= ENEMIES_PHASE_SPAWN_TIMEOUT_DECREASE_MUL;
        m_move_speed *= ENEMIES_PHASE_MOVE_SPEED_INCREASE_MUL;
    }

    // spawn
    // std::cout << m_spawn_timeout << std::endl;
    timer_update(m_spawn_timer, frame_time);
    if (timer_is_finished(m_spawn_timer))
    {
        // we change spawn timeout on phase change
        m_spawn_timer = timer_start(m_spawn_timeout);

        auto pos = rand_coord_in_range(wr_vec2({50, 50}), ENEMIES_SPAWN_MIN_RANGE, ENEMIES_SPAWN_MAX_RANGE);
        m_list.push_back({pos.x, pos.y, ENEMY_SIZE.x, ENEMY_SIZE.y});
    }

    for (auto &enemy_rect : m_list)
    {
        rect_move_towards_pos(enemy_rect, wr_vec2({50, 50}), m_move_speed, frame_time);
    }

    _damage_flower(flower);
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

void EnemiesManager::_damage_flower(Flower &flower)
{

    timer_update(m_damage_timer, GetFrameTime());

    // cant attack until timer finished
    if (timer_is_in_progress(m_damage_timer)) {
        return;
    }

    for (auto enemy : m_list)
    {
        if (CheckCollisionRecs(enemy, flower.flower_bounds))
        {
            timer_restart(m_damage_timer);
            flower.set_hp(flower.get_hp() - 10.0f);
            // std::cout << "Damage applied. FLOWER HP: " << flower.get_hp() << std::endl;

            break;
        }
    }
}
