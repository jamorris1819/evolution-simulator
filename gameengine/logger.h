#pragma once
#include "eventbus.h"
#include "loglevel.h"
#include "logevent.h"
#include <string>
#include <sstream>

namespace engine {
	class Logger {
	public:
		static EventBus* eventBus;
		static void log(std::string s) { log(s.c_str()); }
		static void log(const char* data) { debug(data); }
		static void log(std::string s, LogLevel level) { log(s.c_str(), level); }
		static void log(const char* data, LogLevel level) {
			if (eventBus == nullptr) return;
			eventBus->publish(new LogEvent(data, level));
		}
		static void debug(const char* data) { log(data, LogLevel::DEBUG); }
		static void info(const char* data) { log(data, LogLevel::INFO); }
		static void warn(const char* data) { log(data, LogLevel::WARN); }
		static void error(const char* data) { log(data, LogLevel::ERROR); }

		static void debug(std::string s) { debug(s.c_str()); }
		static void info(std::string s) { info(s.c_str()); }
		static void warn(std::string s) { warn(s.c_str()); }
		static void error(std::string s) { error(s.c_str()); }

		static void debug(std::stringstream& s) { debug(s.str()); }
		static void info(std::stringstream& s) { info(s.str()); }
		static void warn(std::stringstream& s) { warn(s.str()); }
		static void error(std::stringstream& s) { error(s.str()); }
	};
}