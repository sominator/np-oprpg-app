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

enum ClassChoice 
{
	Auromancer,
	NightAgent,
	Revolutionary,
	Technomancer,
	Terramancer,
	Vanguard
};

int dropDownClassActive = Auromancer;
bool dropDownClassEdit = false;

enum ClassSkill
{
	FirstSkill,
	SecondSkill
};

int toggleAuromancerActive = FirstSkill;
int toggleNightAgentActive = FirstSkill;
int toggleRevolutionaryActive = FirstSkill;
int toggleTechnomancerActive = FirstSkill;
int toggleTerramancerActive = FirstSkill;
int toggleVanguardActive = FirstSkill;

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

std::string attackOutput;
std::string defenseOutput;
std::string hackingOutput;
std::string healingOutput;
std::string mancyOutput;
std::string negotiationOutput;
std::string stealthOutput;
std::string thieveryOutput;
std::string tumblingOutput;
std::string vehiclesOutput;

std::string missionText;

std::vector<std::string> missionObjectives =
{
	"Break into the Presidio to seal the entropy portals",
	"Lockdown the rager outbreak in New Castro",
	"Protect the Golden Gate Bridge from technodragon\ndestruction",
	"Assist shadow dragons in defending the Richmond District",
	"Prevent the release of entropic beasts in the undercity",
	"Escort chronomancers to the fusion site in Downtown"
};

std::string encounterText;

std::vector<std::string> encounters = 
{
	"Defeat the chaos beasts that have appeared in your\npath (Attack)",
	"Protect yourself from an attack by defective Unaligned\ndrones (Defense)",
	"Redirect power from a ceridium core to NIGHT's\nmainframes (Hacking)",
	"Mend a group of Aurikar agents to return to battle\n(Healing)",
	"Help a group of gnome scientists to extract blue\norichalcum from an Orichite Age artifact (Mancy)",
	"Fast talk your way past suspicious guards into a protected\ndwarven safehouse (Negotiation)",
	"Sneak by a group of agitated ragers (Stealth)",
	"Liberate a ceridium power source from a cybernetics\nfacility (Thievery)",
	"Dodge between the debris from an overhead battle between\ndragons and cerucopters (Tumbling)",
	"Race through the undercity to prevent a cultist attempt\nto open a Chaos Rift (Vehicles)"
};

std::string chaosRiftText;

std::vector<std::string> chaosRifts = 
{
	"You engage in battle with a group of ENTROPIC BEASTS.\n"
	"Each player rolls Attack, Defense, or Tumbling. Success\n"
	"grants you +1 HP, even above the normal amount of 3; failure\n"
	"removes 1 HP. Reset the Chaos Meter.",
	//line break for readability
	"You're thrust into an inter-factional race to seal a\n"
	"Chaos Rift and retrieve an ORICHITE ARTIFACT. Each player\n"
	"rolls Negotiation, Thievery, or Vehicles. Success grants you\n"
	"an automatic success on an upcoming roll (player's choice);\n"
	"failure incurs an automatic failure on an upcoming roll\n"
	"(GM's choice). Reset the Chaos Meter.",
	//line break for readability
	"You become enmeshed in the technomagical web of the\n"
	"SIGIL'S NETWORK. Each player rolls Hacking, Mancy, or\n"
	"Stealth. Success grants a +1D6 bonus to one of your existing\n"
	"skills (player's choice); failure incurs a -1D6 penalty to it\n"
	"(GM's choice). Reset the Chaos Meter.",
	//line break for readability
	"If you haven't already entered a Chaos Rift, roll 1d4 again to\n"
	"enter a different Chaos Rift than this one. If you have already\n"
	"entered a Chaos Rift, you've stumbled into a DRAGON BATTLE\n"
	"vying for control over the district. Each player rolls a skill\n"
	"of their choice. A success by all players automatically\n"
	"completes one of your Encounters (GM's choice) and resets\n"
	"the Chaos Meter; a failure by all players ends the game.\n"
	"A combination of successes and failures resets the\n"
	"Chaos Meter, with no benefit or penalty."
};

bool chaosToken1Checked = false;
bool chaosToken2Checked = false;
bool chaosToken3Checked = false;

