#pragma once
#include "Ball.h"
#include <list>
#include <BrickTile.h>
using GeometryBatch = std::unique_ptr<DirectX::PrimitiveBatch< DirectX::VertexPositionColor>>;
class BrickManager
{

public:
	void CreateBricks(int nBricksAcross, int nBricksDown, int brickWidth, int brickHeigth);
	void UpdateBrickState(std::vector<BrickTile>& brickList, Ball& ball, const GeometryBatch& batch);
	std::vector<BrickTile> brickList;
};

