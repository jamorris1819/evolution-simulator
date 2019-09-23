#include "menu.h"
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <vector>
#include "glm\glm.hpp"
#include <string>
#include "../src/neural/nodegene.h"
#include "../../creature/creaturebody.h"
#include "../../util/input.h"
#include "../../terrain/terrainmanager.h"
#include <thread>

bool* Menu::bWindowCreature;
Genome* Menu::selectedGenome;
Body* Menu::selectedBody;
LivingEntity* Menu::selectedLivingEntity;
NeuralGenome* Menu::selectedNeuralGenome;
NeuralGenome* Menu::selectedNeuralGenome1;
NeuralGenome* Menu::selectedNeuralGenome2;
NeuralGenome* Menu::selectedNeuralGenome3;
NetData* Menu::netData;
Camera* Menu::camera;
TerrainManager* Menu::terrain;
EntityManager* Menu::entityManager;

// Helper to display a little (?) mark which shows a tooltip when hovered.
// In your own code you may want to display an actual icon if you are using a merged icon fonts (see misc/fonts/README.txt)
static void HelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

bool* Menu::worldEditorOpen;

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

	worldEditorOpen = new bool;
	*worldEditorOpen = true;

	std::cout << "ImGui has initialised successfully" << std::endl;
}

void Menu::renderGenomeDescription()
{
	ImGui::TextWrapped("The genome is a structure that contains genetic information about the creature. The genome is comprised of 2 strands of DNA which feature a sequence of genes. A gene may be responsible for the creature's speed or colour, for example. View the 'traits' section to see how these genes determine the creature's characteristics.");
	ImGui::Text("The genes represented are:");
	ImGui::Spacing();
	for (int i = 0; i < (int)GeneMarker::GENE_COUNT; i++) {
		ImGui::BulletText(geneMarkerToString((GeneMarker)i));
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
		const char* geneName = geneMarkerToString((GeneMarker)index);
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
		else if (base->typeFloat) {
			ImGui::Text(std::to_string(((Gene<float>*)base)->getValue()).c_str());
		}

		ImGui::NextColumn();
	}
	ImGui::Columns(1);
}

void Menu::renderTraitsDescription()
{
	ImGui::TextWrapped("The traits of a creature are determined from the genome. A creature will have 2 genes relating to size, for example. A weighted average is taken of the 2 values to determine the traits of the creature.");
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

void Menu::renderLivingEntityDetails()
{
	ImGui::Text("Health");
	ImGui::SameLine();
	ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
	ImGui::ProgressBar(selectedLivingEntity->getHealth() / selectedLivingEntity->getMaxHealth(), ImVec2(-1.0f, 0.0f));
	ImGui::PopStyleColor();

	ImGui::Text("Energy");
	ImGui::SameLine();
	ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0.0f, 0.5f, 0.0f, 1.0f));
	ImGui::ProgressBar(selectedLivingEntity->getEnergy() / selectedLivingEntity->getMaxEnergy(), ImVec2(-1.0f, 0.0f));
	ImGui::PopStyleColor();
}

