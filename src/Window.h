#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//#include "Input.h"

#include "Gui.h"

class Window
{
private:
GLFWwindow* mainWindow;

int WIDTH;
int HEIGHT;

public:

	int Init(GLuint width, GLuint height, const char* title)
	{
		WIDTH = width;
		HEIGHT = height;
		//==========Init GLFW==========
		if(!glfwInit())
		{
			std::cerr << "Failed to init GLFW" << std::endl;
			glfwTerminate();
			return -1;
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, 16);
		
		//========Create window========
		mainWindow = glfwCreateWindow(WIDTH, HEIGHT, title, nullptr, nullptr);
		if(!mainWindow)
		{
			std::cerr << "Failed to create WINDOW" << std::endl;
			glfwDestroyWindow(mainWindow);
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(mainWindow);
		
		Gui::Setup(mainWindow);
		
		/*glfwSetKeyCallback(mainWindow, Input::KeyCollback);
		glfwSetMouseButtonCallback(mainWindow, Input::MouseCollback);
		glfwSetCursorPosCallback(mainWindow, Input::CursorPosCallback);
		Input::cursor_position = Input::GetCursorPosition();*/
		//==========Init GLEW==========
		glewExperimental = GL_TRUE;
		if(glewInit() != GLEW_OK)
		{
			std::cerr << "Failed to init GLEW" << std::endl;
			glfwTerminate();
			return -1;
		}
		
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glViewport(0, 0, WIDTH, HEIGHT);
		
		return 0;
	}
	
	inline void PollEvents() const
	{
		//Input::cursor_position_offset = glm::vec2(0.0f, 0.0f);
		glfwPollEvents();
		//Input::CallbackCheck();
	}
	
	inline bool ShouldClose() const
	{
		return glfwWindowShouldClose(mainWindow);
	}
	
	inline void ClearBuffers() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	
	inline void SwapBuffers()
	{
		glfwSwapBuffers(mainWindow);
		
		glfwGetFramebufferSize(mainWindow, &WIDTH, &HEIGHT);
		glViewport(0, 0, WIDTH, HEIGHT);
	}
	
	inline void SetTitle(const char* title)
	{
		glfwSetWindowTitle(mainWindow, title);
	}
	
	inline int GetWidth() const
	{
		return WIDTH;
	}
	
	inline int GetHeight() const
	{
		return HEIGHT;
	}
	
	inline GLFWwindow* GetWindow()
	{
		return mainWindow;
	}
	
	inline ~Window()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
	}
};