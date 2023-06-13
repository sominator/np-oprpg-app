#include "gameturkeys.h"
#include "diceroller.h"
#include <iostream>

namespace GameTurkeys 
{
	float panelX = 50.0f;
	float panelY = 60.0f;
	float textX = 60.0f;
	float textY = 100.0f;

	char name[64] = "Name";
	bool nameEdit = false;

	int ipValue = 3;
	bool ipEdit = false;

	enum RoleChoice
	{
		Artist,
		CommunityManager,
		Developer,
		Marketer,
		Producer,
		QATester
	};

	int dropDownRoleActive = Artist;
	bool dropDownRoleEdit = false;

	enum RoleSkill
	{
		FirstSkill,
		SecondSkill
	};

	int toggleArtistActive = FirstSkill;
	int toggleCommunityManagerActive = FirstSkill;
	int toggleDeveloperActive = FirstSkill;
	int toggleMarketerActive = FirstSkill;
	int toggleProducerActive = FirstSkill;
	int toggleQATesterActive = FirstSkill;

	int businessValue = 1;
	bool businessEdit = false;
	int communicationsValue = 1;
	bool communicationsEdit = false;
	int designValue = 1;
	bool designEdit = false;
	int projectManagementValue = 1;
	bool projectManagementEdit = false;
	int publicRelationsValue = 1;
	bool publicRelationsEdit = false;
	int technicalValue = 1;
	bool technicalEdit = false;
	int rallyValue = 1;
	bool rallyEdit = false;
	
	bool stretchChecked = false;
	bool extraD6Checked = false;

	std::string businessOutput;
	std::string communicationsOutput;
	std::string designOutput;
	std::string projectManagementOutput;
	std::string publicRelationsOutput;
	std::string technicalOutput;
	std::string rallyOutput;
	
	std::string milestoneText;

	std::vector<std::string> milestoneObjectives =
	{
		"Deploy an alpha build to the live servers",
		"Gather new player feedback through a beta\nevent",
		"Attract a publisher by promoting a vertical\nslice",
		"Preview a release candidate at an indie game\nexpo",
		"Offer a closed review event for game\njournalists",
		"Deliver new creative assets for a marketing\npush"
	};

	std::string taskText;

	std::vector<std::string> tasks =
	{
		"Rework your monetization strategy based on an\ninvestment portfolio from BizDev (Business)",
		"Hold a cross-functional meeting to discuss an upcoming\nmarketing campaign (Communications)",
		"Implement changes to a new character class based on\ntriaged player feedback (Design)",
		"Revise your Gantt chart to match up with new timelines\n(Project Management)",
		"Pitch articles about the new combat system by sending out\npreview codes (Public Relations)",
		"Refine your DevOps pipeline to streamline deployment of\ngame updates (Technical)"
	};

	std::string teamPanicText;

	std::vector<std::string> teamPanics =
	{
		"You're tasked with strapping together an emergency build\n"
		"for an EXECUTIVE REVIEW. Each game dev rolls Design,\n"
		"Project Management, or Technical. Success grants a +1d6\n"
		"bonus to one of your existing skills (player's choice);\n"
		"failure incurs a -1d6 penalty to it (GM's choice).\n"
		"Reset the Burnout Meter.",
		//line break for readability
		"You stumble into a dreaded REORGANIZATION of your entire\n"
		"team. Each game dev rolls Business, Communications, or\n"
		"Project Management. Success grants you an automatic\n"
		"success on an upcoming roll (player's choice); failure\n"
		"incurs an automatic failure on an upcoming roll (GM's\n"
		"choice). Reset the Burnout Meter.",
		//line break for readability
		"You're thrown into responding to a REVIEW BOMB by\n"
		"players disgruntled by a recent update. Each game dev\n"
		"rolls Communications, Public Relations, or Technical.\n"
		"Success grants you + 1 Inspiration Points, even above\n"
		"the normal amount of 3; failure removes 1 Inspiration\n"
		"Point. Reset the Burnout Meter."
	};

	bool burnoutCounter1Checked = false;
	bool burnoutCounter2Checked = false;
	bool burnoutCounter3Checked = false;

	void DrawGameTurkeys()
	{
		if (dropDownRoleEdit) GuiLock();

		GuiSetStyle(DEFAULT, TEXT_SIZE, 22);
		GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);

		GuiLabel(Rectangle{ 170, 20, 500, 25 }, "GAME TURKEYS");

