#ifndef _FLOWER_H_
#define _FLOWER_H_

#include "sprite_sheet.h"

class Flower
{
private:
    float m_hp;
    float m_energy;
    int m_stage;

public:
    // Getter and setter for hp
    float get_hp();
    void set_hp(float hp);

    // Getter and setter for energy
    float get_energy();
    void set_energy(float energy);

    // Getter and setter for flower stage
    int get_stage();
    void set_stage(int stage);

    // Draw flower
    void flower_draw(SpriteSheet &sprite_sheet);
};

#endif
