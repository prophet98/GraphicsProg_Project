#pragma once
#include <SimpleMath.h>
using Vec2 = DirectX::SimpleMath::Vector2;
class Ball
{
public:
	Ball(const Vec2& _pos, const Vec2& _vel);
	void Update(float dt);
	Vec2 GetPosition();
	int DoWallCollision(const RECT& walls);
	void ReboundX();
	void ReboundY();
	RECT GetRect();
	Vec2 GetVel() const;
private:
	static constexpr float radius = 10.0f;
	Vec2 pos;
	Vec2 vel;

};