		//panels
		GuiPanel(Rectangle{ panelX, panelY, 545, 560 }, "Character Info");
		GuiPanel(Rectangle{ panelX, panelY + 575, 545, 400 }, "GM Info");

		//name text box and IP value box
		GuiSetStyle(TEXTBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
		if (GuiTextBox(Rectangle{ textX, textY, 300, 30 }, name, 64, nameEdit)) nameEdit = !nameEdit;
		if (GuiSpinner(Rectangle{ textX + 370, textY, 125, 30 }, "IP ", &ipValue, 0, 10, ipEdit)) ipEdit = !ipEdit;

		//roles
		GuiLine(Rectangle{ textX, textY + 45, 500, 30 }, "Role");

		//conditional rendering of role skills based on dropdown selection
		switch (dropDownRoleActive)
		{
		case (0):
			GuiToggleGroup(Rectangle{ textX + 110, textY + 117, 140, 22 }, "+1d6 Design; +1d6 PM", &toggleArtistActive);
			break;
		case (1):
			GuiToggleGroup(Rectangle{ textX + 110, textY + 117, 140, 22 }, "+1d6 Comms.; +1d6 PR", &toggleCommunityManagerActive);
			break;
		case(2):
			GuiToggleGroup(Rectangle{ textX + 110, textY + 117, 140, 22 }, "+1d6 Design; +1d6 Technical", &toggleDeveloperActive);
			break;
		case(3):
			GuiToggleGroup(Rectangle{ textX + 110, textY + 117, 140, 22 }, "+1d6 Business; +1d6 Comms.", &toggleMarketerActive);
			break;
		case(4):
			GuiToggleGroup(Rectangle{ textX + 110, textY + 117, 140, 22 }, "+1d6 Business; +1d6 PM", &toggleProducerActive);
			break;
		default:
			GuiToggleGroup(Rectangle{ textX + 110, textY + 117, 140, 22 }, "+1d6 PR; +1d6 Technical", &toggleQATesterActive);
		};

		//skills
		GuiLine(Rectangle{ textX, textY + 130, 500, 30 }, "Skills");

		GuiCheckBox(Rectangle{ textX + 90, textY + 155, 15, 15 }, "Push", &stretchChecked);
		GuiCheckBox(Rectangle{ textX + 180, textY + 155, 15, 15 }, "+1d6", &extraD6Checked);
		if (GuiSpinner(Rectangle{ textX + 80, textY + 175, 90, 22 }, "Business ", &businessValue, 1, 10, businessEdit)) businessEdit = !businessEdit;
		if (GuiSpinner(Rectangle{ textX + 80, textY + 200, 90, 22 }, "Comms. ", &communicationsValue, 1, 10, communicationsEdit)) communicationsEdit = !communicationsEdit;
		if (GuiSpinner(Rectangle{ textX + 80, textY + 225, 90, 22 }, "Design ", &designValue, 1, 10, designEdit)) designEdit = !designEdit;
		if (GuiSpinner(Rectangle{ textX + 80, textY + 250, 90, 22 }, "PM ", &projectManagementValue, 1, 10, projectManagementEdit)) projectManagementEdit = !projectManagementEdit;
		if (GuiSpinner(Rectangle{ textX + 80, textY + 275, 90, 22 }, "PR ", &publicRelationsValue, 1, 10, publicRelationsEdit)) publicRelationsEdit = !publicRelationsEdit;
		if (GuiSpinner(Rectangle{ textX + 80, textY + 300, 90, 22 }, "Technical ", &technicalValue, 0, 10, technicalEdit)) technicalEdit = !technicalEdit;
		if (GuiSpinner(Rectangle{ textX + 80, textY + 325, 90, 22 }, "Rally ", &rallyValue, 1, 1, rallyEdit)) rallyEdit = !rallyEdit;

		//business roll -- marketers and producers can select to receive a bonus
		if (GuiButton(Rectangle{ textX + 180, textY + 175, 60, 20 }, "Roll"))
		{
			std::cout << "Rolling Business..." << std::endl;
			int roleBonus = 0;
			if (dropDownRoleActive == Marketer)
			{
				std::cout << "Marketer selected..." << std::endl;
				if (toggleMarketerActive == FirstSkill)
				{
					std::cout << "Role Business bonus selected..." << std::endl;
					roleBonus = 1;
				}
			}
			else if (dropDownRoleActive == Producer)
			{
				std::cout << "Producer selected..." << std::endl;
				if (toggleProducerActive == FirstSkill)
				{
					std::cout << "Role Business bonus selected..." << std::endl;
					roleBonus = 1;
				}
			}
			businessOutput = RollSkill(businessValue, stretchChecked, extraD6Checked, roleBonus);
		};

		//communications roll -- community managers and marketers can select to receive a bonus
		if (GuiButton(Rectangle{ textX + 180, textY + 200, 60, 20 }, "Roll"))
		{
			std::cout << "Rolling Communications..." << std::endl;
			int roleBonus = 0;
			if (dropDownRoleActive == CommunityManager)
			{
				std::cout << "Community Manager selected..." << std::endl;
				if (toggleCommunityManagerActive == FirstSkill)
				{
					std::cout << "Role Communications bonus selected..." << std::endl;
					roleBonus = 1;
				}
			}
			else if (dropDownRoleActive == Marketer)
			{
				std::cout << "Marketer selected..." << std::endl;
				if (toggleMarketerActive == SecondSkill)
				{
					std::cout << "Role Communications bonus selected..." << std::endl;
					roleBonus = 1;
				}
			}
			communicationsOutput = RollSkill(communicationsValue, stretchChecked, extraD6Checked, roleBonus);
		}

		//design roll -- artists and developers can select to receive a bonus
		if (GuiButton(Rectangle{ textX + 180, textY + 225, 60, 20 }, "Roll"))
		{
			std::cout << "Rolling Design..." << std::endl;
			int roleBonus = 0;
			if (dropDownRoleActive == Artist)
			{
				std::cout << "Artist selected..." << std::endl;
				if (toggleArtistActive == FirstSkill)
				{
					std::cout << "Role Design bonus selected..." << std::endl;
					roleBonus = 1;
				}
			}
			else if (dropDownRoleActive == Developer)
			{
				std::cout << "Developer selected..." << std::endl;
				if (toggleMarketerActive == FirstSkill)
				{
					std::cout << "Role Design bonus selected..." << std::endl;
					roleBonus = 1;
				}
			}
			designOutput = RollSkill(designValue, stretchChecked, extraD6Checked, roleBonus);
		}

		//projectManagement roll -- artists and producers can select to receive a bonus
		if (GuiButton(Rectangle{ textX + 180, textY + 250, 60, 20 }, "Roll"))
		{
			std::cout << "Rolling Project Management..." << std::endl;
			int roleBonus = 0;
			if (dropDownRoleActive == Artist)
			{
				std::cout << "Artist selected..." << std::endl;
				if (toggleArtistActive == SecondSkill)
				{
					std::cout << "Role Project Management bonus selected..." << std::endl;
					roleBonus = 1;
				}
			}
			else if (dropDownRoleActive == Producer)
			{
				std::cout << "Producer selected..." << std::endl;
				if (toggleProducerActive == SecondSkill)
				{
					std::cout << "Role Project Management bonus selected..." << std::endl;
					roleBonus = 1;
				}
			}
			projectManagementOutput = RollSkill(projectManagementValue, stretchChecked, extraD6Checked, roleBonus);
		}

		//publicRelations roll -- community managers and QA testers can select to receive a bonus
		if (GuiButton(Rectangle{ textX + 180, textY + 275, 60, 20 }, "Roll"))
		{
			std::cout << "Rolling Public Relations..." << std::endl;
			int roleBonus = 0;
			if (dropDownRoleActive == CommunityManager)
			{
				std::cout << "Community Manager selected..." << std::endl;
				if (toggleCommunityManagerActive == SecondSkill)
				{
					std::cout << "Role Public Relations bonus selected..." << std::endl;
					roleBonus = 1;
				}
			}
			else if (dropDownRoleActive == QATester)
			{
				std::cout << "QA Tester selected..." << std::endl;
				if (toggleQATesterActive == FirstSkill)
				{
					std::cout << "Role Public Relations bonus selected..." << std::endl;
					roleBonus = 1;
				}
			}
			publicRelationsOutput = RollSkill(publicRelationsValue, stretchChecked, extraD6Checked, roleBonus);
		}

		//technical roll -- developers and QA testers can select to receive a bonus
		if (GuiButton(Rectangle{ textX + 180, textY + 300, 60, 20 }, "Roll"))
		{
			std::cout << "Rolling Technical..." << std::endl;
			int roleBonus = 0;
			if (dropDownRoleActive == Developer)
			{
				std::cout << "Developer selected..." << std::endl;
				if (toggleDeveloperActive == SecondSkill)
				{
					std::cout << "Role Technical bonus selected..." << std::endl;
					roleBonus = 1;
				}
			}
			else if (dropDownRoleActive == QATester)
			{
				std::cout << "QA Tester selected..." << std::endl;
				if (toggleQATesterActive == SecondSkill)
				{
					std::cout << "Role Technical bonus selected..." << std::endl;
					roleBonus = 1;
				}
			}
			technicalOutput = RollSkill(technicalValue, stretchChecked, extraD6Checked, roleBonus);
		}
		
		//rally roll
		if (GuiButton(Rectangle{ textX + 180, textY + 325, 60, 20 }, "Roll"))
		{
			int roleBonus = 0;
			std::cout << "Rolling Rally..." << std::endl;
			
			rallyOutput = RollSkill(rallyValue, stretchChecked, extraD6Checked, roleBonus);
		}

		//roll outputs
		GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
		GuiLabel(Rectangle{ textX + 235, textY + 150, 300, 20 }, "Output");
		GuiLabel(Rectangle{ textX + 240, textY + 175, 300, 20 }, businessOutput.c_str());
		GuiLabel(Rectangle{ textX + 240, textY + 200, 300, 20 }, communicationsOutput.c_str());
		GuiLabel(Rectangle{ textX + 240, textY + 225, 300, 20 }, designOutput.c_str());
		GuiLabel(Rectangle{ textX + 240, textY + 250, 300, 20 }, projectManagementOutput.c_str());
		GuiLabel(Rectangle{ textX + 240, textY + 275, 300, 20 }, publicRelationsOutput.c_str());
		GuiLabel(Rectangle{ textX + 240, textY + 300, 300, 20 }, technicalOutput.c_str());
		GuiLabel(Rectangle{ textX + 240, textY + 325, 300, 20 }, rallyOutput.c_str());
		GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);

