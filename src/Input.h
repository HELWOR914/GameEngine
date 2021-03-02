#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "Window.h"

#define _KEEPING_UP 0
#define _KEEPING_DOWN 1
#define _DOWN 2
#define _UP 3

class Input
{
private:

static char keys[512];
static char mouse_buttons[8];

static glm::vec2 cursor_position;
static glm::vec2 cursor_position_offset;

	static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
	{
		cursor_position_offset.x = xpos - cursor_position.x;
		cursor_position_offset.y = ypos - cursor_position.y;
		cursor_position.x = xpos;
		cursor_position.y = ypos;
	}

	static void CallbackCheck()
	{
		for(int key = 0; key < 512; key++)
		{
			if(keys[key] == _DOWN)
			{
				keys[key] = _KEEPING_DOWN;
			}
			
			if(keys[key] == _UP)
			{
				keys[key] = _KEEPING_UP;
			}
		}
		
		for(int button = 0; button < 8; button++)
		{
			if(mouse_buttons[button] == _DOWN)
			{
				mouse_buttons[button] = _KEEPING_DOWN;
			}
			
			if(mouse_buttons[button] == _UP)
			{
				mouse_buttons[button] = _KEEPING_UP;
			}
		}
	}

	static void KeyCollback(GLFWwindow* window, int key, int, int action, int)
	{
		switch(action)
		{
			case GLFW_PRESS:
				keys[key] = _DOWN;
			return;
			
			case GLFW_RELEASE:
				keys[key] = _UP;
			return;
		}
	}
	
	static void MouseCollback(GLFWwindow* window, int button, int action, int mode)
	{
		switch(action)
		{
			case GLFW_PRESS:
				mouse_buttons[button] = _DOWN;
			return;
			
			case GLFW_RELEASE:
				mouse_buttons[button] = _UP;
			return;
		}
	}

public:
	
	inline static bool GetKeyDown(GLenum key)
	{
		return keys[key] == _DOWN;
	}
	
	inline static bool GetKeyUp(GLenum key)
	{
		return keys[key] == _UP;
	}
	
	inline static bool GetKeyHoldingDown(GLenum key)
	{
		return keys[key] == _KEEPING_DOWN;
	}
	
	inline static bool GetKeyHoldingUp(GLenum key)
	{
		return keys[key] == _KEEPING_UP;
	}
	
	inline static bool GetMouseButtonDown(GLenum button)
	{
		return mouse_buttons[button] == _DOWN;
	}
	
	inline static bool GetMouseButtonUp(GLenum button)
	{
		return mouse_buttons[button] == _UP;
	}
	
	inline static bool GetMouseButtonHoldingDown(GLenum button)
	{
		return mouse_buttons[button] == _KEEPING_DOWN;
	}
	
	inline static bool GetMouseButtonHoldingUp(GLenum button)
	{
		return mouse_buttons[button] == _KEEPING_UP;
	}
	
	inline static glm::vec2 GetCursorPosition()
	{
		return cursor_position;
	}
	
	inline static void GetCursorPosition(float &x, float &y)
	{
		x = cursor_position.x;
		y = cursor_position.y;
	}
	
	inline static glm::vec2 GetCursorPositionOffset()
	{
		return cursor_position_offset;
	}
	
	inline static void GetCursorPositionOffset(float &x, float &y)
	{
		x = cursor_position_offset.x;
		y = cursor_position_offset.y;
	}
	
	friend class Window;
};

char Input::keys[512];
char Input::mouse_buttons[8];

glm::vec2 Input::cursor_position(0.0f);
glm::vec2 Input::cursor_position_offset;

#undef _KEEPING_UP
#undef _KEEPING_DOWN
#undef _DOWN
#undef _UP
