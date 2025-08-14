#include "flower.h"

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

void Flower::set_stage(int stage)
{
    m_stage = stage;
}

void Flower::flower_draw(SpriteSheet &flower_sprite_sheet)
{
	flower_sprite_sheet.draw(1, wr_rect_with_center_pos({50, 50}, wr_x_from_y(20), 20), WHITE);
}
