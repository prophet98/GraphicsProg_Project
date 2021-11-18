#pragma once
#include <SimpleMath.h>
using Vec2 = DirectX::SimpleMath::Vector2;
class Ball
{
public:
	Ball(const Vec2& _pos, const Vec2& _vel);
private:
	static constexpr float radius = 7.0f;
	Vec2 pos;
	Vec2 vel;
};
