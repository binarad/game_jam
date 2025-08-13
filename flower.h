#ifndef _FLOWER_H_
#define _FLOWER_H_

class Flower
{
private:
    float m_hp;
    float m_energy;
    int m_stage;

public:
    float get_hp();
    float get_energy();
    int get_stage();
};

#endif