void DrawChaosRifts()
{
	if (dropDownClassEdit) GuiLock();

	GuiSetStyle(DEFAULT, TEXT_SIZE, 22);
	GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);

	GuiLabel(Rectangle{ 170, 20, 500, 25 }, "ENTROMANCY: CHAOS RIFTS");

	//panels
	GuiPanel(Rectangle{ panelX, panelY, 545, 560 }, "Character Info");
	GuiPanel(Rectangle{ panelX, panelY + 575, 545, 400 }, "GM Info");

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

	GuiCheckBox(Rectangle{ textX + 90, textY + 155, 15, 15 }, "Push", &pushChecked);
	GuiCheckBox(Rectangle{ textX + 180, textY + 155, 15, 15 }, "+1d6", &extraD6Checked);
	if (GuiSpinner(Rectangle{ textX + 80, textY + 175, 90, 22 }, "Attack ", &attackValue, 1, 10, attackEdit)) attackEdit = !attackEdit;
	if (GuiSpinner(Rectangle{ textX + 80, textY + 200, 90, 22 }, "Defense ", &defenseValue, 1, 10, defenseEdit)) defenseEdit = !defenseEdit;
	if (GuiSpinner(Rectangle{ textX + 80, textY + 225, 90, 22 }, "Hacking ", &hackingValue, 1, 10, hackingEdit)) hackingEdit = !hackingEdit;
	if (GuiSpinner(Rectangle{ textX + 80, textY + 250, 90, 22 }, "Healing ", &healingValue, 1, 10, healingEdit)) healingEdit = !healingEdit;
	if (GuiSpinner(Rectangle{ textX + 80, textY + 275, 90, 22 }, "Mancy ", &mancyValue, 1, 10, mancyEdit)) mancyEdit = !mancyEdit;
	if (GuiSpinner(Rectangle{ textX + 80, textY + 300, 90, 22 }, "Negot. ", &negotiationValue, 0, 10, negotiationEdit)) negotiationEdit = !negotiationEdit;
	if (GuiSpinner(Rectangle{ textX + 80, textY + 325, 90, 22 }, "Stealth ", &stealthValue, 1, 10, stealthEdit)) stealthEdit = !stealthEdit;
	if (GuiSpinner(Rectangle{ textX + 80, textY + 350, 90, 22 }, "Thievery ", &thieveryValue, 1, 10, thieveryEdit)) thieveryEdit = !thieveryEdit;
	if (GuiSpinner(Rectangle{ textX + 80, textY + 375, 90, 22 }, "Tumbling ", &tumblingValue, 1, 10, tumblingEdit)) tumblingEdit = !tumblingEdit;
	if (GuiSpinner(Rectangle{ textX + 80, textY + 400, 90, 22 }, "Vehicles ", &vehiclesValue, 1, 10, vehiclesEdit)) vehiclesEdit = !vehiclesEdit;

	//attack roll -- revolutionaries can select to receive a bonus
	if (GuiButton(Rectangle{ textX + 180, textY + 175, 60, 20 }, "Roll"))
	{
		std::cout << "Rolling Attack..." << std::endl;
		int classBonus = 0;
		if (dropDownClassActive == Revolutionary)
		{
			std::cout << "Revolutionary selected..." << std::endl;
			if (toggleRevolutionaryActive == FirstSkill)
			{
				std::cout << "Class Attack bonus selected..." << std::endl;
				classBonus = 1;
			}
		}
		attackOutput = RollSkill(attackValue, pushChecked, extraD6Checked, classBonus);
	};

	//defense roll -- auromancers can select to receive a bonus
	if (GuiButton(Rectangle{ textX + 180, textY + 200, 60, 20 }, "Roll"))
	{
		std::cout << "Rolling Defense..." << std::endl;
		int classBonus = 0;
		if (dropDownClassActive == Auromancer)
		{
			std::cout << "Auromancer selected..." << std::endl;
			if (toggleAuromancerActive == FirstSkill)
			{
				std::cout << "Class Defense bonus selected..." << std::endl;
				classBonus = 1;
			}
		}
		defenseOutput = RollSkill(defenseValue, pushChecked, extraD6Checked, classBonus);
	}

	//hacking roll -- technomancers can select to receive a bonus
	if (GuiButton(Rectangle{ textX + 180, textY + 225, 60, 20 }, "Roll"))
	{
		std::cout << "Rolling Hacking..." << std::endl;
		int classBonus = 0;
		if (dropDownClassActive == Technomancer)
		{
			std::cout << "Technomancer selected..." << std::endl;
			if (toggleTechnomancerActive == FirstSkill)
			{
				std::cout << "Class Hacking bonus selected..." << std::endl;
				classBonus = 1;
			}
		}
		hackingOutput = RollSkill(hackingValue, pushChecked, extraD6Checked, classBonus);
	}

	//healing roll -- auromancers and terramancers can select to receive a bonus
	if (GuiButton(Rectangle{ textX + 180, textY + 250, 60, 20 }, "Roll"))
	{
		std::cout << "Rolling Healing..." << std::endl;
		int classBonus = 0;
		if (dropDownClassActive == Auromancer)
		{
			std::cout << "Auromancer selected..." << std::endl;
			if (toggleAuromancerActive == SecondSkill)
			{
				std::cout << "Class Healing bonus selected..." << std::endl;
				classBonus = 1;
			}
		}
		else if (dropDownClassActive == Terramancer)
		{
			std::cout << "Terramancer selected..." << std::endl;
			if (toggleTerramancerActive == FirstSkill)
			{
				std::cout << "Class Healing bonus selected..." << std::endl;
				classBonus = 1;
			}
		}
		healingOutput = RollSkill(healingValue, pushChecked, extraD6Checked, classBonus);
	}

	//mancy roll -- terramancers can select to receive a bonus
	if (GuiButton(Rectangle{ textX + 180, textY + 275, 60, 20 }, "Roll"))
	{
		std::cout << "Rolling Mancy..." << std::endl;
		int classBonus = 0;
		if (dropDownClassActive == Terramancer)
		{
			std::cout << "Terramancer selected..." << std::endl;
			if (toggleTerramancerActive == SecondSkill)
			{
				std::cout << "Class Mancy bonus selected..." << std::endl;
				classBonus = 1;
			}
		}
		mancyOutput = RollSkill(mancyValue, pushChecked, extraD6Checked, classBonus);
	}

	//negotiation roll -- revolutionaries can select to receive a bonus
	if (GuiButton(Rectangle{ textX + 180, textY + 300, 60, 20 }, "Roll"))
	{
		std::cout << "Rolling Negotiation..." << std::endl;
		int classBonus = 0;
		if (dropDownClassActive == Revolutionary)
		{
			std::cout << "Revolutionary selected..." << std::endl;
			if (toggleRevolutionaryActive == SecondSkill)
			{
				std::cout << "Class Negotiation bonus selected..." << std::endl;
				classBonus = 1;
			}
		}
		negotiationOutput = RollSkill(negotiationValue, pushChecked, extraD6Checked, classBonus);
	}

	//stealth roll - night agents and vanguards can select to receive a bonus
	if (GuiButton(Rectangle{ textX + 180, textY + 325, 60, 20 }, "Roll"))
	{
		std::cout << "Rolling Stealth..." << std::endl;
		int classBonus = 0;
		if (dropDownClassActive == NightAgent)
		{
			std::cout << "NIGHT Agent selected..." << std::endl;
			if (toggleNightAgentActive == FirstSkill)
			{
				std::cout << "Class Stealth bonus selected..." << std::endl;
				classBonus = 1;
			}
		}
		else if (dropDownClassActive == Vanguard)
		{
			std::cout << "Vanguard selected..." << std::endl;
			if (toggleVanguardActive == FirstSkill)
			{
				std::cout << "Class Stealth bonus selected..." << std::endl;
				classBonus = 1;
			}
		}
		stealthOutput = RollSkill(stealthValue, pushChecked, extraD6Checked, classBonus);
	}

	//thievery roll - vanguards can select to receive a bonus
	if (GuiButton(Rectangle{ textX + 180, textY + 350, 60, 20 }, "Roll"))
	{
		std::cout << "Rolling Thievery..." << std::endl;
		int classBonus = 0;
		if (dropDownClassActive == Vanguard)
		{
			std::cout << "Vanguard selected..." << std::endl;
			if (toggleVanguardActive == SecondSkill)
			{
				std::cout << "Class Thievery bonus selected..." << std::endl;
				classBonus = 1;
			}
		}
		thieveryOutput = RollSkill(thieveryValue, pushChecked, extraD6Checked, classBonus);
	}

	//tumbling roll - night agents can select to receive a bonus
	if (GuiButton(Rectangle{ textX + 180, textY + 375, 60, 20 }, "Roll"))
	{
		std::cout << "Rolling Tumbling..." << std::endl;
		int classBonus = 0;
		if (dropDownClassActive == NightAgent)
		{
			std::cout << "NIGHT Agent selected..." << std::endl;
			if (toggleNightAgentActive == SecondSkill)
			{
				std::cout << "Class Tumbling bonus selected..." << std::endl;
				classBonus = 1;
			}
		}
		tumblingOutput = RollSkill(tumblingValue, pushChecked, extraD6Checked, classBonus);
	}

	//vehicles roll - technomancers can select to receive a bonus
	if (GuiButton(Rectangle{ textX + 180, textY + 400, 60, 20 }, "Roll"))
	{
		std::cout << "Rolling Vehicles..." << std::endl;
		int classBonus = 0;
		if (dropDownClassActive == Technomancer)
		{
			std::cout << "Technomancer selected..." << std::endl;
			if (toggleTechnomancerActive == SecondSkill)
			{
				std::cout << "Class Vehicles bonus selected..." << std::endl;
				classBonus = 1;
			}
		}
		vehiclesOutput = RollSkill(vehiclesValue, pushChecked, extraD6Checked, classBonus);
	}

	//roll outputs
	GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
	GuiLabel(Rectangle{ textX + 235, textY + 150, 300, 20 }, "Output");
	GuiLabel(Rectangle{ textX + 240, textY + 175, 300, 20 }, attackOutput.c_str());
	GuiLabel(Rectangle{ textX + 240, textY + 200, 300, 20 }, defenseOutput.c_str());
	GuiLabel(Rectangle{ textX + 240, textY + 225, 300, 20 }, hackingOutput.c_str());
	GuiLabel(Rectangle{ textX + 240, textY + 250, 300, 20 }, healingOutput.c_str());
	GuiLabel(Rectangle{ textX + 240, textY + 275, 300, 20 }, mancyOutput.c_str());
	GuiLabel(Rectangle{ textX + 240, textY + 300, 300, 20 }, negotiationOutput.c_str());
	GuiLabel(Rectangle{ textX + 240, textY + 325, 300, 20 }, stealthOutput.c_str());
	GuiLabel(Rectangle{ textX + 240, textY + 350, 300, 20 }, thieveryOutput.c_str());
	GuiLabel(Rectangle{ textX + 240, textY + 375, 300, 20 }, tumblingOutput.c_str());
	GuiLabel(Rectangle{ textX + 240, textY + 400, 300, 20 }, vehiclesOutput.c_str());
	GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);

	//missions
	GuiLine(Rectangle{ textX, textY + 430, 500, 30 }, "Mission Objective");
	if (GuiButton(Rectangle{ textX, textY + 470, 100, 22 }, "Roll"))
	{
		missionText = missionObjectives[RollText(6)];
	};
	GuiSetStyle(DEFAULT, TEXT_SIZE, 15);
	GuiLabel(Rectangle{ textX + 120, textY + 430, 400, 100 }, missionText.c_str());
	GuiSetStyle(DEFAULT, TEXT_SIZE, 22);
	
	//encounters
	GuiLine(Rectangle{ textX, textY + 570, 500, 30 }, "Encounter");
	if (GuiButton(Rectangle{ textX, textY + 615, 100, 20 }, "Roll"))
	{
		encounterText = encounters[RollText(10)];
	};
	GuiSetStyle(DEFAULT, TEXT_SIZE, 15);
	GuiLabel(Rectangle{ textX + 120, textY + 575, 400, 100 }, encounterText.c_str());
	GuiSetStyle(DEFAULT, TEXT_SIZE, 22);

	//chaos rifts
	GuiLine(Rectangle{ textX, textY + 650, 500, 30 }, "Chaos Rift");
	if (GuiButton(Rectangle{ textX, textY + 750, 100, 20 }, "Roll"))
	{
		chaosRiftText = chaosRifts[RollText(4)];
	};
	GuiSetStyle(DEFAULT, TEXT_SIZE, 15);
	GuiLabel(Rectangle{ textX + 120, textY + 720, 400, 100 }, chaosRiftText.c_str());
	GuiSetStyle(DEFAULT, TEXT_SIZE, 22);

	//chaos meter
	GuiLine(Rectangle{ textX, textY + 865, 500, 30 }, "Chaos Meter");
	GuiCheckBox(Rectangle{ textX + 50, textY + 895, 15, 15 }, "Token 1", &chaosToken1Checked);
	GuiCheckBox(Rectangle{ textX + 200, textY + 895, 15, 15 }, "Token 2", &chaosToken2Checked);
	GuiCheckBox(Rectangle{ textX + 350, textY + 895, 15, 15 }, "Token 3", &chaosToken3Checked);

	//back button
	if (GuiButton({ textX + 400, textY + 960, 100, 24 }, "Back"))
	{
		//back to menu
	};

	//class dropdown
	GuiUnlock();
	GuiSetStyle(DROPDOWNBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
	if (GuiDropdownBox(Rectangle{ textX, textY + 80, 500, 30 },
		" Auromancer; NIGHT Agent; Revolutionary; Technomancer; Terramancer; Vanguard",
		&dropDownClassActive, dropDownClassEdit)) dropDownClassEdit = !dropDownClassEdit;
}