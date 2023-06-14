#include "nssv.h"
#include "diceroller.h"
#include <iostream>

namespace NSSV
{
	//initialize variables
	float panelX = 50.0f;
	float panelY = 60.0f;
	float textX = 60.0f;
	float textY = 100.0f;

	char name[64] = "Name";
	bool nameEdit = false;

	int healthValue = 3;
	bool healthEdit = false;

	int dropDownPersonalityActive = 0;
	bool dropDownPersonalityEdit = false;

	int attackValue = 1;
	bool attackEdit = false;
	int communicationsValue = 1;
	bool communicationsEdit = false;
	int defenseValue = 1;
	bool defenseEdit = false;
	int healingValue = 1;
	bool healingEdit = false;
	int mightValue = 1;
	bool mightEdit = false;
	int mindValue = 1;
	bool mindEdit = false;
	int negotiationValue = 1;
	bool negotiationEdit = false;
	int speedValue = 1;
	bool speedEdit = false;
	int stealthValue = 1;
	bool stealthEdit = false;
	int traversalValue = 1;
	bool traversalEdit = false;

	bool pushChecked = false;
	bool extraD6Checked = false;

	std::string attackOutput;
	std::string communicationsOutput;
	std::string defenseOutput;
	std::string healingOutput;
	std::string mightOutput;
	std::string mindOutput;
	std::string negotiationOutput;
	std::string speedOutput;
	std::string stealthOutput;
	std::string traversalOutput;

	std::string objectiveText;

	std::vector<std::string> objectives =
	{
		"Break into the mint to print money with your\nface on it",
		"Expose the secret identity of your nemesis",
		"Release a mind control gas to control the\ncity",
		"Steal a giant laser to blow up the moon"
	};

	std::string encounterText;

	std::vector<std::string> encounters =
	{
		"Defeat the guards to enter the protected facility\n(Attack)",
		"Broadcast your plans across the city's supervillain\nnetwork (Communication)",
		"Protect yourself from an attack by the city's\nanti-super villain defenses (Defense)",
		"Mend a supervillain sidekick to make them indebted\nto you (Healing)",
		"Lift the rubble caused by a superhero battle (Might)",
		"Succeed in a battle of wills against your nemesis\n(Mind)",
		"Fast talk your way through perimeter security\n(Negotiation)",
		"Make it to the facility before security closes the\ngates (Speed)",
		"Sneak by an armed patrol (Stealth)",
		"Climb to the penthouse of the city's tallest building\n(Traversal)"
	};

	std::string superheroBattleText;

	std::vector<std::string> superheroBattles =
	{
		"You engage in battle with the Impossible Protectors.\n"
		"Each player rolls Attack, Defense, or Speed. Success\n"
		"grants a +1d6 bonus to one of your existing\n"
		"mutations (player's choice); failure incurs a -1d6\n"
		"penalty to it (GM's choice). Reset the Fail Meter.",
		//line break for readability
		"You become entangled in the web of Superhero Politics.\n"
		"Each player rolls Communication, Mind, or Negotiation.\n"
		"Success grants you an automatic success on an\n"
		"upcoming roll (player's choice); failure incurs an\n"
		"automatic failure on an upcoming roll (GM's\n"
		"choice). Reset the Fail Meter.",
		//line break for readability
		"You stumble into a protected district of the Energy\n"
		"Commandos. Each player rolls Might, Stealth, or\n"
		"Traversal. Success grants you +1 Health, even above\n"
		"the normal amount of 3; failure removes 1 Health.\n"
		"Reset the Fail Meter.",
		//line break for readability
		"If you haven’t already entered a Superhero Battle,\n"
		"roll 1d4 again to enter a different one. Otherwise,"
		"you’ve attracted the ire of the Cosmic Squad.\n"
		"Each player rolls a skill of their choice. A success\n"
		"by all players automatically completes one of your\n"
		"Encounters (GM's choice) and resets the Fail Meter;\n"
		"a failure by all players ends the game. A	combination\n"
		"resets the Fail Meter, with no benefit or penalty."
	};

	bool failMeterCounter1Checked = false;
	bool failMeterCounter2Checked = false;
	bool failMeterCounter3Checked = false;

	void DrawNSSV()
	{
		if (dropDownPersonalityEdit) GuiLock();

		GuiSetStyle(DEFAULT, TEXT_SIZE, 24);
		GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);

		GuiLabel(Rectangle{ 230, 20, 500, 25 }, "Not-So-Super Villains");

		//panels
		GuiPanel(Rectangle{ panelX, panelY, 545, 560 }, "Character Info");
		GuiPanel(Rectangle{ panelX, panelY + 575, 545, 400 }, "GM Info");

