#pragma once

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

glm::quat to_quaternion(glm::vec3 const& eulerAngles)
{
	float roll_cos  = std::cos(eulerAngles.x / 2.0f);
	float pitch_cos = std::cos(eulerAngles.y / 2.0f);
	float yaw_cos   = std::cos(eulerAngles.z / 2.0f);
	
	float roll_sin  = std::sin(eulerAngles.x / 2.0f);
	float pitch_sin = std::sin(eulerAngles.y / 2.0f);
	float yaw_sin   = std::sin(eulerAngles.z / 2.0f);
	
	return quat(roll_cos * pitch_cos * yaw_cos + roll_sin * pitch_sin * yaw_sin,
				roll_sin * pitch_cos * yaw_cos - roll_cos * pitch_sin * yaw_sin,
				roll_cos * pitch_sin * yaw_cos + roll_sin * pitch_cos * yaw_sin,
				roll_cos * pitch_cos * yaw_sin - roll_sin * pitch_sin * yaw_cos);
}

glm::quat to_quaternion(const float roll, const float pitch, const float yaw)
{
	float roll_cos  = std::cos(roll / 2.0f);
	float pitch_cos = std::cos(pitch / 2.0f);
	float yaw_cos   = std::cos(yaw / 2.0f);
	
	float roll_sin  = std::sin(roll / 2.0f);
	float pitch_sin = std::sin(pitch / 2.0f);
	float yaw_sin   = std::sin(yaw / 2.0f);
	
	return quat(roll_cos * pitch_cos * yaw_cos + roll_sin * pitch_sin * yaw_sin,
				roll_sin * pitch_cos * yaw_cos - roll_cos * pitch_sin * yaw_sin,
				roll_cos * pitch_sin * yaw_cos + roll_sin * pitch_cos * yaw_sin,
				roll_cos * pitch_cos * yaw_sin - roll_sin * pitch_sin * yaw_cos);
}

glm::vec3 to_euler_angles(glm::quat const& q)
{
	float pitch = 2.0f * (q.w * q.y - q.z * q.x);
	std::abs(pitch) >= 1.0f ? pitch = std::copysign(M_PI / 2.0f, pitch) : pitch = std::asin(pitch);
		
	return glm::vec3(std::atan2(2.0f * (q.w * q.x + q.y * q.z), 1.0f - 2.0f * (q.x * q.x + q.y * q.y)),
					pitch,
					std::atan2(2.0f * (q.w * q.z + q.x * q.y), 1.0f - 2.0f * (q.y * q.y + q.z * q.z)));
}

glm::mat4 mat4_cast(glm::quat const& q)
{
	float qxx(q.x * q.x);
	float qyy(q.y * q.y);
	float qzz(q.z * q.z);
	float qxz(q.x * q.z);
	float qxy(q.x * q.y);
	float qyz(q.y * q.z);
	float qwx(q.w * q.x);
	float qwy(q.w * q.y);
	float qwz(q.w * q.z);
	
	return glm::mat4(1.0f - 2.0f * (qyy +  qzz), 2.0f * (qxy + qwz), 2.0f * (qxz - qwy), 0.0f,
					 2.0f * (qxy - qwz), 1.0f - 2.0f * (qxx +  qzz), 2.0f * (qyz + qwx), 0.0f,
					 2.0f * (qxz + qwy), 2.0f * (qyz - qwx), 1.0f - 2.0f * (qxx +  qyy), 0.0f,
					 0.0f, 0.0f, 0.0f, 1.0f);
}

glm::mat3 mat3_cast(glm::quat const& q)
{
	float qxx(q.x * q.x);
	float qyy(q.y * q.y);
	float qzz(q.z * q.z);
	float qxz(q.x * q.z);
	float qxy(q.x * q.y);
	float qyz(q.y * q.z);
	float qwx(q.w * q.x);
	float qwy(q.w * q.y);
	float qwz(q.w * q.z);
	
	return glm::mat3(1.0f - 2.0f * (qyy +  qzz), 2.0f * (qxy + qwz), 2.0f * (qxz - qwy),
					 2.0f * (qxy - qwz), 1.0f - 2.0f * (qxx +  qzz), 2.0f * (qyz + qwx),
					 2.0f * (qxz + qwy), 2.0f * (qyz - qwx), 1.0f - 2.0f * (qxx +  qyy));
}

glm::vec3 rotate_vec_by_quat(glm::quat q, glm::vec3 v)
{
	glm::vec3 q_v = glm::vec3(q.x, q.y, q.z);
	glm::vec3 t = 2.0f * glm::cross(q_v, v);
	return v + (t * q.w) + glm::cross(q_v, t);
}