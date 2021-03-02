#pragma once

#include "Vector2.h"
#include "Vector3.h"

template<typename T>
class Vector4
{
public:
	T x;
	T y;
	T z;
	T w;
	
	Vector4(){}
	
	Vector4(T const& X, T const& Y, T const& Z, T const& W):
	x(X),
	y(Y),
	z(Z),
	w(W)
	{}
	
	Vector4(const float *v)
	{
		x = v[0];
		y = v[1];
		z = v[2];
		w = v[3];
	}
	
	Vector4(const Vector4 &v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
	}
	
	Vector4(const Vector3<T> &v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = T(0);
	}
	
	Vector4(const Vector2<T> &v)
	{
		x = v.x;
		y = v.y;
		z = T(0);
		w = T(0);
	}
	
	Vector4& operator=(const Vector4 &v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
		return *this;
	}
	
	Vector4 operator+(const Vector4 &v) const
	{
		return Vector4(x + v.x, 
					   y + v.y,
					   z + v.z,
					   w + v.w);
	}
	
	Vector4 operator-(const Vector4 &v) const
	{
		return Vector4(x - v.x, 
					   y - v.y,
					   z - v.z,
					   w - v.w);
	}
	
	T operator*(const Vector4 &v) const
	{
		return Vector4(x * v.x + 
					   y * v.y +
					   z * v.z +
					   w * v.w);
	}
	
	Vector4 operator*(T v) const
	{
		return Vector4(x * v, 
					   y * v,
					   z * v,
					   w * v);
	}
	
	Vector4 operator/(T v) const
	{
		return Vector4(x / v, 
					   y / v,
					   z / v,
					   w / v);
	}
	
	bool operator==(const Vector4 &v) const
	{
		return x == v.x && y == v.y && z == v.z && w == v.w;
	}
};