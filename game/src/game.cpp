#include "raylib-cpp-master/include/raylib-cpp.hpp"
#include "chaosrifts.h"
#include "gameturkeys.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "styles/cyber/cyber.h"
#include "styles/candy/candy.h"
#include <iostream>

int main(void)
{
	const int screenWidth = 640;
	const int screenHeight = 1136;

	raylib::Window window(screenWidth, screenHeight, "raylib-gui-oprpg-app");

	SetTargetFPS(60);

	//GuiLoadStyleCyber();
	GuiLoadStyleCandy();

	//seed randomizer
	srand(time(nullptr));

	while (!WindowShouldClose())
	{

		BeginDrawing();
		{
			window.ClearBackground(BLACK);
			
			//DrawChaosRifts();
			GameTurkeys::DrawGameTurkeys();
		}
		EndDrawing();
	}

	return 0;
}