#pragma once

#include "Vector4.h"
#include "Optimization.h"

template<typename T>
class Matrix4
{
private:

T m[4][4];

public:
	
	Matrix4(){}
	
	Matrix4(T const& v)
	{
		m[0][0] = v;
		m[1][1] = v;
		m[2][2] = v;
		m[3][3] = v;
	}
	
	Matrix4(const Vector4<T> &v1, const Vector4<T> &v2, const Vector4<T> &v3, const Vector4<T> &v4)
	{
		m[0][0] = v1.x; m[0][1] = v1.y; m[0][2] = v1.z; m[0][3] = v1.w; 
		m[1][0] = v2.x; m[1][1] = v2.y; m[1][2] = v2.z; m[1][3] = v2.w;
		m[2][0] = v3.x; m[2][1] = v3.y; m[2][2] = v3.z; m[2][3] = v3.w;
		m[3][0] = v4.x; m[3][1] = v4.y; m[3][2] = v4.z; m[3][3] = v4.w;
	}
	
	Matrix4(T const& x1, T const& y1, T const& z1, T const& w1,
			T const& x2, T const& y2, T const& z2, T const& w2,
			T const& x3, T const& y3, T const& z3, T const& w3,
			T const& x4, T const& y4, T const& z4, T const& w4)
	{
		m[0][0] = x1; m[0][1] = y1; m[0][2] = z1; m[0][3] = w1;
		m[1][0] = x2; m[1][1] = y2; m[1][2] = z2; m[1][3] = w2;
		m[2][0] = x3; m[2][1] = y3; m[2][2] = z3; m[2][3] = w3;
		m[3][0] = x4; m[3][1] = y4; m[3][2] = z4; m[3][3] = w4;
	}
	
	Matrix4(const Matrix4 &M)
	{
		m[0][0] = M[0][0]; m[0][1] = M[0][1]; m[0][2] = M[0][2]; m[0][3] = M[0][3];
		m[1][0] = M[1][0]; m[1][1] = M[1][1]; m[1][2] = M[1][2]; m[1][3] = M[1][3];
		m[2][0] = M[2][0]; m[2][1] = M[2][1]; m[2][2] = M[2][2]; m[2][3] = M[2][3];
		m[3][0] = M[3][0]; m[3][1] = M[3][1]; m[3][2] = M[3][2]; m[3][3] = M[3][3];
	}
	
	Matrix4(const float* M)
	{
		m[0][0] = M[0]; m[0][1] = M[1]; m[0][2] = M[2]; m[0][3] = M[3];
		m[1][0] = M[4]; m[1][1] = M[5]; m[1][2] = M[6]; m[1][3] = M[7];
		m[2][0] = M[8]; m[2][1] = M[9]; m[2][2] = M[10]; m[2][3] = M[11];
		m[3][0] = M[12]; m[3][1] = M[13]; m[3][2] = M[14]; m[3][3] = M[15];
	}
	
	Matrix4& operator=(const Matrix4 &M)
	{
		m[0][0] = M[0][0]; m[0][1] = M[0][1]; m[0][2] = M[0][2]; m[0][3] = M[0][3];
		m[1][0] = M[1][0]; m[1][1] = M[1][1]; m[1][2] = M[1][2]; m[1][3] = M[1][3];
		m[2][0] = M[2][0]; m[2][1] = M[2][1]; m[2][2] = M[2][2]; m[2][3] = M[2][3];
		m[3][0] = M[3][0]; m[3][1] = M[3][1]; m[3][2] = M[3][2]; m[3][3] = M[3][3];
		return *this;
	}
	
	float* operator[](unsigned int index) const
	{
		return m[index];
	}
	
	float* operator[](unsigned int index)
	{
		return m[index];
	}
	
	Matrix4 operator+(const Matrix4 &M) const
	{
		float res[16];
		add_mat4(m, &M[0][0], res);
		return Matrix4(res);
	}
	
	Matrix4 operator-(const Matrix4 &M) const
	{
		float res[16];
		sub_mat4(m, &M[0][0], res);
		return Matrix4(res);
	}
	
	Vector4<T> operator*(const Vector4<T> v) const
	{
		float res[4];
		mul_mat4_vec4(m, &v.x, res);
		return Vector4<T>(res);
	}
	
	Matrix4 operator*(const Matrix4 &M) const
	{
		float res[4][4];
		mul_mat4(&m[0][0], &M[0][0], &res[0][0])
		return Matrix4(&res[0][0]);
	}
};