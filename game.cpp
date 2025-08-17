#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include "rutils.h"
#include "gui/gui.h"
#include "button.h"

#include "pallete.h"
#include "enemies_manager.h"
#include "sprite_sheet.h"

#include "flower.h"
const float PLAYER_HP_MAX = 100;
const float PLAYER_ENERGY_MAX = 100;
const float PLAYER_ENERGY_COST = 10;
const float PLAYER_ENERGY_REGEN_SPEED = 0.1;

enum class SceneType
{
	MENU,
	GAME,
	OPTIONS,
	EXIT,
};
struct GameState
{
	// Flower flower;
	SceneType scene_type;
	int phase;
	// float player_hp;
	// float player_energy;
	// Timer player_energy_timer;
};

void gamestate_init(GameState &game_state)
{
	game_state.scene_type = SceneType::GAME;
	game_state.phase = 1;
}

Timer explosion_timer;

void explosion_draw()
{
	DrawRing(GetMousePosition(), EXPLOSION_RADIUS - wr_y(0.3), EXPLOSION_RADIUS, 0, 360, 100, COLOR_YELLOW);
	// DrawCircleLines(GetMouseX(), GetMouseY(), EXPLOSION_RADIUS, COLOR_YELLOW);
}

// void flower_draw(SpriteSheet &flower_sprite_sheet)
// {
// 	flower_sprite_sheet.draw(1, wr_rect_with_center_pos({50, 50}, wr_x_from_y(20), 20), WHITE);
// }

// void hp_energy_draw(GameState &game_state)
// {
// 	// hp border
// 	DrawRectangle(wr_x(4.8f), wr_y(4.5f), wr_x(12.5f), wr_y(3), COLOR_YELLOW);
// 	// hp inner
// 	DrawRectangle(wr_x(5), wr_y(5), wr_x(12), wr_y(2), COLOR_GREEN);

// 	// energy
// 	float energy_amount = game_state.player_energy / PLAYER_ENERGY_MAX;
// 	DrawRectangle(wr_x(5), wr_y(8.5), wr_x(12) * energy_amount, wr_y(2), COLOR_YELLOW);
// }

int main()
{
	SetConfigFlags(FLAG_FULLSCREEN_MODE | FLAG_BORDERLESS_WINDOWED_MODE);
	window_init();

	gui_init();

	// init game state
	GameState game_state;
	gamestate_init(game_state);

	// game_state.player_hp = PLAYER_HP_MAX;
	// game_state.player_energy = PLAYER_ENERGY_MAX;
	// game_state.player_energy_timer = timer_start(PLAYER_ENERGY_REGEN_SPEED);

	// ---------------------------------------------------
	// TODO make a switch case for game_state.scene_type;
	// ---------------------------------------------------

	// init flower
	Flower flower;
	flower.init();

	// init enemies
	EnemiesManager enemies_manager;
	enemies_manager.init();

	SpriteSheet flower_sprite_sheet;
	flower_sprite_sheet.load("assets/flower_sprite_sheet.png", 16);

	SpriteSheet enemy_sprite;
	// TODO: move inside enemy manager
	enemy_sprite.load("assets/enemy-1.png", 16);

	bool is_game_finished = false;
	bool is_died = false;

	enemies_manager.load_enemy_textures();

	while (!WindowShouldClose())
	{

		// BeginDrawing();
		// === UPDATE ===

		// switch (game_state.scene_type)
		{
			// case SceneType::MENU:
			// 	ClearBackground(COLOR_GREEN);
			// 	menu_button_play.draw();
			// 	break;

			// case SceneType::GAME:

			if (!is_game_finished && !is_died)
			{
				auto frame_time = GetFrameTime();
				// frame_time *= 20;

				enemies_manager.update(flower, game_state.phase, frame_time);

				if (game_state.phase == 45)
				{
					is_game_finished = true;
				}

				// regen. energy
				flower.regen_energy(frame_time);
				// timer_update(game_state.player_energy_timer, GetFrameTime());
				// if (timer_is_finished(game_state.player_energy_timer))
				// {
				// 	game_state.player_energy_timer = timer_start(PLAYER_ENERGY_REGEN_SPEED);

				// 	if (game_state.player_energy < PLAYER_ENERGY_MAX)
				// 	{
				// 		game_state.player_energy += 1;
				// 	}
				// }

				// if clicked and have energy for explosion
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && (flower.get_energy() >= flower.EXPLOSION_ENERGY_COST))
				{
					flower.decrease_energy();
					// game_state.player_energy -= PLAYER_ENERGY_COST;
					enemies_manager.remove_clicked_enemies(GetMousePosition());
				}

				if (flower.get_hp() <= 0) {
				is_died = true;
			}
			}
		}

		// === DRAW ===
		BeginDrawing();
		ClearBackground(COLOR_GREEN);

		flower.flower_draw(flower_sprite_sheet, game_state.phase);
		// flower_draw(flower_sprite_sheet);

		enemies_manager.draw(enemy_sprite);

		flower.hp_energy_draw();
		// std::cout << "FLOWER HP: " << flower.get_hp() << std::endl;
		// hp_energy_draw(game_state);
		// CIRCLE DRAW WITH CENTER IN MOUSE POS
		explosion_draw();
		// TODO Make a Enemy class

		enemies_manager.draw_phase(game_state.phase);

		draw_fps();

		if (is_game_finished)
		{
			text_draw_aligned(
				"BLOOOOOOOOM !",
				FontSize::HUGE_SIZE,
				COLOR_YELLOW,
				wr_rect_with_center_pos({50, 50}, 20, 10),
				TextAlignment::AllCenter
			);
		} else if (is_died) {
			Button restart_button(
				{50, 40, 20, 10}, 
				COLOR_GREEN,
				COLOR_YELLOW, 
				"Restart ?"
			);
			if (restart_button.mouse_click(GetMousePosition())) {
				is_died = false;

				gamestate_init(game_state);
				flower.init();
				enemies_manager.init();
			}
			restart_button.draw();
		}

		EndDrawing();
	}
	enemies_manager.unload_enemy_textures();
	gui_deinit();
	window_deinit();

	return 0;
}
