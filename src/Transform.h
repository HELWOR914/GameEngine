#pragma once

#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Gui.h"
#include "Component.h"

namespace vec3
{
	extern const glm::vec3 UP        = glm::vec3( 0.0f, 1.0f, 0.0f);
	extern const glm::vec3 DOWN      = glm::vec3( 0.0f,-1.0f, 0.0f);
	extern const glm::vec3 RIGHT     = glm::vec3( 1.0f, 0.0f, 0.0f);
	extern const glm::vec3 LEFT      = glm::vec3(-1.0f, 0.0f, 0.0f);
	extern const glm::vec3 FORWARD   = glm::vec3( 0.0f, 0.0f, 1.0f);
	extern const glm::vec3 BACKWARD  = glm::vec3( 0.0f, 0.0f, 1.0f);
}

class Transform : public Component
{
public:
Transform *parent;
glm::quat rotation;
glm::vec3 position;
glm::vec3 scale;

	Transform():
	parent(nullptr),
	rotation(glm::vec3(0.0f)),
	position(0.0f),
	scale(glm::vec3(1.0f)),
	euler_a(0.0f)
	{}
	
	inline void Rotate(glm::vec3 const& direction, float angle)
	{
		angle /= 2.0f;
		glm::vec3 norm_direct = glm::normalize(direction);
		float _sin = std::sin(angle);
		
		rotation *= glm::quat(std::cos(angle), _sin * norm_direct.x, _sin * norm_direct.y, _sin * norm_direct.z);
	}
	
	inline void GlobalRotate(glm::vec3 const& direction, float angle)
	{
		angle /= 2.0f;
		glm::vec3 norm_direct = glm::normalize(direction);
		float _sin = std::sin(angle);
		
		rotation = glm::quat(cos(angle), _sin * norm_direct.x, _sin * norm_direct.y, _sin * norm_direct.z) * rotation;
	}
	
	void LookAt(glm::vec3 const& point)
	{
		glm::vec3 forwardVector = glm::normalize(point - position);
		if (std::abs(forwardVector.z + 1.0f) < 0.000001f)
		{
			rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
			return;
		}
		if (std::abs(forwardVector.z - 1.0f) <= 0.000001f)
		{
			rotation = glm::quat(0.0f, 0.0f, 1.0f, 0.0f);
			return;
		}
		//equals the cross with (0, 0, 1)
		glm::vec3 rotAxis = glm::vec3(-forwardVector.y, forwardVector.x, 0.0f);
		
		SetRotation(rotAxis, std::acos(forwardVector.z));
	}
	
	void LookAt(glm::vec3 const& point, glm::vec3 const& front)
	{
		glm::vec3 forwardVector = glm::normalize(point - position);
		
		float angle = glm::dot(front, forwardVector);
		
		if (std::abs(angle + 1.0f) < 0.000001f)
		{
			rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
			return;
		}
		if (std::abs(angle - 1.0f) <= 0.000001f)
		{
			rotation = glm::quat(0.0f, 0.0f, 1.0f, 0.0f);
			return;
		}
		glm::vec3 rotAxis = glm::cross(front, forwardVector);
		
		SetRotation(rotAxis, std::acos(forwardVector.z));
	}
	
	inline void LocalTranslate(glm::vec3 const& v)
	{
		glm::mat3 rot = glm::mat3_cast(rotation);
		position += rot[0] * v.x + rot[1] * v.y + rot[2] * v.z;
	}
	
	inline void Translate(glm::vec3 const& v)
	{
		position += v;
	}
	
	inline void Scale(glm::vec3 const& v)
	{
		scale *= v;
	}
	
	void SetRotation(glm::vec3 const& direction, float angle = 0.0f)
	{
		angle /= 2;
		glm::vec3 norm_direct = glm::normalize(direction);
		float _sin = std::sin(angle);
		
		rotation.x = _sin * norm_direct.x;
		rotation.y = _sin * norm_direct.y;
		rotation.z = _sin * norm_direct.z;
		
		rotation.w = std::cos(angle);
	}
	
	void SetEulerAngles(glm::vec3 const& eulerAngles)
	{
		float x_half = eulerAngles.x * 0.5;
		float y_half = eulerAngles.y * 0.5;
		float z_half = eulerAngles.z * 0.5;
		float c1 = std::cos(x_half);
		float s1 = std::sin(x_half);
		float c2 = std::cos(y_half);
		float s2 = std::sin(y_half);
		float c3 = std::cos(z_half);
		float s3 = std::sin(z_half);
		float c1c2 = c1 * c2;
		float s1s2 = s1 * s2;
		float c1s2 = c1 * s2;
		float s1c2 = s1 * c2;
		rotation.w = c1c2 * c3 - s1s2 * s3;
		rotation.x = s1c2 * c3 + c1s2 * s3;
		rotation.y = c1s2 * c3 - s1c2 * s3;
		rotation.z = c1c2 * s3 + s1s2 * c3;
	}
	
	glm::vec3 GetRotationEuler() const
	{
		glm::vec3 angles;
		float qXX = rotation.x * rotation.x;
		float qYY = rotation.y * rotation.y;
		float qZZ = rotation.z * rotation.z;
		float qWW = rotation.w * rotation.w;
		angles.x = std::atan2(-2.0f * (rotation.y * rotation.z - rotation.w * rotation.x), qWW - qXX - qYY + qZZ);
		angles.y = std::asin(2.0f * (rotation.x * rotation.z + rotation.w * rotation.y));
		angles.z = std::atan2(-2.0f * (rotation.x * rotation.y - rotation.w * rotation.z), qWW + qXX - qYY - qZZ);
		return angles;
	}
	
	glm::mat4 GetMatrix() const
	{
		glm::mat4 m(1.0f);
		m[3].x = position.x;
		m[3].y = position.y;
		m[3].z = position.z;
		m *= glm::mat4_cast(rotation);
		m[0] *= scale.x;
		m[1] *= scale.y;
		m[2] *= scale.z;
		
		if(parent)
			return parent->GetMatrix() * m;
			
		return m;
	}
#ifndef BUILD
private:
	glm::vec3 euler_a;

public:
	virtual void InspectorUpdate() override
	{
		ImGui::InputFloat3("position", &position.x);
	
		if(ImGui::SliderFloat3("rotation", &euler_a.x, 0, 360))
		{
			SetEulerAngles(glm::radians(euler_a));
		}
		
		ImGui::InputFloat3("scale", &scale.x);
	}
#endif
};