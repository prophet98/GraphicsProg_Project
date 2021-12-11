#include "pch.h"
#include "BrickManager.h"
#include "BrickTile.h"

#include <iostream>
void BrickManager::CreateBricks(int nBricksAcross, int nBricksDown, int brickWidth, int brickHeigth)
{
	float spawnOffset = 0.0f;

	for (unsigned int y = 1; y < nBricksDown + 1; y++)
	{
		for (unsigned int x = 1; x < nBricksAcross + 1; x++)
		{
			RECT defaultBrickSize;

			defaultBrickSize.left = 0.0f;
			defaultBrickSize.top = 0.0f;
			defaultBrickSize.right = brickWidth;
			defaultBrickSize.bottom = brickHeigth;

			spawnOffset = defaultBrickSize.right + brickDistance ;

			defaultBrickSize.left = x * spawnOffset + centeredPos;
			defaultBrickSize.right += x * spawnOffset + centeredPos;

			defaultBrickSize.top = y * spawnOffset + centeredPos;
			defaultBrickSize.bottom += y * spawnOffset + centeredPos;

			if (y % 2 == 0)
			{
				BrickTile brick = BrickTile(defaultBrickSize, DirectX::Colors::Orange);
				brickList.push_back(brick);
				brick.isDestroyed = false;
			}
			else
			{
				BrickTile brick = BrickTile(defaultBrickSize, DirectX::Colors::OrangeRed);
				brickList.push_back(brick);
				brick.isDestroyed = false;
			}

			
		}

	}
}

void BrickManager::UpdateBrickState(std::vector<BrickTile>& brickList, Ball& ball, const GeometryBatch& batch)
{
	int brickIndex = 0;
	bool hasCollided = false;
	float currentCollDist = 0;
	int curColIndex = 0;
	for (std::vector<BrickTile>::iterator brickElem = brickList.begin(); brickElem != brickList.end(); ++brickElem) {
		
		if (!brickElem->isDestroyed)
		{
			batch->DrawQuad(brickElem->v1, brickElem->v2, brickElem->v3, brickElem->v4);
		}
		if (brickElem->CheckBallCollision(ball))
		{
			const float newCollDistSquared = (ball.GetPosition() - brickElem->GetCenter()).LengthSquared();
			if (hasCollided)
			{
				if (newCollDistSquared < currentCollDist)
				{
					currentCollDist = newCollDistSquared;
					curColIndex = brickIndex;
				}
			}
			else
			{
				currentCollDist = newCollDistSquared;
				curColIndex = brickIndex;
				hasCollided = true;
			}
			destroyedBricks++;
			if (brickSound && !brickSound->IsInUse())
			{
				brickSound->Play();
			}
		}
		
		brickIndex++;
	}
	if (hasCollided)
	{
		brickList[curColIndex].ExecuteBallCollision(ball);
	}
	if (destroyedBricks == brickList.size())
	{
		//handle restart
	}

}

void BrickManager::RemoveAllBricks()
{
	brickList.clear();
}



BrickManager::BrickManager(std::unique_ptr<DirectX::SoundEffect> in_sound)
{
	brickSound = std::move(in_sound);
}

BrickManager::BrickManager()
{

}

