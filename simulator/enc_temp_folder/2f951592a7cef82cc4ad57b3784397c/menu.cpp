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
Body* Menu::selectedBody;
NeuralGenome* Menu::selectedNeuralGenome;
NetData Menu::netData;

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

void Menu::renderBodyDescription()
{
	ImGui::TextWrapped("The variables that affect the body shape & size are determined through the genome. Here you can view the body traits derived from the genome.");
}

void Menu::renderBodyDetails()
{
	ImGui::LabelText("Attribute", "Value");
	ImGui::Separator();

	// SEED
	ImGui::DragInt("Seed", &selectedBody->seed);

	// STEPS
	ImGui::DragInt("Steps", &selectedBody->steps);

	// FREQUENCY
	ImGui::DragFloat("Frequency", &selectedBody->frequency);

	// STRIDE
	ImGui::DragInt("Stride X", &selectedBody->strideX);
	ImGui::DragInt("Stride Y", &selectedBody->strideY);

	// OFFSET
	ImGui::DragFloat("Offset X", &selectedBody->offsetX);
	ImGui::DragFloat("Offset Y", &selectedBody->offsetY);

	// OCTAVES
	ImGui::DragInt("Octaves", &selectedBody->octaves);

	// LENGTH / WIDTH
	ImGui::DragFloat("Length", &selectedBody->length);
	ImGui::DragFloat("Width", &selectedBody->width);
}

void Menu::renderNeuralNetDescription()
{
	ImGui::TextWrapped("some Neural Net description here...");
}

void Menu::renderNeuralNetDetails()
{
	if (selectedNeuralGenome == nullptr)
		return;

	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	static ImVec4 colf = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	const ImU32 col = ImColor(colf);
	const ImVec2 p = ImGui::GetCursorScreenPos();
	float x = p.x + 4.0f, y = p.y + 4.0f;


	static float size = 24.0f;
	float spacing = 10.0f;
	float outputNodeOffset = 200.0f;

	int inputNodeCount = selectedNeuralGenome->inputCount;
	int outputNodeCount = selectedNeuralGenome->outputCount;
	int totalNodeCount = selectedNeuralGenome->getNodeCount() - inputNodeCount - outputNodeCount;
	std::map<int, ConnectionGene> connections = selectedNeuralGenome->getConnections();

	x = p.x + 4.0f, y = p.y + 4.0f;

	// Render the input nodes.
	for (int i = 0; i < inputNodeCount; i++) {
		draw_list->AddCircleFilled(ImVec2(
			x + (size * 0.5f),	// start x
			y + (size * 0.5f)	// start y
			+ (i * (size + spacing))), // y offset
			size * 0.5f, col, 20);
	}

	//float offset = (inputNodeCount * (sz + spacing)) / (outputNodeCount + 1);
	float inputHeight = (inputNodeCount + 1) * (size + spacing);
	float padOffset = (inputHeight) / (outputNodeCount + 1);
	padOffset -= size * 0.5f;
	// Render the output nodes.
	for (int i = 0; i < outputNodeCount; i++) {
		draw_list->AddCircleFilled(ImVec2(
			x + outputNodeOffset + (size * 0.5f), // start x
			y + (size * 0.5f) // start y
			+ (i * (size + spacing)) // y offset
			+ padOffset - (size * 0.5f)),
			size * 0.5f, col, 20);
	}

	x = p.x + 4.0f, y = p.y + 4.0f;

	// Render the connections.
	std::map<int, ConnectionGene>::iterator it;
	for (it = connections.begin(); it != connections.end(); it++) {
		int inputNode = it->second.getInputNode();
		int outputNode = it->second.getOutputNode();

		//x = p.x + 4.0f, y = p.y + 4.0f;

		if (inputNode < inputNodeCount && outputNode < outputNodeCount + inputNodeCount) {
			draw_list->AddLine(ImVec2(x, y), ImVec2(1000, 1000), col, 10.0f);
		}
	}
}

