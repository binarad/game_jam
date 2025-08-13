#include <iostream>
#include <raylib.h>
#include "rutils.h"
#include "gui/gui.h"
#include "pallete.h"
#include "enemies.h"
#include "sprite_sheet.h"


void flower_draw(SpriteSheet &flower_sprite_sheet) 
{
	flower_sprite_sheet.draw(4, wr_rect_with_center_pos({50, 50}, wr_x_from_y(20), 20), WHITE);
}


int main()
{
	window_init();
	gui_init();

	EnemiesManager enemies_manager;
	enemies_manager.start_spawning();

	// FLOWER SPRITE SHEET
	// Texture2D flower_texture = LoadTexture();
	// Rectangle source_rec = Rectangle {32,32, 16, 16};
	// Vector2 position_V = Vector2{200, 200};

	SpriteSheet flower_sprite_sheet;
	flower_sprite_sheet.load("assets/flower_sprite_sheet.png", 16);
	
	// ---------------------------------------
	while (!WindowShouldClose())
	{
		// UPDATE
		enemies_manager.update();

		// DRAW
		BeginDrawing();
		ClearBackground(COLOR_GREEN);

		flower_draw(flower_sprite_sheet);
		enemies_manager.draw();

		// FLOWER DRAW
		// DrawTextureRec(flower_texture, source_rec, position_V, WHITE);
		// DrawTexturePro(flower_texture, source_rec, wr_rect({20, 20, 10, 10}), )
		// CIRCLE DRAW WITH CENTER IN MOUSE POS
		DrawCircleLines(GetMouseX(), GetMouseY(), 50.0f, COLOR_YELLOW);
		//TODO Make a Enemy class
		// if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionCircleRec(GetMousePosition(), 50.0f,))
        

		draw_fps();

		EndDrawing();
	}	 

	gui_deinit();
	window_deinit();

	return 0;
}

