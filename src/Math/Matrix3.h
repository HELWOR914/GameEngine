#pragma once

#include "Vector3.h"

template<typename T>
class Matrix3
{
private:

T m[3][3];

public:
	
	Matrix3(){}
	
	Matrix3(T const& v)
	{
		m[0][0] = v;
		m[1][1] = v;
		m[2][2] = v;
	}
	
	Matrix3(const Vector3<T> &v1, const Vector3<T> &v2, const Vector3<T> &v3)
	{
		m[0][0] = v1.x; m[0][1] = v1.y; m[0][2] = v1.z;
		m[1][0] = v2.x; m[1][1] = v2.y; m[1][2] = v2.z;
		m[2][0] = v3.x; m[2][1] = v3.y; m[2][2] = v3.z;
	}
	
	Matrix3(T const& x1, T const& y1, T const& z1,
			T const& x2, T const& y2, T const& z2,
			T const& x3, T const& y3, T const& z3)
	{
		m[0][0] = x1; m[0][1] = y1; m[0][2] = z1;
		m[1][0] = x2; m[1][1] = y2; m[1][2] = z2;
		m[2][0] = x3; m[2][1] = y3; m[2][2] = z3;
	}
	
	Matrix3(const Matrix3 &M)
	{
		m[0][0] = M[0][0]; m[0][1] = M[0][1]; m[0][2] = M[0][2];
		m[1][0] = M[1][0]; m[1][1] = M[1][1]; m[1][2] = M[1][2];
		m[2][0] = M[2][0]; m[2][1] = M[2][1]; m[2][2] = M[2][2];
	}
	
	Matrix3& operator=(const Matrix3 &M)
	{
		m[0][0] = M[0][0]; m[0][1] = M[0][1]; m[0][2] = M[0][2];
		m[1][0] = M[1][0]; m[1][1] = M[1][1]; m[1][2] = M[1][2];
		m[2][0] = M[2][0]; m[2][1] = M[2][1]; m[2][2] = M[2][2];
		return *this;
	}
	
	float* operator[](unsigned int index)
	{
		return m[index];
	}
	
	float* operator[](unsigned int index) const
	{
		return m[index];
	}
	
	Matrix3 operator+(const Matrix3 &M) const
	{
		return Matrix3(m[0][0] + M[0][0], m[0][1] + M[0][1], m[0][2] + M[0][2],
					   m[1][0] + M[1][0], m[1][1] + M[1][1], m[1][2] + M[1][2],
					   m[2][0] + M[2][0], m[2][1] + M[2][1], m[2][2] + M[2][2]);
	}
	
	Matrix3 operator-(const Matrix3 &M) const
	{
		return Matrix3(m[0][0] - M[0][0], m[0][1] - M[0][1], m[0][2] - M[0][2],
					   m[1][0] - M[1][0], m[1][1] - M[1][1], m[1][2] - M[1][2],
					   m[2][0] - M[2][0], m[2][1] - M[2][1], m[2][2] - M[2][2]);
	}
	
	Vector3<T> operator*(const Vector3<T> v) const
	{
		return Vector3<T>(m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z,
						  m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z,
						  m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z);
	}
	
	Matrix3 operator*(const Matrix3 &M) const
	{
		return Matrix3(m[0][0] * M[0][0]   +   m[0][1] * M[1][0]   +   m[0][2] * M[2][0],
					   m[0][0] * M[0][1]   +   m[0][1] * M[1][1]   +   m[0][2] * M[2][1],
					   m[0][0] * M[0][2]   +   m[0][1] * M[1][2]   +   m[0][2] * M[2][2],
					   m[1][0] * M[0][0]   +   m[1][1] * M[1][0]   +   m[1][2] * M[2][0],
					   m[1][0] * M[0][1]   +   m[1][1] * M[1][1]   +   m[1][2] * M[2][1],
					   m[1][0] * M[0][2]   +   m[1][1] * M[1][2]   +   m[1][2] * M[2][2],
					   m[2][0] * M[0][0]   +   m[2][1] * M[1][0]   +   m[2][2] * M[2][0],
					   m[2][0] * M[0][1]   +   m[2][1] * M[1][1]   +   m[2][2] * M[2][1],
					   m[2][0] * M[0][2]   +   m[2][1] * M[1][2]   +   m[2][2] * M[2][2]);
	}
};