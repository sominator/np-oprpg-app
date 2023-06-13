#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

std::string RollSkill(int value, bool pushChecked, bool extraD6Checked, int bonus);

int RollSkillOLD(int value, bool pushChecked, bool extraD6Checked, int classBonus);

int RollText(int number);