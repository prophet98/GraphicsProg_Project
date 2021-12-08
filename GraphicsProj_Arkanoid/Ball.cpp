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

int Ball::DoWallCollision(const RECT& walls)
{
	int collided = 0;
	const RECT rect = GetRect();
	if (rect.left < walls.left)
	{
		pos.x += walls.left - rect.left;
		ReboundX();
		collided = 1;
	}
	else if (rect.right > walls.right)
	{
		pos.x -= rect.right - walls.right;
		ReboundX();
		collided = 1;
	}
	if (rect.top < walls.top)
	{
		pos.y += walls.top - rect.top;

		ReboundY();
		collided = 1;
	}
	else if (rect.bottom > walls.bottom)
	{
		pos.y -= rect.bottom - walls.bottom;

		ReboundY();
		collided = 2;
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

Vec2 Ball::GetVel() const
{
	return vel;
}



