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
			levelTypes[0] = true;
			levelTypes[1] = true;
			levelTypes[2] = true;
			levelTypes[3] = true;
			scrollToBottom = false;
			autoScroll = true;
		}
		virtual void initialise() override {}
	protected:
		EventBus& eventBus;
		ImGuiTextBuffer buffer;
		ImGuiTextFilter filter;
		std::vector<int> lineOffsets;
		bool levelTypes[4];
		bool scrollToBottom;
		bool autoScroll;
		virtual void renderWindow() override {
			renderTopOptions();
			ImGui::Separator();
			renderLogOutput();
			scrollToBottom = false;
		}

		void renderLogOutput();
		void renderTopOptions();

		void clear() {
			buffer.clear();
			lineOffsets.clear();
			lineOffsets.push_back(0);
		}
		void handleLogEvent(LogEvent* e) {
			if (!levelTypes[(int)e->level]) return;

			static std::string types[4] = {
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
			if (autoScroll)
				scrollToBottom = true;
		}
	};
}