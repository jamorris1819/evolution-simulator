#include "worldwindow.h"
#include <string>

void WorldWindow::initialise()
{
	setName("World Window");
	windowVisible = true;
	windowSize = ImVec2(400, 300);
}

void WorldWindow::renderWindow()
{
	if (terrain == nullptr) {
		return;
	}

	bool changeMade = false;

	if (terrain->noiseHeightMapCount() == 0) {
		terrain->createNoiseHeightMap();
		char name[128] = "base layer";
		changeMade = true;
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
			// TODO: remove this logic
			if (ImGui::Button("Make plants")) {
				int tileSize = terrain->getTileSize();
				for (int y = 0; y < terrain->getHeight(); y++) {
					for (int x = 0; x < terrain->getWidth(); x++) {
						if (rand() % 3 != 1) continue;
						float noise = terrain->getHeightNoise(x, y);
						float temp = terrain->getTemperature(x, y);
						if (noise < 0.2f || (temp < 0.3f || temp > 0.7f)) {
							continue;
						}

						glm::vec2 position;
						position.x = tileSize * x * sqrt(3);
						if (y % 2 != 0) position.x += tileSize * sqrt(3) / 2; // Offset if an odd row
						position.y = tileSize * y * 2 * 0.75f;

						float offsetX = ((rand() % 200) - 100) / 100.0f;
						float offsetY = ((rand() % 200) - 100) / 100.0f;

						position += glm::vec2(offsetX * tileSize / 2.0f, offsetY * tileSize / 2.0f);
						entityManager->createPlant(position);
					}
				}
			}

			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
}
