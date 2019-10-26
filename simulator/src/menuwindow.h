#pragma once
#include "imgui.h"

class MenuWindow {
public:
	void setName(const char* windowName) {
		this->windowName = windowName;
	};
	virtual void initialise() = 0;
	void render() {
		if (windowName == nullptr) return;

		ImGui::SetNextWindowSize(windowSize, ImGuiCond_FirstUseEver);

		if (!ImGui::Begin(windowName, &windowVisible, 0)) {
			ImGui::End();
			return;
		}

		renderWindow();

		ImGui::End();
	};
	bool isVisible() { return windowVisible; }
	void setVisible(bool visible) { windowVisible = visible; }
	const char* windowName;
protected:
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
	virtual void renderWindow() = 0;
	bool windowVisible;
	ImVec2 windowSize;
};