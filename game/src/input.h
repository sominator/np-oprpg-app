#pragma once
#include "raylib-cpp-master/include/raylib-cpp.hpp"
#include "ui.h"

struct Input
{
	void Update(UI& ui);

	void Draw();
};