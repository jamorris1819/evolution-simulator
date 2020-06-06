#pragma once
#include "uiwindow.h"
#include "window.h"
#include <vector>
#include <memory>

namespace engine {
	class UIManager {
	public:
		void initialise(Window* window);
		void render();
		void addWindow(UIWindow* window);
		void unload();
	private:
		std::vector<std::unique_ptr<UIWindow>> windows;
	};
}