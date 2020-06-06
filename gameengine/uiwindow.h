#pragma once
#include <string>
#include "imgui.h"

namespace engine {
	class UIWindow {
	public:
		UIWindow(std::string t, ImVec2 s) : title(t), size(s), visible(true) {}
		virtual void initialise() = 0;
		void render() {
			ImGui::SetNextWindowSize(size, ImGuiCond_FirstUseEver);

			if (!ImGui::Begin(title.c_str(), &visible, ImGuiWindowFlags_NoResize)) {
				ImGui::End();
				return;
			}

			renderWindow();

			ImGui::End();
		}
		void setTitle(std::string& t) { title = t; }
		const std::string& getTitle() const { return title; }
		void setVisible(bool v) { visible = v; }
		bool isVisible() const { return visible; }
	protected:
		virtual void renderWindow() = 0;
		void HelpMarker(std::string& desc) { HelpMarker(desc.c_str()); }
		void HelpMarker(const char* desc) {
			ImGui::TextDisabled("(?)");
			if (ImGui::IsItemHovered()) {
				ImGui::BeginTooltip();
				ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
				ImGui::TextUnformatted(desc);
				ImGui::PopTextWrapPos();
				ImGui::EndTooltip();
			}
		}
	private:
		std::string title;
		ImVec2 size;
		bool visible;
	};
}