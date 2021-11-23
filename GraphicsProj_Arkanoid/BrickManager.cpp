#include "pch.h"
#include "BrickManager.h"
#include "BrickTile.h"

#include <iostream>
void BrickManager::CreateBricks(int width, int height)
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
			defaultBrickSize.right += y * spawnOffset;

			defaultBrickSize.top = x * spawnOffset;
			defaultBrickSize.bottom += x * spawnOffset;

			BrickTile brick = BrickTile(defaultBrickSize, DirectX::Colors::Red);
			brickList.push_back(brick);
		}

	}
}

void BrickManager::UpdateBrickState(std::list<BrickTile>& brickList, Ball& ball, const GeometryBatch& batch)
{
	for (std::list<BrickTile>::iterator brickElem = brickList.begin(); brickElem != brickList.end(); ++brickElem) {
		if (!brickElem->isDestroyed)
		{
			batch->DrawQuad(brickElem->v1, brickElem->v2, brickElem->v3, brickElem->v4);

		}
		if (brickElem->DoBallCollision(ball))
		{

		}
	}
	
}



