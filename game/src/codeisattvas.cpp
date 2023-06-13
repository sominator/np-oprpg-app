#include "codeisattvas.h"
#include "diceroller.h"
#include <iostream>

namespace Codeisattvas
{
	float panelX = 50.0f;
	float panelY = 60.0f;
	float textX = 60.0f;
	float textY = 100.0f;

	char name[64] = "Name";
	bool nameEdit = false;

	int bpValue = 3;
	bool bpEdit = false;

	int dropDownPersonalityActive = 0;
	bool dropDownPersonalityEdit = false;

	int generosityValue = 1;
	bool generosityEdit = false;
	int virtueValue = 1;
	bool virtueEdit = false;
	int patienceValue = 1;
	bool patienceEdit = false;
	int diligenceValue = 1;
	bool diligenceEdit = false;
	int concentrationValue = 1;
	bool concentrationEdit = false;
	int wisdomValue = 1;
	bool wisdomEdit = false;
	int restoreValue = 1;
	bool restoreEdit = false;

	bool overrideChecked = false;
	bool extraD6Checked = false;

	std::string generosityOutput;
	std::string virtueOutput;
	std::string patienceOutput;
	std::string diligenceOutput;
	std::string concentrationOutput;
	std::string wisdomOutput;
	std::string restoreOutput;

	std::string simulationText;

	std::vector<std::string> simulationObjectives =
	{
		"Infiltrate the mainframe to deactivate\nthe simulation codex",
		"Release the simulation protocols to\nrestore environment controls",
		"Access the simulation server to reveal\nthe database model",
		"Procure the initiation sequence to\nrecover the simulation entry point",
		"Build the application interface to map\nthe simulation's extensions",
		"Redirect the simulation's security\nparameters to redistribute its payloads"
	};

	std::string encounterText;

	std::vector<std::string> encounters =
	{
		"Deploy food sources to terrestrial\necologies (Generosity)",
		"Cleanse pollution from ocean habitats\n(Virtue)",
		"Protect seed germination in new flora\ndomains (Patience)",
		"Release fauna in captivity (Diligence)",
		"Repair technology for climate\nstabilization (Concentration)",
		"Restore equilibrium to imbalanced\necosystems (Wisdom)"
	};

	std::string systemLockdownText;

	std::vector<std::string> systemLockdowns =
	{
		"You're swarmed by the A.N.G.E.R. protocol.\n"
		"Each hacker rolls Patience, Diligence,\n"
		"or Wisdom. Return grants a +1d6 bonus to\n"
		"one of your existing perfections (player's\n"
		"choice); throw incurs a -1d6 penalty to it\n"
		"(GM's choice). Reset the Bit Counter.",
		//line break for readability
		"You stumble into the baited trap of the\n"
		"G.R.E.E.D. protocol. Each hacker rolls\n"
		"Generosity, Virtue, or Diligence. Return\n"
		"grants you an automatic success on an\n"
		"upcoming roll (player's choice); throw\n"
		"incurs an automatic failure on an\n"
		"upcoming roll (GM's choice). Reset the\n"
		"Bit Counter.",
		//line break for readability
		"You become entangled in the web of the\n"
		"I.G.N.O.R.A.N.C.E. protocol. Each player\n"
		"rolls Virtue, Concentration, or Wisdom.\n"
		"Return grants you +1 Bit Points, even\n"
		"above the normal amount of 3; throw\n"
		"removes 1 Bit Point. Reset the Bit\n"
		"Counter."
	};

	bool bitCounterToken1Checked = false;
	bool bitCounterToken2Checked = false;
	bool bitCounterToken3Checked = false;

	void DrawCodeisattvas()
	{
		if (dropDownPersonalityEdit) GuiLock();

		GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
		GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);

		GuiLabel(Rectangle{ 230, 20, 500, 25 }, "{CODE}isattvas");

		//panels
		GuiPanel(Rectangle{ panelX, panelY, 545, 560 }, "Character Info");
		GuiPanel(Rectangle{ panelX, panelY + 575, 545, 400 }, "GM Info");

