#include "ui.h"

raylib::Color textColor = Color{81, 191, 211, 255};

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

bool auromancerDefenseChecked = false;
bool auromancerHealingChecked = false;
bool nightAgentStealthChecked = false;
bool nightAgentTumblingChecked = false;
bool revolutionaryAttackChecked = false;
bool revolutionaryNegotiationChecked = false;
bool technomancerHackingChecked = false;
bool technomancerVehiclesChecked = false;
bool terramancerHealingChecked = false;
bool terramancerMancyChecked = false;
bool vanguardStealthChecked = false;
bool vanguardThieveryChecked = false;

bool attackChecked = false;
bool defenseChecked = false;
bool hackingChecked = false;
bool healingChecked = false;
bool mancyChecked = false;
bool negotiationChecked = false;
bool stealthChecked = false;
bool thieveryChecked = false;
bool tumblingChecked = false;
bool vehiclesChecked = false;

bool pushChecked = false;
bool extraD6Checked = false;

int attackValue = 0;
bool attackEdit = false;

int dropDownMissionActive = 0;
bool dropDownMissionEdit = false;

int dropDownEncounterActive = 0;
bool dropDownEncounterEdit = false;

int dropDownChaosRiftActive = 0;
bool dropDownChaosRiftEdit = false;

bool chaosToken1Checked = false;
bool chaosToken2Checked = false;
bool chaosToken3Checked = false;

int toggleActive = 0;

