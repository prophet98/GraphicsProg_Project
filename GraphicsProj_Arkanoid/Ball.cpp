#include "pch.h"
#include "Ball.h"

Ball::Ball(const Vec2& _pos, const Vec2& _vel) : pos(_pos), vel(_vel)
{

}

void Ball::Update(float dt)
{
	pos += vel * dt;
}

Vec2 Ball::GetPosition()
{
	return pos;
}

bool Ball::DoWallCollision(const RECT& walls)
{
	bool collided = false;
	const RECT rect = GetRect();
	if (rect.left < walls.left)
	{
		ReboundX();
		collided = true;
	}
	else if (rect.right > walls.right)
	{
		ReboundX();
		collided = true;
	}
	if (rect.top < walls.top)
	{
		ReboundY();
		collided = true;
	}
	else if (rect.bottom > walls.bottom)
	{
		ReboundY();
		collided = true;
	}

	return collided;
}

void Ball::ReboundX()
{
	vel.x = -vel.x;
}

void Ball::ReboundY()
{
	vel.y = -vel.y;
}

RECT Ball::GetRect()
{
	const Vec2 half(radius, radius);
	RECT ballRect;
	ballRect.left = pos.x - half.x;
	ballRect.top = pos.y - half.y;
	ballRect.right = pos.x + half.x;
	ballRect.bottom = pos.y + half.y;
	return ballRect;
}



