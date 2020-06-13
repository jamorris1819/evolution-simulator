#pragma once
#include "event.h"
#include "loglevel.h"

namespace engine {
	class LogEvent : public Event {
	public:
		/// <summary>
		/// Creates a debug log event
		/// </summary>
		/// <param name="m">The message to be logged</param>
		LogEvent(const char* m) : message(m), level(LogLevel::DEBUG) {}

		/// <summary>
		/// Creates a log event
		/// </summary>
		/// <param name="m">The message to be logged</param>
		/// <param name="l">The level to log the message at</param>
		LogEvent(const char* m, LogLevel l) : message(m), level(l) {}
		
		LogLevel level;
		const char* message;
	};
}