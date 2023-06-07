#pragma once
#include <iostream>

void roll(int value, bool pushChecked, bool extraD6Checked)
{
	//store all inputted values
	int all = value + pushChecked + extraD6Checked;
	
	//store result
	int result = 0;
	
	//log each value to console
	std::cout << "Value: " << value << std::endl;
	std::cout << "pushChecked: " << pushChecked << std::endl;
	std::cout << "extraD6Checked: " << extraD6Checked << std::endl;
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
}