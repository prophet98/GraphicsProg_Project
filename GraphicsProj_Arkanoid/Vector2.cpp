#include "pch.h"
#include "Vector2.h"
#include <cmath>

Vector2::Vector2(float x_in, float y_in)
	:
	x(x_in),
	y(y_in)
{
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(x + other.x, y + other.y);
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	return *this = *this + other;
}

Vector2 Vector2::operator*(float other) const
{
	return Vector2(x * other, y * other);
}

Vector2& Vector2::operator*=(float other)
{
	return *this = *this * other;
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(x - other.x, y - other.y);
}

Vector2& Vector2::operator-=(const Vector2& other)
{
	return *this = *this - other;
}

float Vector2::GetLength() const
{
	return std::sqrt(GetLengthSq());
}

float Vector2::GetLengthSq() const
{
	return x * x + y * y;
}

Vector2& Vector2::Normalize()
{
	return *this = GetNormalized();
}

Vector2 Vector2::GetNormalized() const
{
	const float len = GetLength();
	if (len != 0.0f)
	{
		return *this * (1.0f / len);
	}
	return *this;
}