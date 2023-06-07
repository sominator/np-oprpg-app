#include "chaosrifts.h"
#include "diceroller.h"

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

void ChaosRifts::Draw()
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
	GuiToggleGroup(Rectangle{ textX + 110, textY + 117, 140, 22 }, "+1d6 Defense; +1d6 Healing", &toggleAuromancerActive);
	
	//skills
	GuiLine(Rectangle{ textX, textY + 130, 500, 30 }, "Skills");

	GuiCheckBox(Rectangle{ textX + 195, textY + 155, 15, 15 }, "Push", &pushChecked);
	GuiCheckBox(Rectangle{ textX + 295, textY + 155, 15, 15 }, "GM +1d6", &extraD6Checked);
	
	if (GuiSpinner(Rectangle{ textX + 80, textY + 175, 90, 22}, "Attack ", &attackValue, 1, 10, attackEdit)) attackEdit = !attackEdit;
	if (GuiSpinner(Rectangle{ textX + 80, textY + 200, 90, 22 }, "Defense ", &defenseValue, 1, 10, defenseEdit)) defenseEdit = !defenseEdit;
	if (GuiSpinner(Rectangle{ textX + 80, textY + 225, 90, 22 }, "Hacking ", &hackingValue, 1, 10, hackingEdit)) hackingEdit = !hackingEdit;
	if (GuiSpinner(Rectangle{ textX + 80, textY + 250, 90, 22 }, "Healing  ", &healingValue, 1, 10, healingEdit)) healingEdit = !healingEdit;
	if (GuiSpinner(Rectangle{ textX + 80, textY + 275, 90, 22 }, "Mancy ", &mancyValue, 1, 10, mancyEdit)) mancyEdit = !mancyEdit;
	if (GuiSpinner(Rectangle{ textX + 80, textY + 300, 90, 22 }, "Negot. ", &negotiationValue, 0, 10, negotiationEdit)) negotiationEdit = !negotiationEdit;
	if (GuiSpinner(Rectangle{ textX + 80, textY + 325, 90, 22 }, "Stealth ", &stealthValue, 1, 10, stealthEdit)) stealthEdit = !stealthEdit;
	if (GuiSpinner(Rectangle{ textX + 80, textY + 350, 90, 22 }, "Thievery ", &thieveryValue, 1, 10, thieveryEdit)) thieveryEdit = !thieveryEdit;
	if (GuiSpinner(Rectangle{ textX + 80, textY + 375, 90, 22 }, "Tumbling ", &tumblingValue, 1, 10, tumblingEdit)) tumblingEdit = !tumblingEdit;
	if (GuiSpinner(Rectangle{ textX + 80, textY + 400, 90, 22 }, "Vehicles ", &vehiclesValue, 1, 10, vehiclesEdit)) vehiclesEdit = !vehiclesEdit;

	if (GuiButton(Rectangle{ textX + 180, textY + 175, 100, 20 }, "Roll")) { roll(attackValue, pushChecked, extraD6Checked); };
	if (GuiButton(Rectangle{ textX + 180, textY + 200, 100, 20 }, "Roll"));
	if (GuiButton(Rectangle{ textX + 180, textY + 225, 100, 20 }, "Roll"));
	if (GuiButton(Rectangle{ textX + 180, textY + 250, 100, 20 }, "Roll"));
	if (GuiButton(Rectangle{ textX + 180, textY + 275, 100, 20 }, "Roll"));
	if (GuiButton(Rectangle{ textX + 180, textY + 300, 100, 20 }, "Roll"));
	if (GuiButton(Rectangle{ textX + 180, textY + 325, 100, 20 }, "Roll"));
	if (GuiButton(Rectangle{ textX + 180, textY + 350, 100, 20 }, "Roll"));
	if (GuiButton(Rectangle{ textX + 180, textY + 375, 100, 20 }, "Roll"));
	if (GuiButton(Rectangle{ textX + 180, textY + 400, 100, 20 }, "Roll"));

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