#pragma once

#include "imGui/imgui.h"
#include "imGui/imgui_impl_opengl3.h"
#include "imGui/imgui_impl_glfw.h"

class Gui
{
private:

public:
	
	inline static void Setup(GLFWwindow* window)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();  
		ImGuiIO &io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330 core");
	}
	
	inline static void NewFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}
	
	inline static void Render()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
};