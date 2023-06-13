#include <menu.h>

namespace Menu 
{
	void DrawMenu()
	{
		GuiSetStyle(DEFAULT, TEXT_SIZE, 42);

		if (GuiButton(Rectangle{ 125, 250, 400, 60 }, "Chaos Rifts"))
		{

		};
		if (GuiButton(Rectangle{ 125, 350, 400, 60 }, "Game Turkeys"))
		{

		};
		if (GuiButton(Rectangle{ 125, 450, 400, 60 }, "{CODE}isattvas"))
		{

		};
		if (GuiButton(Rectangle{ 125, 550, 400, 60 }, "Not-So-Super Villains"))
		{

		};
	}
}