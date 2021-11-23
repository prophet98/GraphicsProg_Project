#pragma once
#include <Ball.h>

using namespace DirectX;

class Gameobject;

class BrickTile
{
public:
	BrickTile(const RECT& _rect, XMVECTORF32 _color) : rect(_rect), m_color(_color) {

		v1 = VertexPositionColor(DirectX::SimpleMath::Vector2(_rect.left, _rect.top), m_color);
		v2 = VertexPositionColor(DirectX::SimpleMath::Vector2(_rect.right, _rect.top), m_color);
		v3 = VertexPositionColor(DirectX::SimpleMath::Vector2(_rect.right, _rect.bottom), m_color);
		v4 = VertexPositionColor(DirectX::SimpleMath::Vector2(_rect.left, _rect.bottom), m_color);
		isDestroyed = false;
	}
	bool DoBallCollision(Ball& ball);

public:
	VertexPositionColor v1;
	VertexPositionColor v2;
	VertexPositionColor v3;
	VertexPositionColor v4;
	bool isDestroyed;

private:
	RECT rect;
	XMVECTORF32 m_color;
	bool IsOverlappingWith(const RECT& other);
};

