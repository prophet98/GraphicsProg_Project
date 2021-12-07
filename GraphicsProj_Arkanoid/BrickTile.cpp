#include "pch.h"
#include "BrickTile.h"

bool BrickTile::DoBallCollision(Ball& ball)
{
	if (!isDestroyed && IsOverlappingWith(ball.GetRect()))
	{
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
		return true;
	}
	return false;
}

bool BrickTile::IsOverlappingWith(const RECT& other)
{
	return rect.right > other.left && rect.left < other.right
		&& rect.bottom > other.top && rect.top < other.bottom;
}

