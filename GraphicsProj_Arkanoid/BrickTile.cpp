#include "pch.h"
#include "BrickTile.h"
#include <assert.h>

void BrickTile::ExecuteBallCollision(Ball& ball)
{
	assert(CheckBallCollision(ball));

	const Vec2 ballPos = ball.GetPosition();
	if (ballPos.x >= rect.left && ballPos.x <= rect.right)
	{
		ball.ReboundY();

	}
	else
	{
		ball.ReboundX();
	}
	isDestroyed = true;

}

bool BrickTile::CheckBallCollision(Ball& ball)
{
	return !isDestroyed && IsOverlappingWith(ball.GetRect());
}

bool BrickTile::IsOverlappingWith(const RECT& other)
{
	return rect.right > other.left && rect.left < other.right
		&& rect.bottom > other.top && rect.top < other.bottom;
}
Vec2 BrickTile::GetCenter() const
{
	return Vec2((rect.left + rect.right) / 2.0f, (rect.top + rect.bottom) / 2.0f);
}
