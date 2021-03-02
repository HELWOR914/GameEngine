#pragma once

#include <string>
#include <vector>

#include "Model/Mesh.h"
#include "Transform.h"
#include "Texture.h"
#include "Shader.h"
#include "Component.h"

class GameObject
{
private:
GameObject *parent;
std::vector<GameObject*> childs;
GLuint texture;

public:
std::vector<Component*> components;
Transform transform;
Mesh* mesh;
std::string name;

	GameObject():
	parent(nullptr),
	components{&transform},
	name("")
	{}

	void SetMesh(Mesh& mesh)
	{
		this->mesh = &mesh;
	}

	inline void Draw() const
	{
		glBindTexture(GL_TEXTURE_2D, texture);
		mesh->Draw();
	}
	
	inline void LoadTexture(const char* path)
	{
		texture = LoadImage(path);
	}
	
	inline void SetTexture(GLuint id)
	{
		texture = id;
	}
	
	inline void SetParent(GameObject* obj)
	{
		if(parent != obj)
		{			
			if(parent)
				parent->childs.pop_back();
			
			parent = obj;
			transform.parent = &obj->transform;
			
			if(obj)
				obj->childs.push_back(this);
		}
	}
	
	inline GameObject* GetParent() const
	{
		return parent;
	}
	
	inline size_t GetChildsCount() const
	{
		return childs.size();
	}
	
	inline std::vector<GameObject*> &GetChilds()
	{
		return childs;
	}
	
	inline void AddComponent(Component* comp)
	{
		components.push_back(comp);
	}
};
