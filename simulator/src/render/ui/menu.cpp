#include "menu.h"
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <vector>
#include "glm\glm.hpp"
#include <string>

bool* Menu::bWindowCreature;
Genome* Menu::selectedGenome;

void Menu::initialise(GLFWwindow* window)
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
	bWindowCreature = new bool;
	*bWindowCreature = true;

	selectedGenome = nullptr;

	std::cout << "ImGui has initialised successfully" << std::endl;
}

void Menu::renderGenomeDescription()
{
	ImGui::TextWrapped("The genome is a structure that contains genetic information about the creature. The genome is comprised of 2 strands of DNA which feature a sequence of genes. A gene may be responsible for the creature's speed or colour, for example. View the 'traits' section to see how these genes determine the creature's characteristics.");
	ImGui::Text("The genes represented are:");
	ImGui::Spacing();
	for (int i = 0; i < (int)GeneMarker::GENE_COUNT; i++) {
		ImGui::BulletText(ToString((GeneMarker)i));
	}
}

void Menu::renderGenomeDetails()
{
	ImGui::LabelText("Strand B", "Strand A");
	int strandLength = selectedGenome->strandLength;

	// Render columns representing genome.
	ImGui::Columns(2);
	for (int i = 0; i < 2 * strandLength; i++)
	{
		int index = (int)(glm::floor(i / 2));
		const char* geneName = ToString((GeneMarker)index);
		std::vector<Base*> strand = i % 2 == 0 ? selectedGenome->strandA : selectedGenome->strandB;
		Base* base = strand[index];
		bool enabled = strand[index]->enabled;
		bool dominant = strand[index]->dominant;

		if (ImGui::GetColumnIndex() == 0)
			ImGui::Separator();


		// Title
		ImGui::Text(geneName);

		if (dominant) ImGui::TextColored(ImVec4(0.000f, 0.520f, 0.031f, 1.000f), "DOMINANT");
		else ImGui::TextColored(ImVec4(0.819f, 0.000f, 0.000f, 1.000f), "RECESSIVE");

		ImGui::Text("Value: ");
		ImGui::SameLine();

		// Figure out how to display value.
		if (base->typeInt) {
			ImGui::Text(std::to_string(((Gene<int>*)base)->getValue()).c_str());
		}
		else if (base->typeBool) {
			ImGui::Text(((Gene<bool>*)base)->getValue() ? "TRUE" : "FALSE");
		}

		ImGui::NextColumn();
	}
	ImGui::Columns(1);
}

void Menu::renderTraitsDetails()
{
	ImGui::LabelText("Trait", "Value");
	ImGui::Separator();

	// SIZE
	int size = selectedGenome->getGeneValue<int>((int)GeneMarker::GM_SIZE);
	ImGui::DragInt("Size", &size); 

	// COLOUR
	float colour[3] = {
		selectedGenome->getGeneValue<int>((int)GeneMarker::GM_COLOUR_R) / 255.0f,
		selectedGenome->getGeneValue<int>((int)GeneMarker::GM_COLOUR_G) / 255.0f,
		selectedGenome->getGeneValue<int>((int)GeneMarker::GM_COLOUR_B) / 255.0f
	};
	ImGui::ColorEdit3("Colour", colour);

	// MOVEMENT SPEED
	int movementSpeed = selectedGenome->getGeneValue<int>((int)GeneMarker::GM_SPEED_MOVEMENT);
	ImGui::DragInt("Movement Speed", &movementSpeed);

	// ROTATION SPEED
	int rotationSpeed = selectedGenome->getGeneValue<int>((int)GeneMarker::GM_SPEED_ROTATION);
	ImGui::DragInt("Rotation Speed", &rotationSpeed);
}

void Menu::renderCreatureWindow()
{
	ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("Creature Window", bWindowCreature, 0)) {
		ImGui::End();
	}

	// Left pane.
	static int selected = 0;
	ImGui::BeginChild("left pane", ImVec2(150, 0), true);
	std::vector<const char*> options;
	options.push_back("Genome");
	options.push_back("Traits");
	options.push_back("Test");
	for (int i = 0; i < options.size(); i++)
	{
		char label[128];
		sprintf_s(label, (const char*)options[i], i);
		if (ImGui::Selectable(label, selected == i))
			selected = i;
	}
	ImGui::EndChild();
	ImGui::SameLine();

	// Right pane.
	ImGui::BeginGroup();
	ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
	
	const char* title;
	switch (selected) {
	case 0:
		title = "Viewing Genome";
		break;
	case 1:
		title = "Viewing Traits";
		break;
	default:
		title = "DEFAULT";
			break;
	}
	ImGui::Text(title);

	ImGui::Separator();
	if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
	{
		if (ImGui::BeginTabItem("Description"))
		{
			if (selected == 0 && selectedGenome != nullptr) renderGenomeDescription();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Details"))
		{
			if (selected == 0 && selectedGenome != nullptr) renderGenomeDetails();
			if (selected == 1 && selectedGenome != nullptr) renderTraitsDetails();

			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
	ImGui::EndChild();
	if (ImGui::Button("Close")) { selectedGenome->mutate(); }
	ImGui::EndGroup();

	ImGui::End();
}

void Menu::renderMenuBar()
{
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			ImGui::MenuItem("New");
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Windows")) {
			ImGui::MenuItem("Main window");
			ImGui::MenuItem("Debug window");
			ImGui::MenuItem("Creature window");
			ImGui::MenuItem("Environment window");
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

void Menu::renderUI()
{
	// Create new frames.
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::ShowDemoWindow();
	Menu::renderMenuBar();
	Menu::renderCreatureWindow();

	// Render frame.
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Menu::destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Menu::focusGenome(Genome* genome)
{
	selectedGenome = genome;
}