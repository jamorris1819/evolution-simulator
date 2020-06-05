#pragma once
#include "gamestate.h"

#include "rendersystem.h"
#include "systemmanager.h"
#include "entitymanager.h"
#include "shadermanager.h"

namespace engine {
	class SystemGameState : public GameState {
	public:
		SystemGameState(EventBus& eb) : GameState(eb) {}
		virtual void initialise() override;
		virtual void update() override;
		virtual void render() override;
	protected:
		SystemManager systemManager;
		EntityManager entityManager;
		ShaderManager shaderManager;
	};
}