#pragma once
#include "uiwindow.h"
#include "imgui_internal.h"
#include <vector>
#include "eventbus.h"
#include "logevent.h"
#include <iostream>

namespace engine {
	class LoggingWindow : public UIWindow {
	public:
		LoggingWindow(EventBus& e) : UIWindow("Log Window", ImVec2(450, 650)), eventBus(e), lineOffsets({ 0 }) {
			eventBus.subscribe(this, &LoggingWindow::handleLogEvent);
		}
		virtual void initialise() override {}
	protected:
		EventBus& eventBus;
		ImGuiTextBuffer buffer;
		ImGuiTextFilter filter;
		std::vector<int> lineOffsets;
		virtual void renderWindow() override {
			renderTopOptions();
			ImGui::Separator();
			renderLogOutput();
		}

		void renderLogOutput();
		void renderTopOptions();

		void renderSideOptions() {
			ImGui::Text("harro");
		}

		void clear() {
			buffer.clear();
			lineOffsets.clear();
			lineOffsets.push_back(0);
		}
		void handleLogEvent(LogEvent* e) {
			std::string types[4] = {
				"DEBUG",
				"INFO",
				"WARN",
				"ERROR"
			};
			std::string message = "";
			message += "[";
			message += types[(int)e->level];
			message += "] ";
			message += e->message;
			message += "\n";
			addLog(message.c_str());
		}

		void addLog(const char* fmt, ...) IM_FMTARGS(2) {
			int old_size = buffer.size();
			va_list args;
			va_start(args, fmt);
			buffer.appendfv(fmt, args);
			va_end(args);
			for (int new_size = buffer.size(); old_size < new_size; old_size++)
				if (buffer[old_size] == '\n')
					lineOffsets.push_back(old_size + 1);
		}
	};
}