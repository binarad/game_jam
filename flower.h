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
    int m_stage;

public:
    const float MAX_HP = 100.0f;
    const float MAX_ENERGY = 100.0f;
    const float ENERGY_REGEN_SPEED = 0.1f;
    const float EXPLOSION_ENERGY_COST = 10.0f;

    Timer m_flower_energy_timer;
    // do we even need this?
    float get_hp();
    void set_hp(float hp);

    float get_energy();
    void set_energy(float energy);

    int get_stage();

    void flower_draw(SpriteSheet &sprite_sheet);
    void hp_energy_draw();

    void regen_energy();
    void decrease_energy();
};

#endif
