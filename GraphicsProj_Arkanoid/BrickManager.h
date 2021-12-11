#pragma once
#include "Ball.h"
#include <list>
#include <BrickTile.h>
using GeometryBatch = std::unique_ptr<DirectX::PrimitiveBatch< DirectX::VertexPositionColor>>;
class BrickManager
{
private:
	int brickDistance = 5;
	int centeredPos = 75;
	int destroyedBricks = 0;
public:
	void CreateBricks(int nBricksAcross, int nBricksDown, int brickWidth, int brickHeigth);
	void UpdateBrickState(std::vector<BrickTile>& brickList, Ball& ball, const GeometryBatch& batch);
	void RemoveAllBricks();
	std::vector<BrickTile> brickList;
	std::unique_ptr<DirectX::SoundEffect> brickSound;
	BrickManager(std::unique_ptr<DirectX::SoundEffect> in_sound );
	BrickManager();
};