		//name text box and health value box
		GuiSetStyle(TEXTBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
		if (GuiTextBox(Rectangle{ textX, textY, 300, 30 }, name, 64, nameEdit)) nameEdit = !nameEdit;
		if (GuiSpinner(Rectangle{ textX + 370, textY, 125, 30 }, "Health ", &healthValue, 0, 10, healthEdit)) healthEdit = !healthEdit;

		//personalities
		GuiLine(Rectangle{ textX, textY + 45, 500, 30 }, "Personality");

		//skills
		GuiLine(Rectangle{ textX, textY + 130, 500, 30 }, "Skills");

		GuiCheckBox(Rectangle{ textX + 90, textY + 160, 15, 15 }, "Push", &pushChecked);
		GuiCheckBox(Rectangle{ textX + 180, textY + 160, 15, 15 }, "+1d6", &extraD6Checked);
		if (GuiSpinner(Rectangle{ textX + 83, textY + 180, 90, 22 }, "Attack ", &attackValue, 1, 10, attackEdit)) attackEdit = !attackEdit;
		if (GuiSpinner(Rectangle{ textX + 83, textY + 205, 90, 22 }, "Comms. ", &communicationsValue, 1, 10, communicationsEdit)) communicationsEdit = !communicationsEdit;
		if (GuiSpinner(Rectangle{ textX + 83, textY + 230, 90, 22 }, "Defense ", &defenseValue, 1, 10, defenseEdit)) defenseEdit = !defenseEdit;
		if (GuiSpinner(Rectangle{ textX + 83, textY + 255, 90, 22 }, "Healing ", &healingValue, 1, 10, healingEdit)) healingEdit = !healingEdit;
		if (GuiSpinner(Rectangle{ textX + 83, textY + 280, 90, 22 }, "Might ", &mightValue, 1, 10, mightEdit)) mightEdit = !mightEdit;
		if (GuiSpinner(Rectangle{ textX + 83, textY + 305, 90, 22 }, "Mind ", &mindValue, 1, 10, mindEdit)) mindEdit = !mindEdit;
		if (GuiSpinner(Rectangle{ textX + 83, textY + 330, 90, 22 }, "Negot. ", &negotiationValue, 1, 10, negotiationEdit)) negotiationEdit = !negotiationEdit;
		if (GuiSpinner(Rectangle{ textX + 83, textY + 355, 90, 22 }, "Speed ", &speedValue, 1, 10, speedEdit)) speedEdit = !speedEdit;
		if (GuiSpinner(Rectangle{ textX + 83, textY + 380, 90, 22 }, "Stealth ", &stealthValue, 1, 10, stealthEdit)) stealthEdit = !stealthEdit;
		if (GuiSpinner(Rectangle{ textX + 83, textY + 405, 90, 22 }, "Travers. ", &traversalValue, 1, 10, traversalEdit)) traversalEdit = !traversalEdit;

		//attack roll
		if (GuiButton(Rectangle{ textX + 180, textY + 180, 60, 20 }, "Roll"))
		{
			std::cout << "Rolling Attack..." << std::endl;
			attackOutput = RollSkill(attackValue, pushChecked, extraD6Checked, 0);
		};

		//communications roll
		if (GuiButton(Rectangle{ textX + 180, textY + 205, 60, 20 }, "Roll"))
		{
			std::cout << "Rolling Communications..." << std::endl;
			communicationsOutput = RollSkill(communicationsValue, pushChecked, extraD6Checked, 0);
		}

		//defense roll
		if (GuiButton(Rectangle{ textX + 180, textY + 230, 60, 20 }, "Roll"))
		{
			std::cout << "Rolling Defense..." << std::endl;
			defenseOutput = RollSkill(defenseValue, pushChecked, extraD6Checked, 0);
		}

		//healing roll
		if (GuiButton(Rectangle{ textX + 180, textY + 255, 60, 20 }, "Roll"))
		{
			std::cout << "Rolling Healing..." << std::endl;
			healingOutput = RollSkill(healingValue, pushChecked, extraD6Checked, 0);
		}

		//might roll
		if (GuiButton(Rectangle{ textX + 180, textY + 280, 60, 20 }, "Roll"))
		{
			std::cout << "Rolling Might..." << std::endl;
			mightOutput = RollSkill(mightValue, pushChecked, extraD6Checked, 0);
		}

		//mind roll
		if (GuiButton(Rectangle{ textX + 180, textY + 305, 60, 20 }, "Roll"))
		{
			std::cout << "Rolling Mind..." << std::endl;
			mindOutput = RollSkill(mindValue, pushChecked, extraD6Checked, 0);
		}

		//negotiation roll
		if (GuiButton(Rectangle{ textX + 180, textY + 330, 60, 20 }, "Roll"))
		{
			std::cout << "Rolling Negotiation..." << std::endl;
			negotiationOutput = RollSkill(negotiationValue, pushChecked, extraD6Checked, 0);
		}

		//speed roll
		if (GuiButton(Rectangle{ textX + 180, textY + 355, 60, 20 }, "Roll"))
		{
			std::cout << "Rolling Speed..." << std::endl;
			speedOutput = RollSkill(speedValue, pushChecked, extraD6Checked, 0);
		}

		//stealth roll
		if (GuiButton(Rectangle{ textX + 180, textY + 380, 60, 20 }, "Roll"))
		{
			std::cout << "Rolling Stealth..." << std::endl;
			stealthOutput = RollSkill(stealthValue, pushChecked, extraD6Checked, 0);
		}

		//traversal roll
		if (GuiButton(Rectangle{ textX + 180, textY + 405, 60, 20 }, "Roll"))
		{
			std::cout << "Rolling Traversal..." << std::endl;
			traversalOutput = RollSkill(traversalValue, pushChecked, extraD6Checked, 0);
		}

		//roll outputs
		GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
		GuiLabel(Rectangle{ textX + 235, textY + 155, 300, 20 }, "Output");
		GuiLabel(Rectangle{ textX + 240, textY + 180, 300, 20 }, attackOutput.c_str());
		GuiLabel(Rectangle{ textX + 240, textY + 205, 300, 20 }, communicationsOutput.c_str());
		GuiLabel(Rectangle{ textX + 240, textY + 230, 300, 20 }, defenseOutput.c_str());
		GuiLabel(Rectangle{ textX + 240, textY + 255, 300, 20 }, healingOutput.c_str());
		GuiLabel(Rectangle{ textX + 240, textY + 280, 300, 20 }, mightOutput.c_str());
		GuiLabel(Rectangle{ textX + 240, textY + 305, 300, 20 }, mindOutput.c_str());
		GuiLabel(Rectangle{ textX + 240, textY + 330, 300, 20 }, negotiationOutput.c_str());
		GuiLabel(Rectangle{ textX + 240, textY + 355, 300, 20 }, speedOutput.c_str());
		GuiLabel(Rectangle{ textX + 240, textY + 380, 300, 20 }, stealthOutput.c_str());
		GuiLabel(Rectangle{ textX + 240, textY + 405, 300, 20 }, traversalOutput.c_str());
		GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);