		//milestones
		GuiLine(Rectangle{ textX, textY + 380, 500, 30 }, "Milestone Objective");
		if (GuiButton(Rectangle{ textX, textY + 440, 100, 22 }, "Roll"))
		{
			milestoneText = milestoneObjectives[RollText(6)];
		};
		GuiLabel(Rectangle{ textX + 120, textY + 400, 400, 100 }, milestoneText.c_str());

		//tasks
		GuiLine(Rectangle{ textX, textY + 570, 500, 30 }, "Task");
		if (GuiButton(Rectangle{ textX, textY + 615, 100, 20 }, "Roll"))
		{
			taskText = tasks[RollText(6)];
		};
		GuiSetStyle(DEFAULT, TEXT_SIZE, 18);
		GuiLabel(Rectangle{ textX + 120, textY + 575, 400, 100 }, taskText.c_str());
		GuiSetStyle(DEFAULT, TEXT_SIZE, 22);

		//team panic
		GuiLine(Rectangle{ textX, textY + 650, 500, 30 }, "Team Panic");
		if (GuiButton(Rectangle{ textX, textY + 750, 100, 20 }, "Roll"))
		{
			teamPanicText = teamPanics[RollText(3)];
		};
		GuiSetStyle(DEFAULT, TEXT_SIZE, 18);
		GuiLabel(Rectangle{ textX + 120, textY + 720, 400, 100 }, teamPanicText.c_str());
		GuiSetStyle(DEFAULT, TEXT_SIZE, 22);

		//chaos meter
		GuiLine(Rectangle{ textX, textY + 865, 500, 30 }, "Burnout Meter");
		GuiCheckBox(Rectangle{ textX + 50, textY + 895, 15, 15 }, "Token 1", &burnoutCounter1Checked);
		GuiCheckBox(Rectangle{ textX + 200, textY + 895, 15, 15 }, "Token 2", &burnoutCounter2Checked);
		GuiCheckBox(Rectangle{ textX + 350, textY + 895, 15, 15 }, "Token 3", &burnoutCounter3Checked);

		//back button
		if (GuiButton({ textX + 400, textY + 960, 100, 24 }, "Back"))
		{
			//back to menu
		};

		//class dropdown
		GuiUnlock();
		GuiSetStyle(DROPDOWNBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
		if (GuiDropdownBox(Rectangle{ textX, textY + 80, 500, 30 },
			" Artist; Community Manager; Developer; Marketer; Producer; QA Tester",
			&dropDownRoleActive, dropDownRoleEdit)) dropDownRoleEdit = !dropDownRoleEdit;
	}
}