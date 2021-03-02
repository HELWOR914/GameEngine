#pragma once

#include "Gui.h"
#include "Core.h"

class Editor
{
private:
static GameObject* obj;

public:
static Engine* e;

	static void DrawInspector()
	{
		if(!obj)
			return;
			
		ImGui::Begin("Inspector");
		for(size_t i = 0; i < obj->components.size(); i++)
		{
			if(ImGui::TreeNode(obj->components[i]->GetName()))
			{
				obj->components[i]->InspectorUpdate();
				ImGui::TreePop();
			}
		}
		ImGui::End();
	}
	
	static void DrawHierarchyItem(std::vector<GameObject*>& objects)
	{
		for(size_t i = 0; i < objects.size(); i++)
		{
			if(ImGui::TreeNode(objects[i]->name.c_str()))
			{
				obj = objects[i];
				DrawHierarchyItem(objects[i]->GetChilds());
				ImGui::TreePop();
			}
		}
	}
	
	static void DrawHierarchy()
	{
		ImGui::Begin("Hierarchy");
	
		for(size_t i = 0;i < e->GameObjects.size();i++)
		{
			if(e->GameObjects[i]->GetParent() == nullptr)
			{
				if(ImGui::TreeNode(e->GameObjects[i]->name.c_str()))
				{
					obj = e->GameObjects[i];
					DrawHierarchyItem(e->GameObjects[i]->GetChilds());
					ImGui::TreePop();
				}
			}
		}
		
		ImGui::End();
	}
	
	static void Begin(int width, int height)
	{
		ImGui::SetNextWindowSize(ImVec2(width, height));
		ImGui::Begin("Game engine");
	}
	
	static void End()
	{
		ImGui::End();
	} 
};

GameObject* Editor::obj;
Engine* Editor::e;