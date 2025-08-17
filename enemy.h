#pragma once

#include <raylib.h>
#include "rutils.h"
#include "sprite_sheet.h"
class Enemy
{
public:
    Rectangle bounds;
    SpriteSheet texture;

    Enemy(float x, float y, float width, float height, const SpriteSheet &tex) : texture(tex)
    {
        bounds = {x, y, width, height};
    }
};