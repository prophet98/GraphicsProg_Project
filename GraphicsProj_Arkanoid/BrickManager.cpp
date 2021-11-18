#include "pch.h"
#include "BrickManager.h"
#include "BrickTile.h"

void BrickManager::DrawBricks(int width, int height, const GeometryBatch& batch)
{

	float spawnOffset = 105.0f;

	for (unsigned int x = 0; x < height; x++)
	{
		for (unsigned int y = 0; y < width; y++)
		{
			RECT defaultBrickSize;
			defaultBrickSize.left = 0.0f;
			defaultBrickSize.top = 0.0f;
			defaultBrickSize.right = 100.0f;
			defaultBrickSize.bottom = 100.0f;

			defaultBrickSize.left = y * spawnOffset;
			defaultBrickSize.right += y *  spawnOffset;

			defaultBrickSize.top = x * spawnOffset;
			defaultBrickSize.bottom += x * spawnOffset;

			BrickTile Brick = BrickTile(defaultBrickSize, DirectX::Colors::Red);
			batch->DrawQuad(Brick.v1, Brick.v2, Brick.v3, Brick.v4);
		}

	}


	
}
