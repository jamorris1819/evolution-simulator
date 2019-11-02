#include "menu.h"
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <vector>
#include "glm\glm.hpp"
#include <string>
#include "nodegene.h"
#include "creaturebody.h"
#include "input.h"
#include "terrainmanager.h"
#include <thread>

Menu::Menu() {}

void Menu::initialise(GLFWwindow* window)
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsDark();
	//io.FontGlobalScale = 2.0f;

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

	std::cout << "ImGui has initialised successfully" << std::endl;
}

void Menu::render()
{
	// Create new frames.
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::ShowDemoWindow();

	renderMenuBar();

	for (int i = 0; i < windows.size(); i++) {
		MenuWindow* menuWindow = windows[i];
		if (menuWindow->isVisible()) menuWindow->render();
	}

	// Render frame.
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Menu::addWindow(MenuWindow* menuWindow)
{
	menuWindow->initialise();
	windows.push_back(menuWindow);
}

void Menu::renderOverlay()
{
	/*const float DISTANCE = 10.0f;
	static int corner = 2;
	static bool a = true;
	ImGuiIO& io = ImGui::GetIO();
	if (camera == nullptr) return;
	glm::vec3 originalMouse = glm::vec3(io.MousePos.x / 64, -io.MousePos.y / 64, 0) ;
	originalMouse.x /= camera->zoom;
	originalMouse.y /= camera->zoom * (1920 / 1080);
	glm::mat4 te = camera->projection * camera->view;

	glm::mat4 real = glm::translate(glm::mat4(1), originalMouse) * camera->view * camera->projection;

	originalMouse /= camera->zoom;
	glm::mat4 aa = glm::translate(glm::mat4(1), originalMouse);


	

	glm::vec3 mouseinput = glm::vec3(Input::mouseCoordinates, 1.0f);
	mouseinput.x = ((mouseinput.x / 1920) * 2) - 1;
	mouseinput.y = -1 * (((mouseinput.y / 1080) * 2) - 1);

	glm::mat4 pv = camera->projection;
	glm::mat4 ipv = glm::inverse(pv);

	glm::vec3 ppp = (glm::vec4(mouseinput, 1.0f) * ipv);

	/*glm::vec3 t =  glm::unProject(
		mouseinput / camera->zoom,
		camera->view,
		camera->projection,
		camera->viewport
	);*/
	/*glm::vec3 mousePos = glm::vec4(ppp, 0.0f) - glm::vec4(camera->position.x, camera->position.y, 0.0f, 0.0f);/*
		
		- glm::vec4(camera->viewport.z / 2.0f, camera->viewport.w / 2.0f, 0.0f, 0.0f)
		- glm::vec4(ppp, 0.0f); // glm::vec3(te[3]) + glm::vec3();// glm::vec3(io.MousePos.x, -io.MousePos.y, 0);*/


	/*if (corner != -1)
	{
		ImVec2 window_pos = ImVec2((corner & 1) ? io.DisplaySize.x - DISTANCE : DISTANCE, (corner & 2) ? io.DisplaySize.y - DISTANCE : DISTANCE);
		ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
		ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
	}
	ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
	if (ImGui::Begin("Example: Simple overlay", &a, (corner != -1 ? ImGuiWindowFlags_NoMove : 0) | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
	{
		ImGui::Text("Description Overlay");
		ImGui::Separator();
		if (ImGui::IsMousePosValid())
			ImGui::Text("Mouse Position: (%.1f,%.1f)", mousePos.x, mousePos.y);
		else
			ImGui::Text("Mouse Position: <invalid>");
		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::MenuItem("Custom", NULL, corner == -1)) corner = -1;
			if (ImGui::MenuItem("Top-left", NULL, corner == 0)) corner = 0;
			if (ImGui::MenuItem("Top-right", NULL, corner == 1)) corner = 1;
			if (ImGui::MenuItem("Bottom-left", NULL, corner == 2)) corner = 2;
			if (ImGui::MenuItem("Bottom-right", NULL, corner == 3)) corner = 3;
			ImGui::EndPopup();
		}
	}
	ImGui::End();*/
}

void Menu::renderMenuBar()
{
	if (ImGui::BeginMainMenuBar()) {
		for (int i = 0; i < windows.size(); i++) {
			if (ImGui::MenuItem(windows[i]->windowName)) {
				windows[i]->setVisible(!windows[i]->isVisible());
			}
		}

		ImGui::EndMainMenuBar();
	}
}

void Menu::unload()
{
	for (int i = 0; i < windows.size(); i++) {
		delete windows[i];
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
