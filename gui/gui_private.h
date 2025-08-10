#ifndef _GUI_PRIVATE_H_
#define _GUI_PRIVATE_H_

#include "raylib.h"
#include "../rutils.h" 
#include "gui.h"
#include <map>
#include <string>

constexpr float FONTS_SPACING = 0.0f;

// Loads all fonts
void _load_fonts();

// Unloads all fonts
void _unload_fonts();

// Get font by size
Font _get_font(FontSize size);

// Load single font
void _load_font(FontSize size);

#endif