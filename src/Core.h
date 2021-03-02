#pragma once

#include <vector>

#include "GameObject.h"
#include "Window.h"
#include "Shader.h"
#include "Camera.h"
#include "Framebuffer.h"

class Engine
{
private:
Shader shader;

public:
Framebuffer framebuffer;
Window window;
std::vector<GameObject*> GameObjects;
Camera camera;

void (*update)();
	
	void Init(unsigned int window_width, unsigned int window_height, const char* window_title);
	
	void Update();
};

#include "Core.cpp"