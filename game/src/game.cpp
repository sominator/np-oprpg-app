#include "raylib-cpp-master/include/raylib-cpp.hpp"
#include "menu.h"
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

enum Scenes
{
	MenuScene,
	ChaosRiftsScene,
	GameTurkeysScene,
	CodeisattvasScene,
	NSSVScene
};

Scenes currentScene = MenuScene;

void DrawMenu();

int main(void)
{
	const int screenWidth = 640;
	const int screenHeight = 1136;

	raylib::Window window(screenWidth, screenHeight, "raylib-gui-oprpg-app");
	raylib::Texture2D logo("resources/NPLogo1.png");

	SetTargetFPS(60);

	GuiLoadStyleCyber();
	
	//seed randomizer
	srand(time(nullptr));

	while (!WindowShouldClose())
	{

		BeginDrawing();
		{
			window.ClearBackground(BLACK);
			
			switch (currentScene)
			{
			case MenuScene:
				logo.Draw(50, 50, WHITE);
				DrawMenu();
				break;
			case ChaosRiftsScene:
				logo.Draw(50, 50, WHITE);
				ChaosRifts::DrawChaosRifts();
				break;
			case GameTurkeysScene:
				logo.Draw(50, 50, WHITE);
				GameTurkeys::DrawGameTurkeys();
				break;
			case CodeisattvasScene:
				logo.Draw(50, 50, WHITE);
				Codeisattvas::DrawCodeisattvas();
				break;
			case NSSVScene:
				logo.Draw(50, 50, WHITE);
				NSSV::DrawNSSV();
				break;
			default:
				DrawMenu();
			}

			//back button
			if (currentScene != MenuScene)
			{
				if (GuiButton({ 460, 1060, 100, 24 }, "Back"))
				{
					GuiLoadStyleCyber();
					currentScene = MenuScene;
				};
			}
		}
		EndDrawing();
	}

	return 0;
}

void DrawMenu()
{
	GuiSetStyle(DEFAULT, TEXT_SIZE, 42);

	if (GuiButton(Rectangle{ 125, 250, 400, 60 }, "Chaos Rifts"))
	{
		GuiLoadStyleCyber();
		currentScene = ChaosRiftsScene;
	};
	if (GuiButton(Rectangle{ 125, 350, 400, 60 }, "Game Turkeys"))
	{
		GuiLoadStyleCandy();
		currentScene = GameTurkeysScene;
	};
	if (GuiButton(Rectangle{ 125, 450, 400, 60 }, "{CODE}isattvas"))
	{
		GuiLoadStyleJungle();
		currentScene = CodeisattvasScene;
	};
	if (GuiButton(Rectangle{ 125, 550, 400, 60 }, "Not-So-Super Villains"))
	{
		GuiLoadStyleLavanda();
		currentScene = NSSVScene;
	};
}