void Menu::renderWorldEditor()
{
	if (terrain == nullptr) return;
	bool changeMade = false;

	if (terrain->noiseHeightMapCount() == 0) {
		terrain->createNoiseHeightMap();
		char name[128] = "base layer";
		changeMade = true;
	}


	ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("World Editor", worldEditorOpen, 0)) {
		ImGui::End();
	}

	if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
	{
		if (ImGui::BeginTabItem("Height map"))
		{
			static int selected = 0; // The selected layer

			// Buttons for managing layers.
			if (ImGui::Button("Create")) {
				selected = terrain->createNoiseHeightMap();
				string name = "new layer ";
				name += std::to_string(terrain->noiseHeightMapCount());

				changeMade = true;
			}
			ImGui::SameLine();
			NoiseLayer& layer = terrain->getNoiseLayer(selected);
			if (ImGui::Button("Delete") && terrain->noiseHeightMapCount() > 1) {
				terrain->deleteNoiseHeightMap(selected);
				if (selected > terrain->noiseHeightMapCount() - 1) selected--;
				changeMade = true;
			}

			// Render panel of layers
			ImGui::BeginChild("left pane", ImVec2(173, 0), true);
			for (int i = 0; i < terrain->noiseHeightMapCount(); i++)
			{
				char label[128];
				sprintf_s(label, terrain->getNoiseLayer(i).name.c_str(), i);
				if (ImGui::Selectable(label, selected == i))
					selected = i;
			}
			ImGui::EndChild();


			ImGui::SameLine();


			// Render information about the selected layer.
			ImGui::BeginGroup();
			ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us

			const char* title;
			title = "Editing height map layers";
			ImGui::Text(title);

			ImGui::Separator();


			ImGui::LabelText("Attribute", "Value");
			ImGui::Separator();

			// Standard noise settings.
			static char layerName[128];
			std::copy(layer.name.begin(), layer.name.end(), layerName);
			layerName[layer.name.size()] = '\0';

			const char* noiseTypes[] = { "Value", "Value Fractal", "Perlin", "Perlin Fractal", "Simplex", "Simplex Fractal", "Cellular", "White Noise", "Cubic", "Cubic Fractal" };


			changeMade |= ImGui::Combo("noise type", &layer.noiseType, noiseTypes, IM_ARRAYSIZE(noiseTypes)); ImGui::SameLine(); HelpMarker("The type of noise determines what patterns will be present in the generated height map.");
			changeMade |= ImGui::InputText("layer name", layerName, IM_ARRAYSIZE(layerName));
			changeMade |= ImGui::DragInt("seed", &layer.seed); ImGui::SameLine(); HelpMarker("A seed used by the generator to create the map.");
			changeMade |= ImGui::DragFloat("scale", &layer.scale);
			changeMade |= ImGui::SliderFloat("frequency", &layer.frequency, 0.0f, 0.5f, "frequency = %.3f"); ImGui::SameLine(); HelpMarker("Frequency is the number of cycles that occur in a wave.");

			ImGui::Separator();

			// Fractal noise settings.
			const char* fractalTypes[] = { "FBM", "Billow", "Rigid Multi" };

			if (std::string(noiseTypes[layer.noiseType]).find("Fractal") != std::string::npos) {
				changeMade |= ImGui::Combo("fractal type", &layer.fractalType, fractalTypes, IM_ARRAYSIZE(fractalTypes)); ImGui::SameLine(); HelpMarker("The fractal types determine which algortithm they are generated with.");
				changeMade |= ImGui::SliderInt("octaves", &layer.octaves, 1, 12); ImGui::SameLine(); HelpMarker("Octaves are used to add extra detail to the map.");
				changeMade |= ImGui::DragFloat("lacunarity", &layer.lacunarity, 0.1f, 0.0f, 2.0f);
				changeMade |= ImGui::DragFloat("gain", &layer.gain, 0.1f, 0.0f, 2.0f);
			}

			changeMade |= ImGui::SliderInt("offset x", &layer.offsetX, -1000, 1000);
			changeMade |= ImGui::SliderInt("offset y", &layer.offsetY, -1000, 1000);

			changeMade |= ImGui::Checkbox("inverse", &layer.inverse);

			if (changeMade) {
				terrain->updateNoiseLayer(selected,
					layerName,
					true,
					layer.inverse,
					layer.seed,
					layer.scale,
					layer.noiseType,
					layer.frequency,
					layer.fractalType,
					layer.octaves,
					layer.lacunarity,
					layer.gain,
					layer.offsetX,
					layer.offsetY);
				terrain->paintTerrain();
			}
			ImGui::EndChild();
			ImGui::EndGroup();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Weather map"))
		{
			if (ImGui::Button("Make plants")) {
				int tileSize = terrain->getTileSize();
				for (int y = 0; y < terrain->getHeight(); y++) {
					for (int x = 0; x < terrain->getWidth(); x++) {
						float noise = terrain->getHeightNoise(y, x);
						float temp = terrain->getTemperature(x, y);
						if (noise < 0.2f || (temp < 0.3f || temp > 0.7f)) {
							continue;
						}

						//float chance = rand() % 2 == 0;

						//if (chance) continue;

						//int times = 1 + rand() % 2;
						glm::vec2 position;
						position.x = tileSize * x * sqrt(3);
						if (y % 2 != 0) position.x += tileSize * sqrt(3) / 2; // Offset if an odd row
						position.y = tileSize * y * 2 * 0.75f;

						//for (int i = 0; i < times; i++) {

						float offsetX = ((rand() % 200) - 100) / 100.0f;
						float offsetY = ((rand() % 200) - 100) / 100.0f;

							

							position += glm::vec2(offsetX * tileSize / 2.0f, offsetY * tileSize / 2.0f);

							entityManager->createPlant(position);
						//}
					}
				}
			}

			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
	ImGui::End();
}

void Menu::renderBodyDescription()
{
	ImGui::TextWrapped("The variables that affect the body shape & size are determined through the genome. Here you can view the body traits derived from the genome.");
}

void Menu::renderBodyDetails()
{
	ImGui::LabelText("Attribute", "Value");
	ImGui::Separator();

	// SEED
	ImGui::DragInt("Seed", &((CreatureBody*)selectedBody)->seed);

	// STEPS
	ImGui::DragInt("Steps", &((CreatureBody*)selectedBody)->steps);

	// FREQUENCY
	ImGui::DragFloat("Frequency", &((CreatureBody*)selectedBody)->frequency);

	// STRIDE
	ImGui::DragInt("Stride X", &((CreatureBody*)selectedBody)->strideX);
	ImGui::DragInt("Stride Y", &((CreatureBody*)selectedBody)->strideY);

	// OFFSET
	ImGui::DragFloat("Offset X", &((CreatureBody*)selectedBody)->offsetX);
	ImGui::DragFloat("Offset Y", &((CreatureBody*)selectedBody)->offsetY);

	// OCTAVES
	ImGui::DragInt("Octaves", &((CreatureBody*)selectedBody)->octaves);

	// LENGTH / WIDTH
	ImGui::DragFloat("Length", &((CreatureBody*)selectedBody)->length);
	ImGui::DragFloat("Width", &((CreatureBody*)selectedBody)->width);
}

void Menu::renderNeuralNetDescription()
{
	ImGui::TextWrapped("The Neural Network is the brain of the creature. The network contains takes in multiple inputs and performs mathematical functions on the data in order to produce an output, which is used to control what the creature does.");
}

ImVec4 lerpColour(ImVec4 col1, ImVec4 col2, float x)
{
	ImVec4 delta = ImVec4(
		(col2.x - col1.x) * x,
		(col2.y - col1.y) * x,
		(col2.z - col1.z) * x,
		(col2.w - col1.w) * x
	);

	return ImVec4(
		col1.x + delta.x,
		col1.y + delta.y,
		col1.z + delta.z,
		col1.w + delta.w
	);
}

// work in progress
void Menu::renderNeuralNetDetails()
{
	if (selectedNeuralGenome == nullptr)
		return;

	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	static ImVec4 colf = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);

	// Define colours.
	static ImVec4 cRed = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	static ImVec4 cGreen = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);

	const ImU32 col = ImColor(colf);
	const ImVec2 p = ImGui::GetCursorScreenPos();
	float x = p.x + 4.0f, y = p.y + 4.0f;

	static float size = 24.0f;
	float spacing = 10.0f;
	float outputNodeOffset = 200.0f;

	int inputNodeCount = selectedNeuralGenome->inputCount;
	int outputNodeCount = selectedNeuralGenome->outputCount;
	int totalNodeCount = selectedNeuralGenome->getNodeCount() - inputNodeCount - outputNodeCount;

	std::vector<NodeData> nodes = netData->getNodes();
	std::vector<ConnectionData> connections = netData->getConnections();
	std::vector<std::pair<int, NodeGene>> n = selectedNeuralGenome->getNodes();

	x = p.x + 16.0f, y = p.y + 128.0f;

	// Render the connections.
	for (int j = 0; j < connections.size(); j++) {
		ConnectionData connection = connections[j];
		if (!connection.enabled) continue;

		// Calculate colour + size.
		float connectionWeight = connections.at(j).weight;
		ImColor connectionColour = connectionWeight > 0 ? cGreen : cRed;
		float connectionStrength = abs(connectionWeight * 5.0f);

		// Render connection.
		draw_list->AddLine(ImVec2( x + nodes[connection.from].x, y + nodes[connection.from].y),
			ImVec2(x + nodes[connection.to].x, y + nodes[connection.to].y),
			connectionColour,
			connectionStrength);
	}

	// Render the input + ouptut nodes.
	for (int i = 0; i < nodes.size(); i++) {
		NodeData node = nodes[i];

		// Calculate colour.
		double val = n[i].second.getValue();

		draw_list->AddCircleFilled(ImVec2(
			x + node.x,	// start x
			y + node.y),	// start y
			size * 0.5f,
			ImColor(lerpColour(cRed, cGreen, val)),
			20);
	}
	
	ImGui::BeginGroup();
	ImGui::BeginChild("item view", ImVec2(0, -400));
	if (ImGui::Button("Add connection")) { selectedNeuralGenome->mutateAddConnection(); focusNeuralGenome(selectedNeuralGenome); }
	ImGui::SameLine();
	if (ImGui::Button("Add node")) { selectedNeuralGenome->mutateAddNode(); focusNeuralGenome(selectedNeuralGenome); }
	ImGui::SameLine();
	if (ImGui::Button("Toggle connection")) { selectedNeuralGenome->mutateToggleConnection(); focusNeuralGenome(selectedNeuralGenome); }

	if (ImGui::Button("Shift connection weight")) { selectedNeuralGenome->mutateShiftWeight(); focusNeuralGenome(selectedNeuralGenome); }
	ImGui::SameLine();
	if (ImGui::Button("Random connection weight")) { selectedNeuralGenome->mutateRandomWeight(); focusNeuralGenome(selectedNeuralGenome); }


	if (ImGui::Button("Create 1")) { selectedNeuralGenome1 = new NeuralGenome(7, 4); }
	ImGui::SameLine();
	if (ImGui::Button("Create 2")) { selectedNeuralGenome2 = new NeuralGenome(7, 4); }
	ImGui::SameLine();
	if (ImGui::Button("Cross 3")) { selectedNeuralGenome3 = NeuralGenome::cross(selectedNeuralGenome1, selectedNeuralGenome2); }

	if (ImGui::Button("View 1")) { focusNeuralGenome(selectedNeuralGenome1); }
	ImGui::SameLine();
	if (ImGui::Button("View 2")) { focusNeuralGenome(selectedNeuralGenome2); }
	ImGui::SameLine();
	if (ImGui::Button("View 3")) { focusNeuralGenome(selectedNeuralGenome3); }

	ImGui::EndChild();
	ImGui::EndGroup();
}

