#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include "rutils.h"
#include "gui/gui.h"
#include "button.h"

#include "pallete.h"
#include "enemies_manager.h"
#include "sprite_sheet.h"


const float PLAYER_HP_MAX = 100;
const float PLAYER_ENERGY_MAX = 100;
const float PLAYER_ENERGY_COST = 10;
const float PLAYER_ENERGY_REGEN_SPEED = 0.1;

struct GameState
{
	float player_hp;
	float player_energy;
	Timer player_energy_timer;
};

void flower_draw(SpriteSheet &flower_sprite_sheet)
{
	flower_sprite_sheet.draw(1, wr_rect_with_center_pos({50, 50}, wr_x_from_y(20), 20), WHITE);
}


void hp_energy_draw(GameState &game_state)
{
	// hp border
	DrawRectangle(wr_x(4.8f), wr_y(4.5f), wr_x(12.5f), wr_y(3), COLOR_YELLOW);
	// hp inner
	DrawRectangle(wr_x(5), wr_y(5), wr_x(12), wr_y(2), COLOR_GREEN);

	// energy
	float energy_amount = game_state.player_energy / PLAYER_ENERGY_MAX;
	DrawRectangle(wr_x(5), wr_y(8.5), wr_x(12) * energy_amount, wr_y(2), COLOR_YELLOW);
}

int main()
{
	window_init();
	gui_init();

	// init game state
	GameState game_state;
	game_state.player_hp = PLAYER_HP_MAX;
	game_state.player_energy = PLAYER_ENERGY_MAX;
	game_state.player_energy_timer = timer_start(PLAYER_ENERGY_REGEN_SPEED);

	// init enemies
	EnemiesManager enemies_manager;
	enemies_manager.start_spawning();

	SpriteSheet flower_sprite_sheet;
	flower_sprite_sheet.load("assets/flower_sprite_sheet.png", 16);

	SpriteSheet enemy_sprite;
	// TODO: move inside enemy manager
	enemy_sprite.load("assets/enemy-1.png", 16);

	// ---------------------------------------
	bool close_window = false;
	// Button play_button(Rectangle{50.0f, 50.0f, 20.0f, 10.0f}, COLOR_YELLOW, COLOR_GREEN, "PLAY");

	while (!WindowShouldClose() && !close_window)
	{
		// if (play_button.Hover(GetMousePosition()))
		// {
		// 	play_button.color = COLOR_GREEN;
		// 	play_button.label_color = COLOR_YELLOW;
		// }
		// else
		// {
		// 	play_button.color = COLOR_YELLOW;
		// 	play_button.label_color = COLOR_GREEN;
		// }

		// === UPDATE ===
		{
			enemies_manager.update();

			// regen. energy
			timer_update(game_state.player_energy_timer, GetFrameTime());
			if (timer_is_finished(game_state.player_energy_timer)) {
				game_state.player_energy_timer = timer_start(PLAYER_ENERGY_REGEN_SPEED);

				if (game_state.player_energy < PLAYER_ENERGY_MAX) {
					game_state.player_energy += 1;
					// flower.regen_energy()
				}
			}

			// if clicked and have energy for explosion
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && (game_state.player_energy >= PLAYER_ENERGY_COST)) {
				game_state.player_energy -= PLAYER_ENERGY_COST;
				// flower.spend_energy_for_explosion()
				enemies_manager.check_mouse_click(GetMousePosition());
			}
		}

		// === DRAW ===
		BeginDrawing();
		ClearBackground(COLOR_GREEN);

		flower_draw(flower_sprite_sheet);
		
		enemies_manager.draw(enemy_sprite);
		
		// TODO: move to flower
		hp_energy_draw(game_state);
		// FLOWER DRAW
		// DrawTextureRec(flower_texture, source_rec, position_V, WHITE);
		// DrawTexturePro(flower_texture, source_rec, wr_rect({20, 20, 10, 10}), )
		// CIRCLE DRAW WITH CENTER IN MOUSE POS
		DrawCircleLines(GetMouseX(), GetMouseY(), EXPLOSION_RADIUS, COLOR_YELLOW);
		// TODO Make a Enemy class

		draw_fps();

		EndDrawing();
	}

	gui_deinit();
	window_deinit();

	return 0;
}
