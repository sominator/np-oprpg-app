#include "raylib-cpp-master/include/raylib-cpp.hpp"
#include "chaosrifts.h"
#include "gameturkeys.h"
#include "codeisattvas.h"
#include "nssv.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "styles/cyber/cyber.h"
#include "styles/candy/candy.h"
#include "styles/jungle/jungle.h"
#include "styles/lavanda/lavanda.h"
#include <iostream>

int main(void)
{
	const int screenWidth = 640;
	const int screenHeight = 1136;

	raylib::Window window(screenWidth, screenHeight, "raylib-gui-oprpg-app");

	SetTargetFPS(60);

	//GuiLoadStyleCyber();
	//GuiLoadStyleCandy();
	//GuiLoadStyleJungle();
	GuiLoadStyleLavanda();

	//seed randomizer
	srand(time(nullptr));

	while (!WindowShouldClose())
	{

		BeginDrawing();
		{
			window.ClearBackground(BLACK);
			
			//ChaosRifts::DrawChaosRifts();
			//GameTurkeys::DrawGameTurkeys();
			//Codeisattvas::DrawCodeisattvas();
			NSSV::DrawNSSV();
		}
		EndDrawing();
	}

	return 0;
}