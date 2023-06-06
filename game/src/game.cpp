#include "raylib-cpp-master/include/raylib-cpp.hpp"
#include "chaosrifts.h"
#include "input.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "styles/cyber.h"

int main(void)
{
	const int screenWidth = 640;
	const int screenHeight = 1136;

	raylib::Window window(screenWidth, screenHeight, "raylib-gui-oprpg-app");

	ChaosRifts chaosRifts;
	
	Input input;
	
	SetTargetFPS(60);

	GuiLoadStyleCyber();

	while (!WindowShouldClose())
	{
		input.Update(chaosRifts);

		BeginDrawing();
		{
			window.ClearBackground(BLACK);
			
			chaosRifts.Draw();

			input.Draw();
		}
		EndDrawing();
	}

	return 0;
}