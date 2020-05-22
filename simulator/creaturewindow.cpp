#include "creaturewindow.h"
#include <string>
#include "creaturebody.h"

void CreatureWindow::initialise() {
	setName("Creature Window");
	options.push_back("Life");
	options.push_back("Genome");
	options.push_back("Traits");
	options.push_back("Body");
	options.push_back("Neural Network");

	selected = 0;
	windowVisible = true;

	if (creature == nullptr) {
		std::cout << "no creature setup" << std::endl;
		abort();
	}

	creatureViewNet = initialiseNeuralNetwork();
}

void CreatureWindow::renderWindow() {
	// Render the different categories.
	ImGui::BeginChild("Categories", ImVec2(150, 0), true);
	for (int i = 0; i < options.size(); i++) {
		char label[128];
		sprintf_s(label, options[i].c_str(), i);
		if (ImGui::Selectable(label, selected == i))
			selected = i;
	}
	ImGui::EndChild();
	ImGui::SameLine();

	// Right pane.
	ImGui::BeginGroup();
	ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us

	string titleString = "Viewing " + options.at(selected);
	const char* title = titleString.c_str();

	ImGui::Text(title);

	ImGui::Separator();
	if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None)) {
		if (ImGui::BeginTabItem("Description")) {
			if (selected == 0) renderLivingEntityDetails();
			if (selected == 1) renderGenomeDescription();
			if (selected == 2) renderTraitsDescription();
			if (selected == 3) renderBodyDescription();
			if (selected == 4) renderNeuralNetworkDescription();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Details")) {
			if (selected == 0) renderLivingEntityDetails();
			if (selected == 1) renderGenomeDetails();
			if (selected == 2) renderTraitsDetails();
			if (selected == 3) renderBodyDetails();
			if (selected == 4) renderNeuralNetworkDetails();

			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
	ImGui::EndChild();
	//if (ImGui::Button("Mutate")) { delete selectedNeuralGenome; focusNeuralGenome(new NeuralGenome(3, 1)); selectedGenome->mutate(); triggerBodyRegen(); }
	ImGui::SameLine();
	//if (ImGui::Button("Regen body")) { triggerBodyRegen(); }
	ImGui::SameLine();
	ImGui::SameLine();
	ImGui::EndGroup();
}

void CreatureWindow::renderDetails() {
}

void CreatureWindow::renderDescription() {
}

void CreatureWindow::renderGenomeDescription() {
	ImGui::TextWrapped("The genome is a structure that contains genetic information about the creature. The genome is comprised of 2 strands of DNA which feature a sequence of genes. A gene may be responsible for the creature's speed or colour, for example. View the 'traits' section to see how these genes determine the creature's characteristics.");
	ImGui::Text("The genes represented are:");
	ImGui::Spacing();
	for (int i = 0; i < (int)GeneMarker::GENE_COUNT; i++) {
		ImGui::BulletText(geneMarkerToString((GeneMarker)i));
	}
}

void CreatureWindow::renderTraitsDescription() {
	ImGui::TextWrapped("The traits of a creature are determined from the genome. A creature will have 2 genes relating to size, for example. A weighted average is taken of the 2 values to determine the traits of the creature.");
}

void CreatureWindow::renderBodyDescription() {
	ImGui::TextWrapped("The variables that affect the body shape & size are determined through the genome. Here you can view the body traits derived from the genome.");
}

void CreatureWindow::renderLivingEntityDescription() {
}

void CreatureWindow::renderLivingEntityDetails() {
	LivingEntity* selectedLivingEntity = creature;

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

void CreatureWindow::renderNeuralNetworkDetails() {
	NeuralGenome* neuralGenome = creature->getNeuralGenome();
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	static ImVec4 colf = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);

	// Define colours.
	static ImVec4 cRed = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	static ImVec4 cGreen = ImVec4(0.0f, 0.65f, 0.0f, 1.0f);

	const ImU32 col = ImColor(colf);
	const ImVec2 p = ImGui::GetCursorScreenPos();
	float x = p.x + 4.0f, y = p.y + 4.0f;

	static float size = 24.0f;
	float spacing = 10.0f;
	float outputNodeOffset = 200.0f;

	int inputNodeCount = neuralGenome->inputCount;
	int outputNodeCount = neuralGenome->outputCount;
	int totalNodeCount = neuralGenome->getNodeCount() - inputNodeCount - outputNodeCount;

	std::vector<NodeData> nodes = creatureViewNet->getNodes();
	std::vector<ConnectionData> connections = creatureViewNet->getConnections();
	std::vector<std::pair<int, NodeGene>> n = neuralGenome->getNodes();

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
		draw_list->AddLine(ImVec2(x + nodes[connection.from].x, y + nodes[connection.from].y),
			ImVec2(x + nodes[connection.to].x, y + nodes[connection.to].y),
			connectionColour,
			connectionStrength);
	}

	// Render the input + ouptut nodes.
	for (int i = 0; i < nodes.size(); i++) {
		NodeData node = nodes[i];

		// Calculate colour.
		double val = neuralGenome->activateFunction(n[i].first, n[i].second.getValue());
		draw_list->AddCircleFilled(ImVec2(
			x + node.x,	// start x
			y + node.y),	// start y
			size * 0.5f,
			ImColor(lerpColour(cRed, cGreen, val)),
			20);

		draw_list->AddText(ImVec2(
			x + node.x,	// start x
			y + node.y - 8),
			ImColor(255, 255, 255),
			to_string(val).c_str());
	}

	ImGui::BeginGroup();
	ImGui::BeginChild("item view", ImVec2(0, -400));
	if (ImGui::Button("Add connection")) { neuralGenome->mutateAddConnection(); delete creatureViewNet; creatureViewNet = initialiseNeuralNetwork(); }
	ImGui::SameLine();
	if (ImGui::Button("Add node")) { neuralGenome->mutateAddNode(); delete creatureViewNet; creatureViewNet = initialiseNeuralNetwork(); }
	ImGui::SameLine();
	if (ImGui::Button("do it again")) { delete creatureViewNet; creatureViewNet = initialiseNeuralNetwork(); }
	ImGui::SameLine();
	if (ImGui::Button("Toggle connection")) { neuralGenome->mutateToggleConnection(); delete creatureViewNet; creatureViewNet = initialiseNeuralNetwork(); }

	if (ImGui::Button("Shift connection weight")) { neuralGenome->mutateShiftWeight(); delete creatureViewNet; creatureViewNet = initialiseNeuralNetwork(); }
	ImGui::SameLine();
	if (ImGui::Button("Random connection weight")) { neuralGenome->mutateRandomWeight(); delete creatureViewNet; creatureViewNet = initialiseNeuralNetwork(); }

	ImGui::EndChild();
	ImGui::EndGroup();
}

