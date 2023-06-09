#pragma once
#include <iostream>

int RollSkill(int value, bool pushChecked, bool extraD6Checked, int classBonus)
{
	//store all inputted values
	int all = value + pushChecked + extraD6Checked + classBonus;
	
	//store result
	int result = 0;
	
	//log each value to console
	std::cout << "Value: " << value << std::endl;
	std::cout << "pushChecked: " << pushChecked << std::endl;
	std::cout << "extraD6Checked: " << extraD6Checked << std::endl;
	std::cout << "classBonus: " << classBonus << std::endl;
	std::cout << "All: " << all << std::endl;

	//roll d6 for each value
	for (int i = 0; i < all; i++)
	{
		int roll = (rand() % 6) + 1;
		result += roll;
		std::cout << "Roll " << i + 1 << ": " << roll << std::endl;
	}

	//log result to console
	std::cout << "Result: " << result << std::endl;
	std::cout << "-----" << std::endl;

	return result;
}

std::string TestRoll(int value, bool pushChecked, bool extraD6Checked, int classBonus)
{
	//store all inputted values
	int all = value + pushChecked + extraD6Checked + classBonus;

	//store result
	std::vector<int> rolls;
	std::string result;

	//log each value to console
	std::cout << "Value: " << value << std::endl;
	std::cout << "pushChecked: " << pushChecked << std::endl;
	std::cout << "extraD6Checked: " << extraD6Checked << std::endl;
	std::cout << "classBonus: " << classBonus << std::endl;
	std::cout << "All: " << all << std::endl;

	//roll d6 for each value
	for (int i = 0; i < all; i++)
	{
		int roll = (rand() % 6) + 1;
		rolls.push_back(roll);
		std::cout << "Roll " << i + 1 << ": " << roll << std::endl;
	}

	result = std::to_string(rolls[0]);
	for (int i = 1; i < rolls.size(); i++)
	{
		result += ", ";
		result += std::to_string(rolls[i]);
	}
	//log result to console
	std::cout << "Result: " << result << std::endl;
	std::cout << "-----" << std::endl;

	return result;
}