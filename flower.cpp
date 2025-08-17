#include "flower.h"
#include "rutils.h"
#include "pallete.h"

void Flower::init()
{
    m_hp = MAX_HP;
	m_energy = MAX_ENERGY;
	m_flower_energy_timer = timer_start(ENERGY_REGEN_SPEED);
}

float Flower::get_energy()
{
    return m_energy;
}

void Flower::set_energy(float energy)
{
    m_energy = energy;
}

float Flower::get_hp()
{
    return m_hp;
}

void Flower::set_hp(float hp)
{
    m_hp = hp;
    if (m_hp < 0) {
        m_hp = 0;
    }
}

void Flower::flower_draw(SpriteSheet &flower_sprite_sheet, int game_phase)
{
    flower_sprite_sheet.draw(game_phase / 10, flower_bounds, WHITE);
}

void Flower::hp_energy_draw()
{
    // hp border
    DrawRectangle(wr_x(4.8f), wr_y(4.5f), wr_x(12.5f), wr_y(3), COLOR_YELLOW);
    // hp inner
    float hp_amount = m_hp / MAX_HP;
    DrawRectangle(wr_x(5), wr_y(5), wr_x(12) * hp_amount, wr_y(2), COLOR_GREEN);

    // energy
    float energy_amount = m_energy / MAX_ENERGY;
    DrawRectangle(wr_x(5), wr_y(8.5), wr_x(12) * energy_amount, wr_y(2), COLOR_YELLOW);
}

void Flower::regen_energy(float frame_time)
{
    timer_update(m_flower_energy_timer, frame_time);
    if (timer_is_finished(m_flower_energy_timer))
    {
        m_flower_energy_timer = timer_start(ENERGY_REGEN_SPEED);

        if (m_energy < MAX_ENERGY)
        {
            m_energy += 1;
        }
    }
}

void Flower::decrease_energy()
{
    m_energy -= EXPLOSION_ENERGY_COST;
}