void Menu::triggerBodyRegen()
{
	selectedBody->unload();
	selectedBody->addParameters(
		selectedGenome->getGeneValue<int>(GeneMarker::GM_BODY_STEPS),
		5,
		5,
		selectedGenome->getGeneValue<float>(GeneMarker::GM_BODY_OFFSETX),
		selectedGenome->getGeneValue<float>(GeneMarker::GM_BODY_OFFSETY),
		selectedGenome->getGeneValue<int>(GeneMarker::GM_COLOUR_R),
		selectedGenome->getGeneValue<int>(GeneMarker::GM_COLOUR_G),
		selectedGenome->getGeneValue<int>(GeneMarker::GM_COLOUR_B)
	);
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
		title = "Viewing Genome";
		break;
	case 1:
		title = "Viewing Traits";
		break;
	case 2:
		title = "Viewing Body";
		break;
	case 3:
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
			if (selected == 0 && selectedGenome != nullptr) renderGenomeDescription();
			if (selected == 1 && selectedGenome != nullptr) renderTraitsDescription();
			if (selected == 2 && selectedBody != nullptr) renderBodyDescription();
			if (selected == 3 && selectedBody != nullptr) renderNeuralNetDescription();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Details"))
		{
			if (selected == 0 && selectedGenome != nullptr) renderGenomeDetails();
			if (selected == 1 && selectedGenome != nullptr) renderTraitsDetails();
			if (selected == 2 && selectedBody != nullptr) renderBodyDetails();
			if (selected == 3 && selectedBody != nullptr) renderNeuralNetDetails();

			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
	ImGui::EndChild();
	if (ImGui::Button("Mutate")) { selectedGenome->mutate(); triggerBodyRegen(); }
	ImGui::SameLine();
	if (ImGui::Button("Regen body")) { triggerBodyRegen(); }
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

void Menu::focusBody(Body* body)
{
	selectedBody = body;
}

void Menu::focusNeuralGenome(NeuralGenome* neuralGenome)
{
	selectedNeuralGenome = neuralGenome;
	std::map<int, NodeGene> nodeGenes = neuralGenome->getNodes();
	std::map<int, ConnectionGene> connectionGenes = neuralGenome->getConnections();
	int inputCount = 0;
	int outputCount = 0;
	int hiddenCount = 0;
	int hiddenLayers = 1;

	int inputNodeCount = selectedNeuralGenome->inputCount;
	int outputNodeCount = selectedNeuralGenome->outputCount;
	int totalNodeCount = selectedNeuralGenome->getNodeCount() - inputNodeCount - outputNodeCount;

	// Create the node info.
	std::map<int, NodeGene>::iterator it;
	for (it = nodeGenes.begin(); it != nodeGenes.end(); it++) {
		int order = it->first;
		NodeData nodeData;

		// If this is an input node.
		if (order < inputNodeCount)	{
			nodeData.x = 0;
			nodeData.y = inputCount++;
			nodeData.type = NodeType::INPUT;
		}
		else if(order >= inputNodeCount + outputNodeCount) {
			// This is a hidden node.
			nodeData.x = 1;
			nodeData.y = hiddenCount++;
			nodeData.type = NodeType::HIDDEN;
			continue;
		}
		else {
			// This is an output node.
			nodeData.x = 2;
			nodeData.y = outputCount++;
			nodeData.type = NodeType::OUTPUT;
		}

		netData.addNode(nodeData);
	}

	// Create connection info.
	std::map<int, ConnectionGene>::iterator it2;
	for (it2 = connectionGenes.begin(); it2 != connectionGenes.end(); it2++) {
		ConnectionData connectionData;
		NodeData n1 = netData.getNodes()[it2->second.getInputNode()];
		NodeData n2 = netData.getNodes()[it2->second.getOutputNode()];
		connectionData.fx = n1.x;
		connectionData.fy = n1.y;
		connectionData.tx = n2.x;
		connectionData.ty = n2.y;
	}

	int a = 3;
}