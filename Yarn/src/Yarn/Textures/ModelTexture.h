#pragma once
class ModelTexture
{
public:
	ModelTexture(unsigned int id);
	inline unsigned int getID() const { return _textureID; }
private:
	unsigned int _textureID;
};
