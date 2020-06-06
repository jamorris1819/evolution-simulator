#pragma once
#include "event.h"
#include "loglevel.h"

namespace engine {
	class LogEvent : public Event {
	public:
		LogEvent(const char* m) : message(m), level(LogLevel::DEBUG) {}
		LogEvent(const char* m, LogLevel l) : message(m), level(l) {}
		LogLevel level;
		const char* message;
	};
}