void UI::Draw()
{
	if (dropDownClassEdit || dropDownMissionEdit) GuiLock();

	textColor.DrawText("ENTROMANCY: CHAOS RIFTS", 155, 25, 20);

	GuiSetStyle(DEFAULT, TEXT_SIZE, 22);

	//panels
	GuiPanel(Rectangle{ panelX, panelY, 525, 560 }, "Character Info");
	GuiPanel(Rectangle{ panelX, panelY + 575, 525, 300 }, "GM Info");

	//name text box and HP value box
	GuiSetStyle(TEXTBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
	if (GuiTextBox(Rectangle{ textX, textY, 300, 30 }, name, 64, nameEdit)) nameEdit = !nameEdit;
	if (GuiSpinner(Rectangle{ textX + 370, textY, 125, 30 }, "HP ", &hpValue, 0, 10, hpEdit)) hpEdit = !hpEdit;

	//classes
	GuiLine(Rectangle{ textX, textY + 45, 500, 30 }, "Class");
	GuiCheckBox(Rectangle{ textX + 80, textY + 120, 15, 15 }, "+1d6 Defense", &auromancerDefenseChecked);
	GuiCheckBox(Rectangle{ textX + 300, textY + 120, 15, 15 }, "+1d6 Healing", &auromancerHealingChecked);
	
	//skills
	GuiLine(Rectangle{ textX, textY + 130, 500, 30 }, "Skills");

	GuiCheckBox(Rectangle{ textX + 205, textY + 155, 15, 15 }, "Push", &pushChecked);
	GuiCheckBox(Rectangle{ textX + 295, textY + 155, 15, 15 }, "Extra d6", &extraD6Checked);
	
	GuiCheckBox(Rectangle{ textX, textY + 175, 15, 15 }, "+1d6 Attack", &attackChecked);
	GuiCheckBox(Rectangle{ textX, textY + 200, 15, 15 }, "+1d6 Defense", &defenseChecked);
	GuiCheckBox(Rectangle{ textX, textY + 225, 15, 15 }, "+1d6 Hacking", &hackingChecked);
	GuiCheckBox(Rectangle{ textX, textY + 250, 15, 15 }, "+1d6 Healing", &healingChecked);
	GuiCheckBox(Rectangle{ textX, textY + 275, 15, 15 }, "+1d6 Mancy", &mancyChecked);
	GuiCheckBox(Rectangle{ textX, textY + 300, 15, 15 }, "+1d6 Negotiation", &negotiationChecked);
	GuiCheckBox(Rectangle{ textX, textY + 325, 15, 15 }, "+1d6 Stealth", &stealthChecked);
	GuiCheckBox(Rectangle{ textX, textY + 350, 15, 15 }, "+1d6 Thievery", &thieveryChecked);
	GuiCheckBox(Rectangle{ textX, textY + 375, 15, 15 }, "+1d6 Tumbling", &tumblingChecked);
	GuiCheckBox(Rectangle{ textX, textY + 400, 15, 15 }, "+1d6 Vehicles", &vehiclesChecked);

	if (GuiButton(Rectangle{ textX + 170, textY + 175, 100, 20 }, "Roll"));
	if (GuiButton(Rectangle{ textX + 170, textY + 200, 100, 20 }, "Roll"));
	if (GuiButton(Rectangle{ textX + 170, textY + 225, 100, 20 }, "Roll"));
	if (GuiButton(Rectangle{ textX + 170, textY + 250, 100, 20 }, "Roll"));
	if (GuiButton(Rectangle{ textX + 170, textY + 275, 100, 20 }, "Roll"));
	if (GuiButton(Rectangle{ textX + 170, textY + 300, 100, 20 }, "Roll"));
	if (GuiButton(Rectangle{ textX + 170, textY + 325, 100, 20 }, "Roll"));
	if (GuiButton(Rectangle{ textX + 170, textY + 350, 100, 20 }, "Roll"));
	if (GuiButton(Rectangle{ textX + 170, textY + 375, 100, 20 }, "Roll"));
	if (GuiButton(Rectangle{ textX + 170, textY + 400, 100, 20 }, "Roll"));

	if (GuiValueBox(Rectangle{ textX + 370, textY + 175, 125, 20 }, "Output: ", &attackValue, 0, 20, attackEdit)) attackEdit= !attackEdit;
	if (GuiValueBox(Rectangle{ textX + 370, textY + 200, 125, 20 }, "Output: ", &attackValue, 0, 20, attackEdit)) attackEdit = !attackEdit;
	if (GuiValueBox(Rectangle{ textX + 370, textY + 225, 125, 20 }, "Output: ", &attackValue, 0, 20, attackEdit)) attackEdit = !attackEdit;
	if (GuiValueBox(Rectangle{ textX + 370, textY + 250, 125, 20 }, "Output: ", &attackValue, 0, 20, attackEdit)) attackEdit = !attackEdit;
	if (GuiValueBox(Rectangle{ textX + 370, textY + 275, 125, 20 }, "Output: ", &attackValue, 0, 20, attackEdit)) attackEdit = !attackEdit;
	if (GuiValueBox(Rectangle{ textX + 370, textY + 300, 125, 20 }, "Output: ", &attackValue, 0, 20, attackEdit)) attackEdit = !attackEdit;
	if (GuiValueBox(Rectangle{ textX + 370, textY + 325, 125, 20 }, "Output: ", &attackValue, 0, 20, attackEdit)) attackEdit = !attackEdit;
	if (GuiValueBox(Rectangle{ textX + 370, textY + 350, 125, 20 }, "Output: ", &attackValue, 0, 20, attackEdit)) attackEdit = !attackEdit;
	if (GuiValueBox(Rectangle{ textX + 370, textY + 375, 125, 20 }, "Output: ", &attackValue, 0, 20, attackEdit)) attackEdit = !attackEdit;
	if (GuiValueBox(Rectangle{ textX + 370, textY + 400, 125, 20 }, "Output: ", &attackValue, 0, 20, attackEdit)) attackEdit = !attackEdit;

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

	//class dropdown
	GuiUnlock();
	GuiSetStyle(DROPDOWNBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
	if (GuiDropdownBox(Rectangle{ textX, textY + 80, 500, 30 },
		" Auromancer; NIGHT Agent; Revolutionary; Technomancer; Terramancer; Vanguard",
		&dropDownClassActive, dropDownClassEdit)) dropDownClassEdit = !dropDownClassEdit;
}