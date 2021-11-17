#pragma once

class Vector2
{
public:
	Vector2() = default;
	Vector2(float x_in, float y_in);
	Vector2 operator+(const Vector2& other) const;
	Vector2& operator+=(const Vector2& other);
	Vector2 operator*(float other) const;
	Vector2& operator*=(float other);
	Vector2 operator-(const Vector2& other) const;
	Vector2& operator-=(const Vector2& other);
	float GetLength() const;
	float GetLengthSq() const;
	Vector2& Normalize();
	Vector2 GetNormalized() const;
public:
	float x;
	float y;
};
