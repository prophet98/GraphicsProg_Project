#include "pch.h"
#include "Gameobject.h"

Gameobject::Gameobject(float _left, float _right, float _top, float _bottom) : left(_left), right(_right), top(_top), bottom(_bottom)
{
}

Gameobject::Gameobject(const Vector2& topLeft, const Vector2& bottomRight) : Gameobject(topLeft.x, bottomRight.x, topLeft.y, bottomRight.y)
{
}

Gameobject::Gameobject(const Vector2& topLeft, float width, float height) : Gameobject(topLeft, topLeft + Vector2(width, height))
{
}

bool Gameobject::IsOverlapping(const Gameobject& other) const
{
	return right > other.left && left < other.right&& bottom>other.top && top < other.bottom;
}
