#include <iostream>
#include <raylib.h>
#include "rutils.h"
#include "gui/gui.h"

int main()
{
	window_init();
	gui_init();

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		auto a = text_init("Hello world", FontSize::Medium, RED, wr_vec2({30, 50}));
		text_draw(a);

		EndDrawing();
	}	 

	gui_deinit();
	window_deinit();

	return 0;
}
