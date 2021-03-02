#pragma once

#define RADIANS(a) a * M_PI / 180

#include <xmmintrin.h>
#include <cmath>

#include <glm/glm.hpp>

namespace glm
{
	glm::mat4 rotate_x(const glm::mat4& m, const float& angle)
	{
		glm::mat4 Result(1.0f);
		
		Result[1].y =  cos(angle);
		Result[1].z =  sin(angle);
		
		Result[2].y = -sin(angle);
		Result[2].z =  cos(angle);
		
		return m * Result;
	}
	
	glm::mat4 rotate_y(const glm::mat4& m, const float& angle)
	{
		glm::mat4 Result(1.0f);
		
		Result[0].x =  cos(angle);
		Result[0].z = -sin(angle);
		
		Result[2].x =  sin(angle);
		Result[2].z =  cos(angle);
		
		return m * Result;
	}
	
	glm::mat4 rotate_z(const glm::mat4& m, const float& angle)
	{
		glm::mat4 Result(1.0f);
		
		Result[0].x =  cos(angle);
		Result[0].y =  sin(angle);
		
		Result[1].x = -sin(angle);
		Result[1].y =  cos(angle);
		
		return m * Result;
	}
	
	glm::mat4 rotateEuler(glm::mat4 const& m, glm::vec3 const& v)
	{
		float cos_roll  = std::cos(v.z);
		float cos_pitch = std::cos(v.y);
		float cos_yaw   = std::cos(v.x);
		
		float sin_roll  = std::sin(v.z);
		float sin_pitch = std::sin(v.y);
		float sin_yaw   = std::sin(v.x);
		
		glm::mat4 Result(1.0f);
		
		Result[0].x = cos_roll * cos_pitch;
		Result[0].y = sin_roll * cos_pitch;
		Result[0].z = -sin_pitch;
		
		Result[1].x = cos_roll * sin_pitch * sin_yaw - sin_roll * cos_yaw;
		Result[1].y = sin_roll * sin_pitch * sin_yaw + cos_roll * cos_yaw;
		Result[1].z = cos_pitch * sin_yaw;
		
		Result[2].x = cos_roll * sin_pitch * cos_yaw + sin_roll * sin_yaw;
		Result[2].y = sin_roll * sin_pitch * cos_yaw - cos_roll * sin_yaw;
		Result[2].z = cos_pitch * cos_yaw;
		
		return m * Result;
	}
}