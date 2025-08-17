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
const float PLAYER_ENERGY_REGEN_SPEED = 0.5;

struct GameState
{
	int phase;
};

void gamestate_init(GameState &game_state)
{
	game_state.phase = 1;
}

Timer explosion_timer;

void explosion_draw()
{
	DrawRing(GetMousePosition(), EXPLOSION_RADIUS - wr_y(0.3), EXPLOSION_RADIUS, 0, 360, 100, COLOR_YELLOW);
}

int main()
{
	SetConfigFlags(FLAG_FULLSCREEN_MODE | FLAG_BORDERLESS_WINDOWED_MODE);
	window_init();
	InitAudioDevice();
	gui_init();

	// init game state
	GameState game_state;
	gamestate_init(game_state);

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

	Music backgroun_music = LoadMusicStream("assets/background_music.mp3");
	backgroun_music.looping = true;
	SetMusicVolume(backgroun_music, 0.35f);
	PlayMusicStream(backgroun_music);

	Sound game_over = LoadSound("assets/game_over.mp3");
	Sound fail_trumpet = LoadSound("assets/fail-trumpet.mp3");

	Sound win_sound = LoadSound("assets/win1.mp3");
	Sound click_sound = LoadSound("assets/on_enemy_click_sound.mp3");

	while (!WindowShouldClose())
	{

		UpdateMusicStream(backgroun_music);
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

				// if clicked and have energy for explosion
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && (flower.get_energy() >= flower.EXPLOSION_ENERGY_COST))
				{
					flower.decrease_energy();
					PlaySound(click_sound);
					enemies_manager.remove_clicked_enemies(GetMousePosition());
				}

				if (flower.get_hp() <= 0)
				{
					is_died = true;
				}
			}
		}

		// === DRAW ===
		BeginDrawing();
		ClearBackground(COLOR_GREEN);

		flower.flower_draw(flower_sprite_sheet, game_state.phase);

		enemies_manager.draw();

		flower.hp_energy_draw();
		// CIRCLE DRAW WITH CENTER IN MOUSE POS
		explosion_draw();

		enemies_manager.draw_phase(game_state.phase);

		draw_fps();

		if (is_game_finished)
		{
			StopMusicStream(backgroun_music);
			PlaySound(win_sound);
			ClearBackground(COLOR_GREEN);
			text_draw_aligned(
				"BLOOOOOOOOM !",
				FontSize::HUGE_SIZE,
				COLOR_YELLOW,
				wr_rect_with_center_pos({50, 50}, 20, 10),
				TextAlignment::AllCenter);
		}
		else if (is_died)
		{
			StopMusicStream(backgroun_music);
			PlaySound(game_over);
			if (!IsSoundPlaying(game_over))
				PlaySound(fail_trumpet);

			Button restart_button(
				{50, 40, 20, 10},
				COLOR_GREEN,
				COLOR_YELLOW,
				"Restart ?");
			if (restart_button.mouse_click(GetMousePosition()))
			{
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
