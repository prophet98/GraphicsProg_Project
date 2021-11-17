#pragma once
#include "Vector2.h"
class Gameobject
{
	//each class object in the game is a rectangle, this are the 4 sizes of each entity
public:
	Gameobject() = default;
	Gameobject(float _left, float _right, float _top, float _bottom);
	Gameobject(const Vector2& topLeft, const Vector2& bottomRight);
	Gameobject(const Vector2& topLeft, float width, float height);

	bool IsOverlapping(const Gameobject& other) const;

	float left;
	float right;
	float top;
	float bottom;
};

