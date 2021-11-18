#include "pch.h"
#include "BrickManager.h"
#include "BrickTile.h"

void BrickManager::DrawBrick(int width, int height, const GeometryBatch& batch)
{
	RECT rectBrick;
	rectBrick.left = 0.0f;
	rectBrick.top = 0.0f;
	rectBrick.right = 100.0f;
	rectBrick.bottom = 100.0f;

	BrickTile Brick = BrickTile(rectBrick, DirectX::Colors::Red);

	batch->DrawQuad(Brick.v1, Brick.v2, Brick.v3, Brick.v4);
}
