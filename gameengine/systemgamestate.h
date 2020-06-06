#pragma once
#include "gamestate.h"

#include "rendersystem.h"
#include "systemmanager.h"
#include "entitymanager.h"
#include "shadermanager.h"
#include "uimanager.h"
#include "camera.h"
#include "events.h"

namespace engine {
	class SystemGameState : public GameState {
	public:
		SystemGameState(Window* w, EventBus& eb) : GameState(w, eb), camera(eb) {}
		virtual void initialise() override;
		virtual void update(double dt) override;
		virtual void render() override;
	protected:
		SystemManager systemManager;
		EntityManager entityManager;
		ShaderManager shaderManager;
		UIManager uiManager;
		Camera camera;
		void alignCamera();
		void handleMouseDrag(CameraEvent* e) { alignCamera(); }
	};
}