		//objectives
		GuiLine(Rectangle{ textX, textY + 430, 500, 30 }, "Objective");
		if (GuiButton(Rectangle{ textX, textY + 470, 100, 22 }, "Roll"))
		{
			objectiveText = objectives[RollText(4)];
		};
		GuiLabel(Rectangle{ textX + 120, textY + 430, 400, 100 }, objectiveText.c_str());

		//encounters
		GuiLine(Rectangle{ textX, textY + 570, 500, 30 }, "Encounter");
		if (GuiButton(Rectangle{ textX, textY + 615, 100, 20 }, "Roll"))
		{
			encounterText = encounters[RollText(10)];
		};
		GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
		GuiLabel(Rectangle{ textX + 120, textY + 575, 400, 100 }, encounterText.c_str());
		GuiSetStyle(DEFAULT, TEXT_SIZE, 22);

		//system lockdown
		GuiLine(Rectangle{ textX, textY + 650, 500, 30 }, "Superhero Battle");
		if (GuiButton(Rectangle{ textX, textY + 750, 100, 20 }, "Roll"))
		{
			superheroBattleText = superheroBattles[RollText(4)];
		};
		GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
		GuiLabel(Rectangle{ textX + 120, textY + 720, 400, 100 }, superheroBattleText.c_str());
		GuiSetStyle(DEFAULT, TEXT_SIZE, 22);

		//bit counter
		GuiLine(Rectangle{ textX, textY + 865, 500, 30 }, "Fail Meter");
		GuiCheckBox(Rectangle{ textX + 50, textY + 895, 15, 15 }, "Counter 1", &failMeterCounter1Checked);
		GuiCheckBox(Rectangle{ textX + 200, textY + 895, 15, 15 }, "Counter 2", &failMeterCounter2Checked);
		GuiCheckBox(Rectangle{ textX + 350, textY + 895, 15, 15 }, "Counter 3", &failMeterCounter3Checked);

		//class dropdown
		GuiUnlock();
		GuiSetStyle(DROPDOWNBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
		if (GuiDropdownBox(Rectangle{ textX, textY + 80, 500, 30 },
			" Brazen, Brash, and Brutal; Cunning, Conniving, and Concise; Fresh, Fabulous, and Fast Talking; Heroic, Herculean, and High Strung; Loud, Laughing, and a Little Unhinged; Smart, Savvy, and Slow Moving",
			&dropDownPersonalityActive, dropDownPersonalityEdit)) dropDownPersonalityEdit = !dropDownPersonalityEdit;
	}
}
