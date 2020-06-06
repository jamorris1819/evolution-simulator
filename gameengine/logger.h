#pragma once
#include "eventbus.h"
#include "loglevel.h"
#include "logevent.h"

namespace engine {
	class Logger {
	public:
		static EventBus* eventBus;
		static void log(const char* data) { debug(data); }
		static void log(const char* data, LogLevel level) {
			if (eventBus == nullptr) return;
			eventBus->publish(new LogEvent(data, level));
		}
		static void debug(const char* data) { log(data, LogLevel::DEBUG); }
		static void info(const char* data) { log(data, LogLevel::INFO); }
		static void warn(const char* data) { log(data, LogLevel::WARN); }
		static void error(const char* data) { log(data, LogLevel::ERROR); }
	};
}