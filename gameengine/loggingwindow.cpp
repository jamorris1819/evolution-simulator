#include "pch.h"
#include "loggingwindow.h"

namespace engine {
	void LoggingWindow::renderLogOutput() {
		ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
		const char* buf = buffer.begin();
		const char* buf_end = buffer.end();
		if (filter.IsActive()) {
			// In this example we don't use the clipper when Filter is enabled.
			// This is because we don't have a random access on the result on our filter.
			// A real application processing logs with ten of thousands of entries may want to store the result of search/filter.
			// especially if the filtering function is not trivial (e.g. reg-exp).
			for (int line_no = 0; line_no < lineOffsets.size(); line_no++) {
				const char* line_start = buf + lineOffsets[line_no];
				const char* line_end = (line_no + 1 < lineOffsets.size()) ? (buf + lineOffsets[line_no + 1] - 1) : buf_end;
				if (filter.PassFilter(line_start, line_end))
					ImGui::TextUnformatted(line_start, line_end);
			}
		}
		else {
			// The simplest and easy way to display the entire buffer:
			//   ImGui::TextUnformatted(buf_begin, buf_end);
			// And it'll just work. TextUnformatted() has specialization for large blob of text and will fast-forward to skip non-visible lines.
			// Here we instead demonstrate using the clipper to only process lines that are within the visible area.
			// If you have tens of thousands of items and their processing cost is non-negligible, coarse clipping them on your side is recommended.
			// Using ImGuiListClipper requires A) random access into your data, and B) items all being the  same height,
			// both of which we can handle since we an array pointing to the beginning of each line of text.
			// When using the filter (in the block of code above) we don't have random access into the data to display anymore, which is why we don't use the clipper.
			// Storing or skimming through the search result would make it possible (and would be recommended if you want to search through tens of thousands of entries)
			ImGuiListClipper clipper;
			clipper.Begin(lineOffsets.size());
			while (clipper.Step()) {
				for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++) {
					const char* line_start = buf + lineOffsets[line_no];
					const char* line_end = (line_no + 1 < lineOffsets.size()) ? (buf + lineOffsets[line_no + 1] - 1) : buf_end;
					ImGui::TextUnformatted(line_start, line_end);
				}
			}
			clipper.End();
		}
		ImGui::PopStyleVar();

		ImGui::EndChild();
	}

	void LoggingWindow::renderTopOptions() {

		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.0f, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.0f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.0f, 0.8f, 0.8f));

		if (ImGui::Button("Clear")) {
			clear();
		}

		ImGui::PopStyleColor(3);

		ImGui::SameLine();

		if (ImGui::Button("Copy")) {
			addLog("hello\n");
		}

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

		ImGui::SameLine();

		filter.Draw("Filter", -65.0f);
		ImGui::SameLine();
		UIWindow::HelpMarker("add some help here");
	}
}