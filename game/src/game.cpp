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

//enum to store scenes
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

	raylib::Window window(screenWidth, screenHeight, "Nightpath Publishing One-Page RPGs");
	raylib::Texture2D logo("NPLogo1.png");

	SetTargetFPS(60);

	GuiLoadStyleCyber();
	
	//seed randomizer
	srand(time(nullptr));

	while (!WindowShouldClose())
	{

		BeginDrawing();
		{
			window.ClearBackground(BLACK);
			
			//draw scene based on the current one selected
			switch (currentScene)
			{
			case MenuScene:
				logo.Draw(raylib::Vector2(70, 50), 0.0f, 0.35f);
				DrawMenu();
				break;
			case ChaosRiftsScene:
				ChaosRifts::DrawChaosRifts();
				break;
			case GameTurkeysScene:
				GameTurkeys::DrawGameTurkeys();
				break;
			case CodeisattvasScene:
				Codeisattvas::DrawCodeisattvas();
				break;
			case NSSVScene:
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

//draw menu with buttons to switch between scenes
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

	GuiSetStyle(DEFAULT, TEXT_SIZE, 22);
	GuiLabel(Rectangle{ 65, 1025, 550, 20 }, "Download one-page RPGs and more at nightpathpub.com");
}