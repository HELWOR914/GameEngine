#pragma once

template<typename T>
class Vector2
{
public:
	T x;
	T y;
	
	Vector2(){}
	
	Vector2(T const& X, T const& Y):
	x(X),
	y(Y)
	{}
	
	Vector2(const float *v)
	{
		x = v[0];
		y = v[1];
	}
	
	Vector2(const Vector2 &v)
	{
		this->x = v.x;
		this->y = v.y;
	}
	
	Vector2& operator=(const Vector2 &v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}
	
	Vector2 operator+(const Vector2 &v) const
	{
		return Vector2(x + v.x, 
					   y + v.y);
	}
	
	Vector2 operator-(const Vector2 &v) const
	{
		return Vector2(x - v.x, 
					   y - v.y);
	}
	
	T operator*(const Vector2 &v) const
	{
		return Vector2(x * v.x + 
					   y * v.y);
	}
	
	Vector2 operator*(T v) const
	{
		return Vector2(x * v, 
					   y * v);
	}
	
	Vector2 operator/(T v) const
	{
		return Vector2(x / v, 
					   y / v);
	}
	
	bool operator==(const Vector2 &v) const
	{
		return x == v.x && y == v.y;
	}
};