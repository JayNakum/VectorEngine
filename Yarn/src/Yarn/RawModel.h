#pragma once
class RawModel
{
public:
	RawModel(unsigned int vaoID, unsigned int vertexCount)
		: _vaoID(vaoID), _vertexCount(vertexCount) {}

	inline unsigned int getVaoID() { return _vaoID; }
	inline unsigned int getVertexCount() { return _vertexCount; }

private:
	unsigned int _vaoID;
	unsigned int _vertexCount;
};