NetData* CreatureWindow::initialiseNeuralNetwork() {
	NeuralGenome* neuralGenome = creature->getNeuralGenome();
	NetData* netData;
	int width = 400;
	int nodeSpacing = 72;
	netData = new NetData();
	std::vector<std::pair<int, NodeGene>> nodeGenes = neuralGenome->getNodes();
	std::vector<std::pair<int, ConnectionGene>> connectionGenes = neuralGenome->getConnections();
	int inputCount = 0;
	int outputCount = 0;
	int hiddenCount = 0;
	int hiddenLayers = 1;

	int inputNodeCount = neuralGenome->inputCount;
	int outputNodeCount = neuralGenome->outputCount;
	int totalNodeCount = neuralGenome->getNodeCount() - inputNodeCount - outputNodeCount;

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

	// We want to put hidden nodes into layers.
	std::vector <std::vector<NodeData*>> nodeDataLists;
	int neuralNetDepth = neuralGenome->nodeMaxDistanceFromInput(inputNodeCount);
	double spacing = (double)width / neuralNetDepth;
	for (int i = 0; i < neuralNetDepth; i++) {
		std::vector<NodeData*> data;
		nodeDataLists.push_back(data);
	}

	// Create the node info (position + type).
	for (int i = 0; i < nodeGenes.size(); i++) {
		int order = nodeGenes[i].first;
		NodeData nodeData;

		// If this is an input node.
		if (order < inputNodeCount) {
			nodeData.x = 0;
			nodeData.y = (inputCount++) * nodeSpacing;
			nodeData.type = NodeType::INPUT;
		}
		else if (order >= inputNodeCount + outputNodeCount) {
			// This is a hidden node.
			double indist = neuralGenome->nodeDistanceFromInput(order);
			nodeData.x = indist * spacing;
			nodeData.y = nodeDataLists[indist].size() * nodeSpacing;
			nodeData.type = NodeType::HIDDEN;

			nodeDataLists[indist].push_back(&nodeData);
		}
		else {
			// This is an output node.
			nodeData.x = width;
			nodeData.y = (outputCount++) * nodeSpacing;
			nodeData.type = NodeType::OUTPUT;
		}

		netData->addNode(nodeData);
	}

	// Calculate the positions for hidden nodes.
	for (int i = 0; i < nodeDataLists.size(); i++) {
		for (int j = 0; j < nodeDataLists[i].size(); j++) {
			NodeData* nodeData = nodeDataLists[i][j];
		}
	}

	return netData;
}

void CreatureWindow::renderNeuralNetworkDescription() {
	ImGui::TextWrapped("The Neural Network is the brain of the creature. The network contains takes in multiple inputs and performs mathematical functions on the data in order to produce an output, which is used to control what the creature does.");
}

void CreatureWindow::renderGenomeDetails() {
	Genome* selectedGenome = creature->getGenome();
	ImGui::LabelText("Strand B", "Strand A");
	int strandLength = selectedGenome->strandLength;

	// Render columns representing genome.
	ImGui::Columns(2);
	for (int i = 0; i < 2 * strandLength; i++) {
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

void CreatureWindow::renderTraitsDetails() {
	Genome* selectedGenome = creature->getGenome();
	ImGui::LabelText("Trait", "Value");
	ImGui::Separator();

	// SIZE
	int size = selectedGenome->getGeneValue<int>(GeneMarker::GM_SIZE);
	ImGui::DragInt("Size", &size);

	// COLOUR
	float colour[3] = {
		selectedGenome->getGeneValue<int>(GeneMarker::GM_COLOUR_R) / 255.0f,
		selectedGenome->getGeneValue<int>(GeneMarker::GM_COLOUR_G) / 255.0f,
		selectedGenome->getGeneValue<int>(GeneMarker::GM_COLOUR_B) / 255.0f
	};
	ImGui::ColorEdit3("Colour", colour);

	// MOVEMENT SPEED
	int movementSpeed = selectedGenome->getGeneValue<int>(GeneMarker::GM_SPEED_MOVEMENT);
	ImGui::DragInt("Movement Speed", &movementSpeed);

	// ROTATION SPEED
	int rotationSpeed = selectedGenome->getGeneValue<int>(GeneMarker::GM_SPEED_ROTATION);
	ImGui::DragInt("Rotation Speed", &rotationSpeed);
}

void CreatureWindow::renderBodyDetails() {
	/*CreatureBody* selectedBody = (CreatureBody*)creature->body;
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
	ImGui::DragFloat("Width", &selectedBody->width);*/
}