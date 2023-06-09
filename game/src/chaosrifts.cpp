#include "chaosrifts.h"
#include "diceroller.h"
#include <iostream>

float panelX = 50.0f;
float panelY = 60.0f;
float textX = 60.0f;
float textY = 100.0f;

char name[64] = "Name";
bool nameEdit = false;

int hpValue = 3;
bool hpEdit = false;

int dropDownClassActive = 0;
bool dropDownClassEdit = false;

int toggleAuromancerActive = 0;
int toggleNightAgentActive = 0;
int toggleRevolutionaryActive = 0;
int toggleTechnomancerActive = 0;
int toggleTerramancerActive = 0;
int toggleVanguardActive = 0;

int attackValue = 1;
bool attackEdit = false;
int defenseValue = 1;
bool defenseEdit = false;
int hackingValue = 1;
bool hackingEdit = false;
int healingValue = 1;
bool healingEdit = false;
int mancyValue = 1;
bool mancyEdit = false;
int negotiationValue = 1;
bool negotiationEdit = false;
int stealthValue = 1;
bool stealthEdit = false;
int thieveryValue = 1;
bool thieveryEdit = false;
int tumblingValue = 1;
bool tumblingEdit = false;
int vehiclesValue = 1;
bool vehiclesEdit = false;

bool pushChecked = false;
bool extraD6Checked = false;

int attackOutput = 0;
bool attackOutputEdit = false;
int defenseOutput = 0;
bool defenseOutputEdit = false;
int hackingOutput = 0;
bool hackingOutputEdit = false;
int healingOutput = 0;
bool healingOutputEdit = false;
int mancyOutput = 0;
bool mancyOutputEdit = false;
int negotiationOutput = 0;
bool negotiationOutputEdit = false;
int stealthOutput = 0;
bool stealthOutputEdit = false;
int thieveryOutput = 0;
bool thieveryOutputEdit = false;
int tumblingOutput = 0;
bool tumblingOutputEdit = false;
int vehiclesOutput = 0;
bool vehiclesOutputEdit = false;

bool chaosToken1Checked = false;
bool chaosToken2Checked = false;
bool chaosToken3Checked = false;

