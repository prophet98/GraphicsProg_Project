#include "pch.h"
#include "BrickTile.h"

bool BrickTile::DoBallCollision(Ball& ball)
{
	if (!isDestroyed && IsOverlappingWith(ball.GetRect()))
	{
		ball.ReboundY();
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

