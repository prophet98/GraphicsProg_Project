#include "pch.h"
#include "Paddle.h"


Paddle::Paddle(Vec2 _pos, float _halfWidth, float _halfHeight) : pos(_pos), halfWidth(_halfWidth), halfHeight(_halfHeight)
{
	
}

bool Paddle::DoBallCollision(Ball& ball)
{
	if (IsOverlappingWith(ball.GetRect()))
	{
		ball.ReboundY();
		return true;
	}
	return false;
}

void Paddle::DoWallCollision(const RECT& walls)
{
	const RECT paddleRect = GetRect();
	if (paddleRect.left < walls.left)
	{
		pos.x += walls.left - paddleRect.left;
	}
	if (paddleRect.right > walls.right)
	{
		pos.x -= paddleRect.right - walls.right;
	}

}


void Paddle::Update(const DirectX::Keyboard::State key, float deltaTime)
{
	if (key.Left)
	{
		pos.x -= speed * deltaTime;
	}
	if (key.Right)
	{
		pos.x += speed * deltaTime;
	}
}


RECT Paddle::GetRect() const
{
	const Vec2 half(halfWidth, halfHeight);
	RECT paddleRect;
	paddleRect.left = pos.x - half.x;
	paddleRect.top = pos.y - half.y;
	paddleRect.right = pos.x + half.x;
	paddleRect.bottom = pos.y + half.y;
	return paddleRect;
}

void Paddle::Draw(const GeometryBatch& batch)
{
	v1 = VertexPositionColor(DirectX::SimpleMath::Vector2(GetRect().left, GetRect().top), color);
	v2 = VertexPositionColor(DirectX::SimpleMath::Vector2(GetRect().right, GetRect().top), color);
	v3 = VertexPositionColor(DirectX::SimpleMath::Vector2(GetRect().right, GetRect().bottom), color);
	v4 = VertexPositionColor(DirectX::SimpleMath::Vector2(GetRect().left, GetRect().bottom), color);

	batch->DrawQuad(v1, v2, v3, v4);
}
