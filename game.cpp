#include <iostream>
#include <raylib.h>
#include "rutils.h"
#include "gui/gui.h"
#include "button.h"

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
		enemies_manager.update();
		BeginDrawing();
		ClearBackground(COLOR_GREEN);

		enemies_manager.draw();
		flower_draw();

		// play_button.Draw();
		EndDrawing();
	}

	gui_deinit();
	window_deinit();

	return 0;
}
