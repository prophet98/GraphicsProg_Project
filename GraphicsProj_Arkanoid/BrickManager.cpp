#include "pch.h"
#include "BrickManager.h"
#include "BrickTile.h"

#include <iostream>
void BrickManager::CreateBricks(int nBricksAcross, int nBricksDown, int brickWidth, int brickHeigth)
{
	float spawnOffset;

	for (unsigned int y = 1; y < nBricksDown + 1; y++)
	{
		for (unsigned int x = 1; x < nBricksAcross + 1; x++)
		{
			RECT defaultBrickSize;

			defaultBrickSize.left = 0.0f;
			defaultBrickSize.top = 0.0f;
			defaultBrickSize.right = brickWidth;
			defaultBrickSize.bottom = brickHeigth;
			spawnOffset = defaultBrickSize.right - defaultBrickSize.left + 5;

			defaultBrickSize.left = x * spawnOffset;
			defaultBrickSize.right += x * spawnOffset;

			defaultBrickSize.top = y * spawnOffset;
			defaultBrickSize.bottom += y * spawnOffset;
			if (y%2 == 0)
			{
				BrickTile brick = BrickTile(defaultBrickSize, DirectX::Colors::Orange);
				brickList.push_back(brick);

			}
			else
			{
				BrickTile brick = BrickTile(defaultBrickSize, DirectX::Colors::OrangeRed);
				brickList.push_back(brick);

			}
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



