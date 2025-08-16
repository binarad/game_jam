#ifndef _RUTILS_H_
#define _RUTILS_H_

// rutils.h
// Version: 25-05-25


#include "raylib.h"
#include <cmath>
#include <cassert>
#include <cstdlib>


// ==================== RANDOM ====================

int rand_i(int min, int max);
float rand_f(float min, float max);
Vector2 rand_coord_in_range(Vector2 init_pos, float min, float max);

// ==================== TIMER ====================

struct Timer {
    float starting_value;
    float value;
};

Timer timer_start(float value);
void timer_update(Timer &timer, float frame_time);
bool timer_is_finished(const Timer &timer);
bool timer_is_in_progress(const Timer &timer);
void timer_restart(Timer &timer);

// ==================== ITERATOR ====================

struct Iterator {
    int index;
    bool done;
};

Iterator iterator_init();

// ==================== PANEL ====================

enum class PanelOrientation {
    None,
    Horizontal,
    Vertical
};

struct Panel {
    Rectangle rect;
    int children_count;
    PanelOrientation orientation;
};

Rectangle panel_get_child_rect(const Panel &panel, int index);
Rectangle panel_next_child(const Panel &panel, Iterator &it);

// ==================== RECT HELPERS ====================

Vector2 rect_calc_center(Rectangle rect);
Vector2 rect_get_pos(Rectangle rect);
Rectangle rect_with_center_pos(Vector2 center_pos, float width, float height);
void rect_move_towards_pos(Rectangle &rect, Vector2 target_pos, float px_per_sec, float frame_time);

// ==================== WINDOW ====================

constexpr float WINDOW_WIDTH = 1600.0f;
constexpr float WINDOW_HEIGHT = 900.0f;
constexpr Vector2 WINDOW_CENTER = {WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f};
constexpr int TARGET_FPS = 400;

void window_init();
void window_deinit();
void draw_fps();

// ==================== WR HELPERS ====================

// WR - window related

float wr_x(float percent);

float wr_y(float percent);

// Convert percent of height into percent of width
float wr_x_from_y(float percent);

Vector2 wr_vec2(Vector2 vec);
Rectangle wr_rect(Rectangle rect);
Rectangle wr_rect_with_center_pos(Vector2 related_center_pos, float related_width, float related_height);


#endif