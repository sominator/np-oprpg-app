#include "raylib-cpp-master/include/raylib-cpp.hpp"
#include "ui.h"
#include "input.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "styles/cyber.h"

int main(void)
{
	const int screenWidth = 640;
	const int screenHeight = 1136;

	raylib::Window window(screenWidth, screenHeight, "raylib-gui-oprpg-app");

	UI ui;
	
	Input input;
	
	SetTargetFPS(60);

	GuiLoadStyleCyber();

	while (!WindowShouldClose())
	{
		input.Update(ui);

		BeginDrawing();
		{
			window.ClearBackground(BLACK);
			
			ui.Draw();

			input.Draw();
		}
		EndDrawing();
	}

	return 0;
}