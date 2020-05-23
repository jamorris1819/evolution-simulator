#pragma once
#include "menuwindow.h"
#include "creature.h"
#include "netdata.h"

class CreatureWindow : public MenuWindow {
public:
	Creature* creature;
	NetData* creatureViewNet;
	void initialise() override;
	void renderWindow() override;
private:
	std::vector<std::string> options;
	int selected;
	void renderDetails();
	void renderDescription();

	// Descriptions
	void renderGenomeDescription();
	void renderTraitsDescription();
	void renderBodyDescription();
	void renderLivingEntityDescription();
	void renderNeuralNetworkDescription();

	// Details
	void renderGenomeDetails();
	void renderTraitsDetails();
	void renderBodyDetails();
	void renderLivingEntityDetails();
	void renderNeuralNetworkDetails();

	NetData* initialiseNeuralNetwork();

	ImVec4 lerpColour(ImVec4 col1, ImVec4 col2, float x)
	{
		x = glm::clamp(x, 0.0f, 1.0f);
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
};