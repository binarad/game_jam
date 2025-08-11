#include <iostream>
#include <raylib.h>
#include "rutils.h"
#include "gui/gui.h"
#include "pallete.h"
#include "enemies.h"


void flower_draw() 
{
	DrawCircleV(wr_vec2({50, 50}), wr_x(4), COLOR_YELLOW);
}


int main()
{
	window_init();
	gui_init();

	EnemiesManager enemies_manager;
	enemies_manager.start_spawning();

	while (!WindowShouldClose())
	{
		// UPDATE
		enemies_manager.update();

		// DRAW
		BeginDrawing();
		ClearBackground(COLOR_GREEN);

		flower_draw();
		enemies_manager.draw();

		draw_fps();

		EndDrawing();
	}	 

	gui_deinit();
	window_deinit();

	return 0;
}

