#include "pch.h"
#include "uimanager.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace engine {
	void UIManager::initialise(Window* window) {
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(window->getWindow(), true);
		ImGui_ImplOpenGL3_Init();
	}

	void UIManager::render() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		for (auto& window : windows) {
			if (window.get()->isVisible())
				window.get()->render();
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void UIManager::addWindow(UIWindow* window) {
		std::unique_ptr<UIWindow> pointer(window);

		windows.push_back(std::move(pointer));
	}

	void UIManager::unload() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
}