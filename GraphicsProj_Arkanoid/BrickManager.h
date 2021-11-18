#pragma once

using GeometryBatch = std::unique_ptr<DirectX::PrimitiveBatch< DirectX::VertexPositionColor>>;
class BrickManager
{
public:
	void DrawBricks(int width, int height, const GeometryBatch& batch);
};

