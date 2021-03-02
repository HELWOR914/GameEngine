#pragma once

#include <glm/glm.hpp>

class perspectiveLH;
class Camera
{
private:

glm::mat4 projection;
glm::mat4 view;
public:

glm::quat rotation;
glm::vec3 position;

float width;
float height;
float angle;
float near;
float far;
bool isOrtho;

	Camera():
	view(1.0f),
	rotation(glm::vec3(0.0f, 0.0f, 0.0f)),
	position(0.0f)
	{}
	
	inline void CreatePerspective()
	{
		projection = glm::perspectiveLH(angle, width/height, near, far);
		isOrtho = false;
	}
	
	inline void CreateOrtho()
	{
		float right = width/2.0f;
		float left = -right;
		float top = height/2.0f;
		float bottom = -top;
		projection = glm::orthoLH(left, right, bottom, top, near, far);
		isOrtho = true;
	}
	inline void Translate(glm::vec3 const& v)
	{
		view = glm::translate(view, -v);
		position = -view[3];
	}
	
	inline void GlobalTranslate(glm::vec3 const& v)
	{
		view = glm::global_translate(view, -v);
		position -= v;
	}
	
	inline void SetPosition(glm::vec3 const& v)
	{
		position = -v;
		view = glm::set_position(view, -v);
	}
	
	inline glm::mat4 GetProjection() const
	{
		return projection;
	}
	
	inline glm::mat4 GetView() const
	{
		return view;
	}
	
	inline void Update(int _width, int _height)
	{
		if(width == _width && height == _height)
			return;
		width = _width;
		height = _height;
		if(isOrtho)
		{
			CreateOrtho();
			return;
		}
		CreatePerspective();
	}
};