#include "pch.h"
#include "Ball.h"

Ball::Ball(const Vec2& _pos, const Vec2& _vel) : pos(_pos),vel(_vel)
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



