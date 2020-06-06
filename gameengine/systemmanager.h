#pragma once
#include <vector>
#include "system.h"
#include <memory>

namespace engine {
	class SystemManager {
	public:
		void addSystem(System* system);
		template<typename SysType>
		SysType getSystem();
		void update(std::vector<std::unique_ptr<Entity>>&, double);
		void render(std::vector<std::unique_ptr<Entity>>&);
	private:
		std::vector<std::unique_ptr<System>> systems;
	};

	template<typename SysType>
	inline SysType SystemManager::getSystem() {
		return SysType();
	}
}