void DrawChaosRifts()
{
	if (dropDownClassEdit) GuiLock();

	GuiSetStyle(DEFAULT, TEXT_SIZE, 22);

	GuiLabel(Rectangle{ 170, 20, 500, 25 }, "ENTROMANCY: CHAOS RIFTS");

	//panels
	GuiPanel(Rectangle{ panelX, panelY, 525, 560 }, "Character Info");
	GuiPanel(Rectangle{ panelX, panelY + 575, 525, 300 }, "GM Info");

	//name text box and HP value box
	GuiSetStyle(TEXTBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
	if (GuiTextBox(Rectangle{ textX, textY, 300, 30 }, name, 64, nameEdit)) nameEdit = !nameEdit;
	if (GuiSpinner(Rectangle{ textX + 370, textY, 125, 30 }, "HP ", &hpValue, 0, 10, hpEdit)) hpEdit = !hpEdit;

	//classes
	GuiLine(Rectangle{ textX, textY + 45, 500, 30 }, "Class");

	//conditional rendering of class skills based on dropdown selection
	switch (dropDownClassActive)
	{
	case (0):
		GuiToggleGroup(Rectangle{ textX + 110, textY + 117, 140, 22 }, "+1d6 Defense; +1d6 Healing", &toggleAuromancerActive);
		break;
	case (1):
		GuiToggleGroup(Rectangle{ textX + 110, textY + 117, 140, 22 }, "+1d6 Stealth; +1d6 Tumbling", &toggleNightAgentActive);
		break;
	case(2):
		GuiToggleGroup(Rectangle{ textX + 110, textY + 117, 140, 22 }, "+1d6 Attack; +1d6 Negot.", &toggleRevolutionaryActive);
		break;
	case(3):
		GuiToggleGroup(Rectangle{ textX + 110, textY + 117, 140, 22 }, "+1d6 Hacking; +1d6 Vehicles", &toggleTechnomancerActive);
		break;
	case(4):
		GuiToggleGroup(Rectangle{ textX + 110, textY + 117, 140, 22 }, "+1d6 Healing; +1d6 Mancy", &toggleTerramancerActive);
		break;
	default:
		GuiToggleGroup(Rectangle{ textX + 110, textY + 117, 140, 22 }, "+1d6 Stealth; +1d6 Thievery", &toggleVanguardActive);
	};

	//skills
	GuiLine(Rectangle{ textX, textY + 130, 500, 30 }, "Skills");

	GuiCheckBox(Rectangle{ textX + 195, textY + 155, 15, 15 }, "Push", &pushChecked);
	GuiCheckBox(Rectangle{ textX + 295, textY + 155, 15, 15 }, "GM +1d6", &extraD6Checked);

	if (GuiSpinner(Rectangle{ textX + 80, textY + 175, 90, 22 }, "Attack ", &attackValue, 1, 10, attackEdit)) attackEdit = !attackEdit;
	if (GuiSpinner(Rectangle{ textX + 80, textY + 200, 90, 22 }, "Defense ", &defenseValue, 1, 10, defenseEdit)) defenseEdit = !defenseEdit;
	if (GuiSpinner(Rectangle{ textX + 80, textY + 225, 90, 22 }, "Hacking ", &hackingValue, 1, 10, hackingEdit)) hackingEdit = !hackingEdit;
	if (GuiSpinner(Rectangle{ textX + 80, textY + 250, 90, 22 }, "Healing  ", &healingValue, 1, 10, healingEdit)) healingEdit = !healingEdit;
	if (GuiSpinner(Rectangle{ textX + 80, textY + 275, 90, 22 }, "Mancy ", &mancyValue, 1, 10, mancyEdit)) mancyEdit = !mancyEdit;
	if (GuiSpinner(Rectangle{ textX + 80, textY + 300, 90, 22 }, "Negot. ", &negotiationValue, 0, 10, negotiationEdit)) negotiationEdit = !negotiationEdit;
	if (GuiSpinner(Rectangle{ textX + 80, textY + 325, 90, 22 }, "Stealth ", &stealthValue, 1, 10, stealthEdit)) stealthEdit = !stealthEdit;
	if (GuiSpinner(Rectangle{ textX + 80, textY + 350, 90, 22 }, "Thievery ", &thieveryValue, 1, 10, thieveryEdit)) thieveryEdit = !thieveryEdit;
	if (GuiSpinner(Rectangle{ textX + 80, textY + 375, 90, 22 }, "Tumbling ", &tumblingValue, 1, 10, tumblingEdit)) tumblingEdit = !tumblingEdit;
	if (GuiSpinner(Rectangle{ textX + 80, textY + 400, 90, 22 }, "Vehicles ", &vehiclesValue, 1, 10, vehiclesEdit)) vehiclesEdit = !vehiclesEdit;

	//attack roll -- revolutionaries can select to receive a bonus
	if (GuiButton(Rectangle{ textX + 180, textY + 175, 100, 20 }, "Roll"))
	{
		std::cout << "Rolling Attack..." << std::endl;
		int classBonus = 0;
		if (dropDownClassActive == 2)
		{
			std::cout << "Revolutionary selected..." << std::endl;
			if (toggleRevolutionaryActive == 0)
			{
				std::cout << "Class Attack bonus selected..." << std::endl;
				classBonus = 1;
			}
		}
		//attackOutput = RollSkill(attackValue, pushChecked, extraD6Checked, classBonus);
		TestRoll(attackValue, pushChecked, extraD6Checked, classBonus);
	};

	//defense roll -- auromancers can select to receive a bonus
	if (GuiButton(Rectangle{ textX + 180, textY + 200, 100, 20 }, "Roll"))
	{
		std::cout << "Rolling Defense..." << std::endl;
		int classBonus = 0;
		if (dropDownClassActive == 0)
		{
			std::cout << "Auromancer selected..." << std::endl;
			if (toggleAuromancerActive == 0)
			{
				std::cout << "Class Defense bonus selected..." << std::endl;
				classBonus = 1;
			}
		}
		defenseOutput = RollSkill(defenseValue, pushChecked, extraD6Checked, classBonus);
	}

	//hacking roll -- technomancers can select to receive a bonus
	if (GuiButton(Rectangle{ textX + 180, textY + 225, 100, 20 }, "Roll"))
	{
		std::cout << "Rolling Hacking..." << std::endl;
		int classBonus = 0;
		if (dropDownClassActive == 3)
		{
			std::cout << "Technomancer selected..." << std::endl;
			if (toggleTechnomancerActive == 0)
			{
				std::cout << "Class Hacking bonus selected..." << std::endl;
				classBonus = 1;
			}
		}
		hackingOutput = RollSkill(hackingValue, pushChecked, extraD6Checked, classBonus);
	}

	//healing roll -- auromancers and terramancers can select to receive a bonus
	if (GuiButton(Rectangle{ textX + 180, textY + 250, 100, 20 }, "Roll"))
	{
		std::cout << "Rolling Healing..." << std::endl;
		int classBonus = 0;
		if (dropDownClassActive == 0)
		{
			std::cout << "Auromancer selected..." << std::endl;
			if (toggleAuromancerActive == 1)
			{
				std::cout << "Class Healing bonus selected..." << std::endl;
				classBonus = 1;
			}
		}
		else if (dropDownClassActive == 4)
		{
			std::cout << "Terramancer selected..." << std::endl;
			if (toggleTerramancerActive == 0)
			{
				std::cout << "Class Healing bonus selected..." << std::endl;
				classBonus = 1;
			}
		}
		healingOutput = RollSkill(healingValue, pushChecked, extraD6Checked, classBonus);
	}

	//mancy roll -- terramancers can select to receive a bonus
	if (GuiButton(Rectangle{ textX + 180, textY + 275, 100, 20 }, "Roll"))
	{
		std::cout << "Rolling Mancy..." << std::endl;
		int classBonus = 0;
		if (dropDownClassActive == 4)
		{
			std::cout << "Terramancer selected..." << std::endl;
			if (toggleTerramancerActive == 1)
			{
				std::cout << "Class Mancy bonus selected..." << std::endl;
				classBonus = 1;
			}
		}
		mancyOutput = RollSkill(mancyValue, pushChecked, extraD6Checked, classBonus);
	}

	//negotiation roll -- revolutionaries can select to receive a bonus
	if (GuiButton(Rectangle{ textX + 180, textY + 300, 100, 20 }, "Roll"))
	{
		std::cout << "Rolling Negotiation..." << std::endl;
		int classBonus = 0;
		if (dropDownClassActive == 2)
		{
			std::cout << "Revolutionary selected..." << std::endl;
			if (toggleRevolutionaryActive == 1)
			{
				std::cout << "Class Negotiation bonus selected..." << std::endl;
				classBonus = 1;
			}
		}
		negotiationOutput = RollSkill(negotiationValue, pushChecked, extraD6Checked, classBonus);
	}
	
	//stealth roll - night agents and vanguards can select to receive a bonus
	if (GuiButton(Rectangle{ textX + 180, textY + 325, 100, 20 }, "Roll"))
	{
		std::cout << "Rolling Stealth..." << std::endl;
		int classBonus = 0;
		if (dropDownClassActive == 1)
		{
			std::cout << "NIGHT Agent selected..." << std::endl;
			if (toggleNightAgentActive == 0)
			{
				std::cout << "Class Stealth bonus selected..." << std::endl;
				classBonus = 1;
			}
		}
		else if (dropDownClassActive == 5)
		{
			std::cout << "Vanguard selected..." << std::endl;
			if (toggleVanguardActive == 0)
			{
				std::cout << "Class Stealth bonus selected..." << std::endl;
				classBonus = 1;
			}
		}
		stealthOutput = RollSkill(stealthValue, pushChecked, extraD6Checked, classBonus);
	}
	
	//thievery roll - vanguards can select to receive a bonus
	if (GuiButton(Rectangle{ textX + 180, textY + 350, 100, 20 }, "Roll"))
	{
		std::cout << "Rolling Thievery..." << std::endl;
		int classBonus = 0;
		if (dropDownClassActive == 5)
		{
			std::cout << "Vanguard selected..." << std::endl;
			if (toggleVanguardActive == 1)
			{
				std::cout << "Class Thievery bonus selected..." << std::endl;
				classBonus = 1;
			}
		}
		thieveryOutput  = RollSkill(thieveryValue, pushChecked, extraD6Checked, classBonus);
	}
	
	//tumbling roll - night agents can select to receive a bonus
	if (GuiButton(Rectangle{ textX + 180, textY + 375, 100, 20 }, "Roll"))
	{
		std::cout << "Rolling Tumbling..." << std::endl;
		int classBonus = 0;
		if (dropDownClassActive == 1)
		{
			std::cout << "NIGHT Agent selected..." << std::endl;
			if (toggleNightAgentActive == 1)
			{
				std::cout << "Class Tumbling bonus selected..." << std::endl;
				classBonus = 1;
			}
		}
		tumblingOutput = RollSkill(tumblingValue, pushChecked, extraD6Checked, classBonus);
	}
	
	//vehicles roll - technomancers can select to receive a bonus
	if (GuiButton(Rectangle{ textX + 180, textY + 400, 100, 20 }, "Roll"))
	{
		std::cout << "Rolling Vehicles..." << std::endl;
		int classBonus = 0;
		if (dropDownClassActive == 3)
		{
			std::cout << "Technomancer selected..." << std::endl;
			if (toggleTechnomancerActive == 1)
			{
				std::cout << "Class Vehicles bonus selected..." << std::endl;
				classBonus = 1;
			}
		}
		vehiclesOutput = RollSkill(vehiclesValue, pushChecked, extraD6Checked, classBonus);
	}

	if (GuiValueBox(Rectangle{ textX + 370, textY + 175, 125, 20 }, "Output: ", &attackOutput, 0, 100, attackOutputEdit)) attackOutputEdit = !attackOutputEdit;
	if (GuiValueBox(Rectangle{ textX + 370, textY + 200, 125, 20 }, "Output: ", &defenseOutput, 0, 100, defenseOutputEdit)) defenseOutputEdit = !defenseOutputEdit;
	if (GuiValueBox(Rectangle{ textX + 370, textY + 225, 125, 20 }, "Output: ", &hackingOutput, 0, 100, hackingOutputEdit)) hackingOutputEdit = !hackingOutputEdit;
	if (GuiValueBox(Rectangle{ textX + 370, textY + 250, 125, 20 }, "Output: ", &healingOutput, 0, 100, healingOutputEdit)) healingOutputEdit = !healingOutputEdit;
	if (GuiValueBox(Rectangle{ textX + 370, textY + 275, 125, 20 }, "Output: ", &mancyOutput, 0, 100, mancyOutputEdit)) mancyOutputEdit = !mancyOutputEdit;
	if (GuiValueBox(Rectangle{ textX + 370, textY + 300, 125, 20 }, "Output: ", &negotiationOutput, 0, 100, negotiationOutputEdit)) negotiationOutputEdit = !negotiationOutputEdit;
	if (GuiValueBox(Rectangle{ textX + 370, textY + 325, 125, 20 }, "Output: ", &stealthOutput, 0, 100, stealthOutputEdit)) stealthOutputEdit = !stealthOutputEdit;
	if (GuiValueBox(Rectangle{ textX + 370, textY + 350, 125, 20 }, "Output: ", &thieveryOutput, 0, 100, thieveryOutputEdit)) thieveryOutputEdit = !thieveryOutputEdit;
	if (GuiValueBox(Rectangle{ textX + 370, textY + 375, 125, 20 }, "Output: ", &tumblingOutput, 0, 100, tumblingOutputEdit)) tumblingOutputEdit = !tumblingOutputEdit;
	if (GuiValueBox(Rectangle{ textX + 370, textY + 400, 125, 20 }, "Output: ", &vehiclesOutput, 0, 100, vehiclesOutputEdit)) vehiclesOutputEdit = !vehiclesOutputEdit;

	//missions
	GuiLine(Rectangle{ textX, textY + 430, 500, 30 }, "Mission Objective");
	if (GuiButton(Rectangle{ textX, textY + 465, 100, 20 }, "Roll"));
	GuiLabel(Rectangle{ textX + 150, textY + 425, 100, 100 }, "Text");

	//encounters
	GuiLine(Rectangle{ textX, textY + 570, 500, 30 }, "Encounter");
	if (GuiButton(Rectangle{ textX, textY + 605, 100, 20 }, "Roll"));
	GuiLabel(Rectangle{ textX + 150, textY + 575, 100, 100 }, "Text");

	//chaos rifts
	GuiLine(Rectangle{ textX, textY + 650, 500, 30 }, "Chaos Rift");
	if (GuiButton(Rectangle{ textX, textY + 685, 100, 20 }, "Roll"));
	GuiLabel(Rectangle{ textX + 150, textY + 645, 100, 100 }, "Text");

	//chaos meter
	GuiLine(Rectangle{ textX, textY + 730, 500, 30 }, "Chaos Meter");
	GuiCheckBox(Rectangle{ textX + 50, textY + 760, 15, 15 }, "Token 1", &chaosToken1Checked);
	GuiCheckBox(Rectangle{ textX + 200, textY + 760, 15, 15 }, "Token 2", &chaosToken2Checked);
	GuiCheckBox(Rectangle{ textX + 350, textY + 760, 15, 15 }, "Token 3", &chaosToken3Checked);

	//back button
	if (GuiButton({ textX + 400, textY + 870, 100, 24 }, "Back"));

	//class dropdown
	GuiUnlock();
	GuiSetStyle(DROPDOWNBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
	if (GuiDropdownBox(Rectangle{ textX, textY + 80, 500, 30 },
		" Auromancer; NIGHT Agent; Revolutionary; Technomancer; Terramancer; Vanguard",
		&dropDownClassActive, dropDownClassEdit)) dropDownClassEdit = !dropDownClassEdit;
}