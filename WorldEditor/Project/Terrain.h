#pragma once
#include "DynamicPlane.h"
#include "Texture.h"
#include "Math.h"
#include <map>

struct HeightMap
{
	Texture* texture;

	int width, height;
	struct Data
	{
		float x, y, z;
	};

	std::map<Vector2, float> data;

	HeightMap(const std::string& texture);

	~HeightMap() { delete texture; }
};

class Terrain : public Drawable
{
private:
	DynamicPlane* plane;

	Texture* blendMap;
	Texture* pathMap;
	Texture* textures[4];
	HeightMap* heightMap;
public:
	Terrain(UINT subdivisions = 0);
	~Terrain();

	float SampleAverage(float x, float z);

	HeightMap* GetHeightMap() { return heightMap; }
	void Draw() const;
};