#include "flower.h"
#include "rutils.h"
#include "pallete.h"

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
}

int Flower::get_stage()
{
    return m_stage;
}

void Flower::flower_draw(SpriteSheet &flower_sprite_sheet)
{
    flower_sprite_sheet.draw(1, wr_rect_with_center_pos({50, 50}, wr_x_from_y(20), 20), WHITE);
}

void Flower::hp_energy_draw()
{
    // hp border
    DrawRectangle(wr_x(4.8f), wr_y(4.5f), wr_x(12.5f), wr_y(3), COLOR_YELLOW);
    // hp inner
    DrawRectangle(wr_x(5), wr_y(5), wr_x(12), wr_y(2), COLOR_GREEN);

    // energy
    float energy_amount = m_energy / MAX_ENERGY;
    DrawRectangle(wr_x(5), wr_y(8.5), wr_x(12) * energy_amount, wr_y(2), COLOR_YELLOW);
}

void Flower::regen_energy()
{
    timer_update(m_flower_energy_timer, GetFrameTime());
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
