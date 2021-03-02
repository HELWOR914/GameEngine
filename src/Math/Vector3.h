#pragma once

#include "Vector2.h"

template<typename T>
class Vector3
{
public:
	T x;
	T y;
	T z;
	
	Vector3(){}
	
	Vector3(T const& X, T const& Y, T const& Z):
	x(X),
	y(Y),
	z(Z)
	{}
	
	Vector3(const float *v)
	{
		x = v[0];
		y = v[1];
		z = v[2];
	}
	
	Vector3(const Vector3 &v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}
	
	Vector3(const Vector2<T> &v)
	{
		x = v.x;
		y = v.y;
		z = T(0);
	}
	
	Vector3& operator=(const Vector3 &v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}
	
	Vector3 operator+(const Vector3 &v) const
	{
		return Vector3(x + v.x, 
					   y + v.y,
					   z + v.z);
	}
	
	Vector3 operator-(const Vector3 &v) const
	{
		return Vector3(x - v.x, 
					   y - v.y,
					   z - v.z);
	}
	
	T operator*(const Vector3 &v) const
	{
		return Vector3(x * v.x + 
					   y * v.y +
					   z * v.z);
	}
	
	Vector3 operator*(T v) const
	{
		return Vector3(x * v, 
					   y * v,
					   z * v);
	}
	
	Vector3 operator/(T v) const
	{
		return Vector3(x / v, 
					   y / v,
					   z / v);
	}
	
	bool operator==(const Vector3 &v) const
	{
		return x == v.x && y == v.y && z == v.z;
	}
};