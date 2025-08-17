#ifndef _FLOWER_H_
#define _FLOWER_H_

#include <raylib.h>
#include "sprite_sheet.h"
#include "rutils.h"

class Flower
{
private:
    float m_hp;
    float m_energy;

public:
    const float MAX_HP = 100.0f;
    const float MAX_ENERGY = 100.0f;
    const float ENERGY_REGEN_SPEED = 0.03f;
    const float EXPLOSION_ENERGY_COST = 10.0f;

    Rectangle flower_bounds = wr_rect_with_center_pos({50, 50}, wr_x_from_y(20), 20);

    Timer m_flower_energy_timer;

    void init();

    // do we even need this?
    float get_hp();
    void set_hp(float hp);

    float get_energy();
    void set_energy(float energy);

    void flower_draw(SpriteSheet &sprite_sheet, int game_phase);
    void hp_energy_draw();

    void regen_energy(float frame_time);
    void decrease_energy();
};

#endif
