// rutils.cpp
// Version: 25-05-25

#include <raylib.h>
#include <raymath.h>
#include <cmath>
#include <cassert>
#include <cstdlib>


// ==================== RANDOM ====================

 int rand_i(int min, int max) {
    return GetRandomValue(min, max);
}

 float rand_f(float min, float max) {
    int v = rand_i(int(min), int(max));
	return v;
}

Vector2 rand_coord_in_range(Vector2 init_pos, float min, float max) {
    int side = GetRandomValue(1, 4);
    float v = 0;

    // left
    if (side == 1) {
        v = rand_f(min, max);
        float new_x = init_pos.x - v;
        v = rand_f(-max, max);
        float new_y = init_pos.y + v;
        return {new_x, new_y};
    }
    // right
    if (side == 2) {
        v = rand_f(min, max);
        float new_x = init_pos.x + v;
        v = rand_f(-max, max);
        float new_y = init_pos.y + v;
        return {new_x, new_y};
    }
    // top
    if (side == 3) {
        v = rand_f(-max, max);
        float new_x = init_pos.x + v;
        v = rand_f(min, max);
        float new_y = init_pos.y - v;
        return {new_x, new_y};
    }
    // bottom
    if (side == 4) {
        v = rand_f(-max, max);
        float new_x = init_pos.x + v;
        v = rand_f(min, max);
        float new_y = init_pos.y + v;
        return {new_x, new_y};
    }

    assert(false && "Unreachable");
    return init_pos;
}

// ==================== TIMER ====================

struct Timer {
    float value;
};

 Timer timer_start(float value) {
    return Timer{value};
}

 void timer_update(Timer &timer, float frame_time) {
    if (timer.value <= 0) return;
    timer.value -= frame_time;
    if (timer.value < 0) timer.value = 0;
}

 bool timer_is_finished(const Timer &timer) {
    return timer.value <= 0;
}

 bool timer_is_in_progress(const Timer &timer) {
    return timer.value > 0;
}

// ==================== ITERATOR ====================

struct Iterator {
    int index;
    bool done;
};

 Iterator iterator_init() {
    return {-1, false};
}

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

Rectangle _panel_x_child_rect_by_index(const Panel &panel, int index) {
    float child_width = panel.rect.width / (float)panel.children_count;
    return {
        panel.rect.x + child_width * index,
        panel.rect.y,
        child_width,
        panel.rect.height
    };
}

Rectangle _panel_y_child_rect_by_index(const Panel &panel, int index) {
    float child_height = panel.rect.height / (float)panel.children_count;
    return {
        panel.rect.x,
        panel.rect.y + child_height * index,
        panel.rect.width,
        child_height
    };
}

Rectangle panel_get_child_rect(const Panel &panel, int index) {
    assert(index < panel.children_count);
    switch (panel.orientation) {
        case PanelOrientation::Horizontal:
            return _panel_x_child_rect_by_index(panel, index);
        case PanelOrientation::Vertical:
            return _panel_y_child_rect_by_index(panel, index);
        default:
            assert(false && "Panel orientation should be set");
            return {};
    }
}

Rectangle panel_next_child(const Panel &panel, Iterator &it) {
    it.index++;
    Rectangle child_rect = panel_get_child_rect(panel, it.index);
    if (it.index == panel.children_count - 1) {
        it.done = true;
    }
    return child_rect;
}

// ==================== RECT HELPERS ====================

Vector2 rect_calc_center(Rectangle rect) {
    return {rect.x + rect.width / 2.0f, rect.y + rect.height / 2.0f};
}

Vector2 rect_get_pos(Rectangle rect) {
    return {rect.x, rect.y};
}

Vector4 rect_to_vec4(Rectangle rect) {
    return {rect.x, rect.y, rect.width, rect.height};
}

Rectangle rect_with_center_pos(Vector2 center_pos, float width, float height) {
    return {center_pos.x - width / 2.0f, center_pos.y - height / 2.0f, width, height};
}

Rectangle vec4_to_rect(const Vector4 vec) {
    return {vec.x, vec.y, vec.z, vec.w};
}

void rect_move_towards_pos(Rectangle &rect, Vector2 target_pos, float px_per_sec, float frame_time) {
    float step = px_per_sec * frame_time;
    auto rect_center = rect_calc_center(rect);
    Vector2 diff = {target_pos.x - rect_center.x, target_pos.y - rect_center.y};
    Vector2 diff_norm = Vector2Normalize(diff);
    Vector2 move_offset = {diff_norm.x * step, diff_norm.y * step};
    rect.x += move_offset.x;
    rect.y += move_offset.y;
}

// rect_move_towards_pos :: proc(
// 	rect: ^rl.Rectangle,
// 	target_pos: rl.Vector2,
// 	px_per_sec: f32,
// 	frame_time: f32,
// ) {
// 	step := px_per_sec * frame_time
// 	diff := target_pos - rect_calc_center(rect^)
// 	diff_norm := rl.Vector2Normalize(diff)
// 	move_offset := rl.Vector2{diff_norm.x * step, diff_norm.y * step}

// 	rect.x += move_offset.x
// 	rect.y += move_offset.y
// }

// ==================== WINDOW ====================

constexpr float WINDOW_WIDTH = 1600.0f;
constexpr float WINDOW_HEIGHT = 900.0f;
constexpr Vector2 WINDOW_CENTER = {WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f};
constexpr int TARGET_FPS = 400;

 void window_init() {
    SetTraceLogLevel(LOG_WARNING);
    InitWindow((int)WINDOW_WIDTH, (int)WINDOW_HEIGHT, "Project AutoRPG");
    SetTargetFPS(TARGET_FPS);
}

 void window_deinit() {
    CloseWindow();
}

 void draw_fps() {
    DrawFPS(0, 10);
}

// ==================== WR HELPERS ====================

 float wr_x(float percent) {
    return WINDOW_WIDTH / 100.0f * percent;
}

 float wr_y(float percent) {
    return WINDOW_HEIGHT / 100.0f * percent;
}

 Vector2 wr_vec2(Vector2 vec) {
    return {wr_x(vec.x), wr_y(vec.y)};
}

 Rectangle wr_rect(Rectangle rect) {
    return {wr_x(rect.x), wr_y(rect.y), wr_x(rect.width), wr_y(rect.height)};
}

 Rectangle wr_rect_with_center_pos(Vector2 related_center_pos, float related_width, float related_height) {
    return {
        wr_x(related_center_pos.x) - wr_x(related_width) / 2.0f,
        wr_y(related_center_pos.y) - wr_y(related_height) / 2.0f,
        wr_x(related_width),
        wr_y(related_height)
    };
}
