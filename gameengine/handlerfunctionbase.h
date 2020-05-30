#pragma once
#include "event.h"

namespace engine {
	class HandlerFunctionBase {
	public:
		void exec(Event* ev) {
			call(ev);
		}
		
	private:
		virtual void call(Event* ev) = 0;
	};
}