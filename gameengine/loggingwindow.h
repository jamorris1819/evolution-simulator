#pragma once
#include "uiwindow.h"
#include "imgui_internal.h"

namespace engine {
	class LoggingWindow : public UIWindow {
	public:
		LoggingWindow() : UIWindow("Log Window", ImVec2(400, 650)) {}
		virtual void initialise() override {}
	protected:
		virtual void renderWindow() override {
			renderTopOptions();
			ImGui::Separator();

			renderLogOutput();
			

		}

		void renderLogOutput() {
			ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

			ImGui::EndChild();
		}

		void renderTopOptions() {

			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.0f, 0.6f, 0.6f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.0f, 0.7f, 0.7f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.0f, 0.8f, 0.8f));
			ImGui::Button("Clear");
			ImGui::PopStyleColor(3);

			ImGui::SameLine();

			ImGui::Button("Copy");

			ImGui::SameLine();

			if (ImGui::BeginPopup("View options")) {
				static bool t = true;
				ImGui::Checkbox("debug", &t);
				ImGui::Checkbox("info", &t);
				ImGui::Checkbox("warning", &t);
				ImGui::Checkbox("error", &t);
				ImGui::EndPopup();
			}

			if (ImGui::Button("View options"))
				ImGui::OpenPopup("View options");
		}

		void renderSideOptions() {
			ImGui::Text("harro");
		}
	};
}