void Menu::triggerBodyRegen()
{
	selectedBody->unload();
	((CreatureBody*)selectedBody)->setRGB(selectedGenome->getGeneValue<int>(GeneMarker::GM_COLOUR_R),
		selectedGenome->getGeneValue<int>(GeneMarker::GM_COLOUR_G),
		selectedGenome->getGeneValue<int>(GeneMarker::GM_COLOUR_B));

	((CreatureBody*)selectedBody)->setNoiseOffset(selectedGenome->getGeneValue<float>(GeneMarker::GM_BODY_OFFSETX),
		selectedGenome->getGeneValue<float>(GeneMarker::GM_BODY_OFFSETY));

	((CreatureBody*)selectedBody)->setNoiseParams(selectedGenome->getGeneValue<int>(GeneMarker::GM_BODY_STEPS), 5, 5);
		
		
	selectedBody->generate();
	selectedBody->load();
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
	options.push_back("Life");
	options.push_back("Genome");
	options.push_back("Traits");
	options.push_back("Body");
	options.push_back("Neural Network");
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
		title = "Viewing Life";
		break;
	case 1:
		title = "Viewing Genome";
		break;
	case 2:
		title = "Viewing Traits";
		break;
	case 3:
		title = "Viewing Body";
		break;
	case 4:
		title = "Viewing Neural Network";
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
			//if (selected == 0 && selectedLivingEntity != nullptr) renderLivingEntityDetails();
			if (selected == 1 && selectedGenome != nullptr) renderGenomeDescription();
			if (selected == 2 && selectedGenome != nullptr) renderTraitsDescription();
			if (selected == 3 && selectedBody != nullptr) renderBodyDescription();
			if (selected == 4 && selectedBody != nullptr) renderNeuralNetDescription();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Details"))
		{
			if (selected == 0 && selectedLivingEntity != nullptr) renderLivingEntityDetails();
			if (selected == 1 && selectedGenome != nullptr) renderGenomeDetails();
			if (selected == 2 && selectedGenome != nullptr) renderTraitsDetails();
			if (selected == 3 && selectedBody != nullptr) renderBodyDetails();
			if (selected == 4 && selectedBody != nullptr) renderNeuralNetDetails();

			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
	ImGui::EndChild();
	if (ImGui::Button("Mutate")) { delete selectedNeuralGenome; focusNeuralGenome(new NeuralGenome(3, 1)); selectedGenome->mutate(); triggerBodyRegen(); }
	ImGui::SameLine();
	if (ImGui::Button("Regen body")) { triggerBodyRegen(); }
	ImGui::SameLine();
	ImGui::SameLine();
	ImGui::EndGroup();

	ImGui::End();
}

void Menu::renderOverlay()
{
	const float DISTANCE = 10.0f;
	static int corner = 2;
	static bool a = true;
	ImGuiIO& io = ImGui::GetIO();
	if (camera == nullptr) return;
	glm::vec3 originalMouse = glm::vec3(io.MousePos.x / 64, -io.MousePos.y / 64, 0) ;
	originalMouse.x /= camera->zoom;
	originalMouse.y /= camera->zoom * (1920 / 1080);
	glm::mat4 te = camera->projection * camera->view;

	glm::mat4 real = glm::translate(glm::mat4(1), originalMouse) * camera->view * camera->projection;

	originalMouse /= camera->zoom;
	glm::mat4 aa = glm::translate(glm::mat4(1), originalMouse);


	

	glm::vec3 mouseinput = glm::vec3(Input::mouseCoordinates, 1.0f);
	mouseinput.x = ((mouseinput.x / 1920) * 2) - 1;
	mouseinput.y = -1 * (((mouseinput.y / 1080) * 2) - 1);

	glm::mat4 pv = camera->projection;
	glm::mat4 ipv = glm::inverse(pv);

	glm::vec3 ppp = (glm::vec4(mouseinput, 1.0f) * ipv);

	/*glm::vec3 t =  glm::unProject(
		mouseinput / camera->zoom,
		camera->view,
		camera->projection,
		camera->viewport
	);*/
	glm::vec3 mousePos = glm::vec4(ppp, 0.0f) - glm::vec4(camera->position.x, camera->position.y, 0.0f, 0.0f);/*
		
		- glm::vec4(camera->viewport.z / 2.0f, camera->viewport.w / 2.0f, 0.0f, 0.0f)
		- glm::vec4(ppp, 0.0f); // glm::vec3(te[3]) + glm::vec3();// glm::vec3(io.MousePos.x, -io.MousePos.y, 0);*/


	if (corner != -1)
	{
		ImVec2 window_pos = ImVec2((corner & 1) ? io.DisplaySize.x - DISTANCE : DISTANCE, (corner & 2) ? io.DisplaySize.y - DISTANCE : DISTANCE);
		ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
		ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
	}
	ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
	if (ImGui::Begin("Example: Simple overlay", &a, (corner != -1 ? ImGuiWindowFlags_NoMove : 0) | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
	{
		ImGui::Text("Description Overlay");
		ImGui::Separator();
		if (ImGui::IsMousePosValid())
			ImGui::Text("Mouse Position: (%.1f,%.1f)", mousePos.x, mousePos.y);
		else
			ImGui::Text("Mouse Position: <invalid>");
		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::MenuItem("Custom", NULL, corner == -1)) corner = -1;
			if (ImGui::MenuItem("Top-left", NULL, corner == 0)) corner = 0;
			if (ImGui::MenuItem("Top-right", NULL, corner == 1)) corner = 1;
			if (ImGui::MenuItem("Bottom-left", NULL, corner == 2)) corner = 2;
			if (ImGui::MenuItem("Bottom-right", NULL, corner == 3)) corner = 3;
			ImGui::EndPopup();
		}
	}
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
	Menu::renderWorldEditor();
	Menu::renderOverlay();

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

void Menu::focusBody(Body* body)
{
	selectedBody = body;
}

// This brings the neural genome into focus and calculates appropriate info in order to render.
void Menu::focusNeuralGenome(NeuralGenome* neuralGenome)
{
	if (netData != nullptr)
		delete netData;

	netData = new NetData();
	selectedNeuralGenome = neuralGenome;
	std::vector<std::pair<int, NodeGene>> nodeGenes = neuralGenome->getNodes();
	std::vector<std::pair<int, ConnectionGene>> connectionGenes = neuralGenome->getConnections();
	int inputCount = 0;
	int outputCount = 0;
	int hiddenCount = 0;
	int hiddenLayers = 1;

	int inputNodeCount = selectedNeuralGenome->inputCount;
	int outputNodeCount = selectedNeuralGenome->outputCount;
	int totalNodeCount = selectedNeuralGenome->getNodeCount() - inputNodeCount - outputNodeCount;
	
	
	// Create connection info.
	for (int i = 0; i < connectionGenes.size(); i++) {
		ConnectionGene connectionGene = connectionGenes[i].second;
		ConnectionData connectionData;
		connectionData.from = connectionGene.getInputNode();
		connectionData.to = connectionGene.getOutputNode();
		connectionData.enabled = connectionGene.getEnabled();
		connectionData.weight = connectionGene.getWeight();

		netData->addConnection(connectionData);
	}

	// Create the node info (position + type).
	
	for (int i = 0; i < nodeGenes.size(); i++) {
		int order = nodeGenes[i].first;
		NodeData nodeData;

		// If this is an input node.
		if (order < inputNodeCount)	{
			nodeData.x = 0;
			nodeData.y = (inputCount++) * 36;
			nodeData.type = NodeType::INPUT;
		}
		else if(order >= inputNodeCount + outputNodeCount) {
			// This is a hidden node.
			nodeData.x = 1;
			nodeData.y = hiddenCount++;
			nodeData.type = NodeType::HIDDEN;

			// As this is a hidden node, we need to calculate where it should be.
			// However we must do it after all nodes have been created.
		}
		else {
			// This is an output node.
			nodeData.x = 400;
			nodeData.y = (outputCount++) * 36;
			nodeData.type = NodeType::OUTPUT;
		}

		netData->addNode(nodeData);
	}

	// Calculate the positions for hidden nodes. 
	for (int i = inputCount + outputCount; i < netData->getNodes().size(); i++) {

		vector<int> hiddenNodeConnections;

		// Iterate through all connections and find which nodes this node connects to.
		for (int j = 0; j < netData->getConnections().size(); j++) {
			ConnectionData connection = netData->getConnections()[j];
			if (connection.to == i) hiddenNodeConnections.push_back(connection.from);
			if (connection.from == i) hiddenNodeConnections.push_back(connection.to);
		}

		// TODO: make this less error prone.
		if (hiddenNodeConnections.size() == 0) continue;

		// Calculate the average position of connected nodes.
		int toDrawX = 0;
		int toDrawY = 0;

		for (int x = 0; x < hiddenNodeConnections.size(); x++) {
			NodeData toNode = netData->getNodes()[hiddenNodeConnections[x]];
			toDrawX += (toNode.x) / hiddenNodeConnections.size();
			toDrawY += (toNode.y) / hiddenNodeConnections.size();
		}

		// This average becomes our hidden node's position.
		netData->getNodes()[i].x = toDrawX;
		netData->getNodes()[i].y = toDrawY;
	}

	int a = 3;
}

// This brings the living entity into focus.
void Menu::focusLivingEntity(LivingEntity* livingEntity)
{
	selectedLivingEntity = livingEntity;
	Creature* creature = (Creature*)livingEntity;
	focusGenome(creature->getGenome());
	focusNeuralGenome(creature->getNeuralGenome());
	focusBody(creature->body);
}

void Menu::focusTerrainManager(TerrainManager* terrainManager)
{
	terrain = terrainManager;
}