		//name text box and BP value box
		GuiSetStyle(TEXTBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
		if (GuiTextBox(Rectangle{ textX, textY, 300, 30 }, name, 64, nameEdit)) nameEdit = !nameEdit;
		if (GuiSpinner(Rectangle{ textX + 370, textY, 125, 30 }, "BP ", &bpValue, 0, 10, bpEdit)) bpEdit = !bpEdit;

		//personalities
		GuiLine(Rectangle{ textX, textY + 45, 500, 30 }, "Personality");

		//skills
		GuiLine(Rectangle{ textX, textY + 130, 500, 30 }, "Skills");

		GuiSetStyle(DEFAULT, TEXT_SIZE, 18);
		GuiCheckBox(Rectangle{ textX + 83, textY + 160, 15, 15 }, "Override", &overrideChecked);
		GuiCheckBox(Rectangle{ textX + 193, textY + 160, 15, 15 }, "+1d6", &extraD6Checked);
		if (GuiSpinner(Rectangle{ textX + 83, textY + 180, 90, 22 }, "Generos. ", &generosityValue, 1, 10, generosityEdit)) generosityEdit = !generosityEdit;
		if (GuiSpinner(Rectangle{ textX + 83, textY + 205, 90, 22 }, "Virtue ", &virtueValue, 1, 10, virtueEdit)) virtueEdit = !virtueEdit;
		if (GuiSpinner(Rectangle{ textX + 83, textY + 230, 90, 22 }, "Patience ", &patienceValue, 1, 10, patienceEdit)) patienceEdit = !patienceEdit;
		if (GuiSpinner(Rectangle{ textX + 83, textY + 255, 90, 22 }, "Dilig. ", &diligenceValue, 1, 10, diligenceEdit)) diligenceEdit = !diligenceEdit;
		if (GuiSpinner(Rectangle{ textX + 83, textY + 280, 90, 22 }, "Conc. ", &concentrationValue, 1, 10, concentrationEdit)) concentrationEdit = !concentrationEdit;
		if (GuiSpinner(Rectangle{ textX + 83, textY + 305, 90, 22 }, "Wisdom ", &wisdomValue, 0, 10, wisdomEdit)) wisdomEdit = !wisdomEdit;
		if (GuiSpinner(Rectangle{ textX + 83, textY + 330, 90, 22 }, "Restore ", &restoreValue, 1, 1, restoreEdit)) restoreEdit = !restoreEdit;

		//generosity roll
		if (GuiButton(Rectangle{ textX + 180, textY + 180, 60, 20 }, "Roll"))
		{
			std::cout << "Rolling Generosity..." << std::endl;
			generosityOutput = RollSkill(generosityValue, overrideChecked, extraD6Checked, 0);
		};

		//virtue roll
		if (GuiButton(Rectangle{ textX + 180, textY + 205, 60, 20 }, "Roll"))
		{
			std::cout << "Rolling Virtue..." << std::endl;
			virtueOutput = RollSkill(virtueValue, overrideChecked, extraD6Checked, 0);
		}

		//patience roll
		if (GuiButton(Rectangle{ textX + 180, textY + 230, 60, 20 }, "Roll"))
		{
			std::cout << "Rolling Patience..." << std::endl;
			patienceOutput = RollSkill(patienceValue, overrideChecked, extraD6Checked, 0);
		}

		//diligence roll
		if (GuiButton(Rectangle{ textX + 180, textY + 255, 60, 20 }, "Roll"))
		{
			std::cout << "Rolling Diligence..." << std::endl;
			diligenceOutput = RollSkill(diligenceValue, overrideChecked, extraD6Checked, 0);
		}

		//concentration roll
		if (GuiButton(Rectangle{ textX + 180, textY + 280, 60, 20 }, "Roll"))
		{
			std::cout << "Rolling Concentration..." << std::endl;
			concentrationOutput = RollSkill(concentrationValue, overrideChecked, extraD6Checked, 0);
		}

		//wisdom roll
		if (GuiButton(Rectangle{ textX + 180, textY + 305, 60, 20 }, "Roll"))
		{
			std::cout << "Rolling Wisdom..." << std::endl;
			wisdomOutput = RollSkill(wisdomValue, overrideChecked, extraD6Checked, 0);
		}

		//restore roll
		if (GuiButton(Rectangle{ textX + 180, textY + 330, 60, 20 }, "Roll"))
		{
			std::cout << "Rolling Restore..." << std::endl;
			restoreOutput = RollSkill(restoreValue, overrideChecked, extraD6Checked, 0);
		}

		//roll outputs
		GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
		GuiLabel(Rectangle{ textX + 235, textY + 155, 300, 20 }, "Output");
		GuiLabel(Rectangle{ textX + 240, textY + 180, 300, 20 }, generosityOutput.c_str());
		GuiLabel(Rectangle{ textX + 240, textY + 205, 300, 20 }, virtueOutput.c_str());
		GuiLabel(Rectangle{ textX + 240, textY + 230, 300, 20 }, patienceOutput.c_str());
		GuiLabel(Rectangle{ textX + 240, textY + 255, 300, 20 }, diligenceOutput.c_str());
		GuiLabel(Rectangle{ textX + 240, textY + 280, 300, 20 }, concentrationOutput.c_str());
		GuiLabel(Rectangle{ textX + 240, textY + 305, 300, 20 }, wisdomOutput.c_str());
		GuiLabel(Rectangle{ textX + 240, textY + 330, 300, 20 }, restoreOutput.c_str());
		GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
		GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

		//simulations
		GuiLine(Rectangle{ textX, textY + 380, 500, 30 }, "Simulation Objective");
		if (GuiButton(Rectangle{ textX, textY + 440, 100, 22 }, "Roll"))
		{
			simulationText = simulationObjectives[RollText(6)];
		};
		GuiSetStyle(DEFAULT, TEXT_SIZE, 18);
		GuiLabel(Rectangle{ textX + 120, textY + 400, 400, 100 }, simulationText.c_str());
		GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

		//encounters
		GuiLine(Rectangle{ textX, textY + 570, 500, 30 }, "Encounter");
		if (GuiButton(Rectangle{ textX, textY + 615, 100, 20 }, "Roll"))
		{
			encounterText = encounters[RollText(6)];
		};
		GuiSetStyle(DEFAULT, TEXT_SIZE, 18);
		GuiLabel(Rectangle{ textX + 120, textY + 575, 400, 100 }, encounterText.c_str());
		GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

		//system lockdown
		GuiLine(Rectangle{ textX, textY + 650, 500, 30 }, "System Lockdown");
		if (GuiButton(Rectangle{ textX, textY + 750, 100, 20 }, "Roll"))
		{
			systemLockdownText = systemLockdowns[RollText(3)];
		};
		GuiSetStyle(DEFAULT, TEXT_SIZE, 17);
		GuiLabel(Rectangle{ textX + 120, textY + 720, 400, 100 }, systemLockdownText.c_str());
		GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

		//bit counter
		GuiLine(Rectangle{ textX, textY + 865, 500, 30 }, "Bit Counter");
		GuiCheckBox(Rectangle{ textX + 50, textY + 895, 15, 15 }, "Token 1", &bitCounterToken1Checked);
		GuiCheckBox(Rectangle{ textX + 200, textY + 895, 15, 15 }, "Token 2", &bitCounterToken2Checked);
		GuiCheckBox(Rectangle{ textX + 350, textY + 895, 15, 15 }, "Token 3", &bitCounterToken3Checked);

		//class dropdown
		GuiUnlock();
		GuiSetStyle(DROPDOWNBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
		if (GuiDropdownBox(Rectangle{ textX, textY + 80, 500, 30 },
			" Brave and Bellowing; Cunning and Cantankerous; Fastidious and Fast Talking; Gregarious and Guffawing; Heroic and High Fiving; Seasoned and Sassy",
			&dropDownPersonalityActive, dropDownPersonalityEdit)) dropDownPersonalityEdit = !dropDownPersonalityEdit;
	}
}
