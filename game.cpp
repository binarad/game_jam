#include <iostream>
#include <raylib.h>
#include "rutils.h"
#include "gui/gui.h"
#include "button.h"

const Color COLOR_YELLOW = GetColor(0xffffa7ff);
const Color COLOR_GREEN = GetColor(0x013220ff);

int main()
{
	window_init();
	gui_init();

	bool close_window = false;
	Button play_button(Rectangle{50.0f, 50.0f, 20.0f, 10.0f}, COLOR_YELLOW, COLOR_GREEN, "PLAY");

	while (!WindowShouldClose() && !close_window)
	{
		if (play_button.Hover(GetMousePosition()))
		{
			play_button.color = COLOR_GREEN;
			play_button.label_color = COLOR_YELLOW;
		}
		else
		{
			play_button.color = COLOR_YELLOW;
			play_button.label_color = COLOR_GREEN;
		}

		BeginDrawing();
		ClearBackground(COLOR_GREEN);

		play_button.Draw();
		EndDrawing();
	}

	gui_deinit();
	window_deinit();

	return 0;
}
