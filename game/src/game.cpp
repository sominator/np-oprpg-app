#include "raylib-cpp-master/include/raylib-cpp.hpp"
#include "chaosrifts.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "styles/cyber.h"

int main(void)
{
	const int screenWidth = 640;
	const int screenHeight = 1136;

	raylib::Window window(screenWidth, screenHeight, "raylib-gui-oprpg-app");

	SetTargetFPS(60);

	GuiLoadStyleCyber();

	while (!WindowShouldClose())
	{

		BeginDrawing();
		{
			window.ClearBackground(BLACK);
			
			DrawChaosRifts();
		}
		EndDrawing();
	}

	return 0;
}