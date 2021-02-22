#pragma once

class LevelMap
{
public:
	struct Tile
	{
		char spriteID;
		unsigned char flags;
	};
private:
	int m_Width;
	int m_Height;
	Tile* TileArray = nullptr;
	olc::Sprite* tilesSprites = nullptr;
public:

	LevelMap(int width, int height, std::string SpriteIDArray, unsigned char* FlagArray);
	~LevelMap();

	void DrawSelf();
	Tile GetTile(float x, float y);
	int GetWidth();
	int GetHeight();
};