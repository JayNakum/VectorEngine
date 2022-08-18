#pragma once
class RawModel
{
public:
	RawModel(unsigned int vaoID, unsigned int vertexCount);

	inline unsigned int getVaoID() const { return _vaoID; }
	inline unsigned int getVertexCount() const { return _vertexCount; }

private:
	unsigned int _vaoID;
	unsigned int _vertexCount;
};

