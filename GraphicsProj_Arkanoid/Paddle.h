#pragma once
#include "Ball.h"	
#include "BrickTile.h"
using GeometryBatch = std::unique_ptr<DirectX::PrimitiveBatch< DirectX::VertexPositionColor>>;

class Paddle : public BrickTile
{
public:
	Paddle(Vec2 _pos, float _halfWidth, float _halfHeight);
	bool DoBallCollision(Ball& ball);
	void DoWallCollision(const RECT& walls);
	void Update(const DirectX::Keyboard::State key, float deltaTime);
	RECT GetRect()const;
	void Draw(const GeometryBatch& batch);
	bool IsOverlappingWith(const RECT& rect) override;

private:
	DirectX::XMVECTORF32 color = DirectX::Colors::Wheat;
	float halfWidth;
	float halfHeight;
	float speed = 500.0f;
	Vec2 pos;

	VertexPositionColor v1;
	VertexPositionColor v2;
	VertexPositionColor v3;
	VertexPositionColor v4;

	float exitXValue = 0.045f;
};

