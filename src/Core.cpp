#include "Core.h"
#include "Editor.h"

void Engine::Init(unsigned int window_width, unsigned int window_height, const char* window_title)
{
	window.Init(window_width, window_height, window_title);
	shader.CreateFast("src/Shaders/TextureShader.vs", "src/Shaders/TextureShader.fs");
	
	camera.angle = glm::radians(45.0f);
	camera.near = 0.01f;
	camera.far = 100.1f;
	camera.isOrtho = false;
	
	framebuffer.Create();
	
	Editor::e = this;
}

void Engine::Update()
{
	while(!window.ShouldClose())
	{
		framebuffer.Resize(window.GetWidth(), window.GetHeight());
		framebuffer.Bind();
		glEnable(GL_DEPTH_TEST);
	
		shader.Use();
		
		camera.Update(window.GetWidth(), window.GetHeight());
		window.PollEvents();
		window.ClearBuffers();
		Gui::NewFrame();
		
		update();
		
		shader.SetMat4("projection", camera.GetProjection());
		shader.SetMat4("view", camera.GetView());
		
		for(size_t i = 0; i < GameObjects.size(); i++)
		{
			shader.SetMat4("model", GameObjects[i]->transform.GetMatrix());
			GameObjects[i]->Draw();
		}
#ifndef BUILD
		Editor::Begin(window.GetWidth(), window.GetHeight());
		Editor::DrawHierarchy();
		Editor::DrawInspector();
#endif
		framebuffer.Unbind();
		
		glDisable(GL_DEPTH_TEST);
		framebuffer.Draw();
#ifndef BUILD
		ImGui::Begin("Viewport");
		ImGui::Image((void*)framebuffer.GetTexture(), ImVec2((float)window.GetWidth() * 0.5f, (float)window.GetHeight() * 0.5f), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::End();
		Editor::End();
		Gui::Render();
#endif
		window.SwapBuffers();
	}
}