#pragma once
class ModelTexture
{
public:
	ModelTexture(unsigned int id);
	inline unsigned int getID() const { return _textureID; }

	inline float getShineDamper() { return _shineDamper; }
	void setShineDamper(float shineDamper);
	inline float getReflectivity() { return _reflectivity; }
	void setReflectivity(float reflectivity);

private:
	float _shineDamper = 1.0f;
	float _reflectivity = 0.0f;

	unsigned int _textureID;
};
