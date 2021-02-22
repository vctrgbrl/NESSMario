#include "GameProps.h"

LevelMap::LevelMap(int w, int h, std::string SpriteIDArray, unsigned char* FlagArray) {
	m_Width = w;
	m_Height = h;

	tilesSprites = new olc::Sprite("./sprites/level1-tiles.png");

	TileArray = new Tile[m_Height * m_Width];

	for (int y = 0; y < m_Height; y++)
	{
		for (int x = 0; x < m_Width; x++)
		{
			TileArray[y * m_Width + x] = { SpriteIDArray[y * m_Width + x], FlagArray[y * m_Width + x]};
		}
	}
}

LevelMap::~LevelMap() {
	delete[] TileArray;
}

LevelMap::Tile LevelMap::GetTile(float x, float y) {
	if (x >= 0 && x < m_Width && y >= 0 && y < m_Height)
	{
		return TileArray[(int)y * m_Width + (int)x];
	}
	return { 0x00, 0x00 };
}

void LevelMap::DrawSelf() {
	for (int y = GameProps::CameraPos.y - GameProps::nVisibleTiles.y / 2; y < GameProps::CameraPos.y + GameProps::nVisibleTiles.y / 2; y++)
	{
		for (int x = GameProps::CameraPos.x - GameProps::nVisibleTiles.x / 2; x < GameProps::CameraPos.x + GameProps::nVisibleTiles.x / 2;x++)
		{
			switch (GetTile((float)x, (float)y).spriteID)
			{
			case '#':
				//GameProps::Game->FillRect((-GameProps::CameraPos.x + x) * GameProps::TileSize + GameProps::Resolution.x / 2.f,
				//	(-GameProps::CameraPos.y + y) * GameProps::TileSize + GameProps::Resolution.y / 2.f,
				//	GameProps::TileSize, GameProps::TileSize, olc::WHITE);
				
				GameProps::Game->DrawPartialSprite((-GameProps::CameraPos.x + x) * GameProps::TileSize + GameProps::Resolution.x / 2.f,
					(-GameProps::CameraPos.y + y) * GameProps::TileSize + GameProps::Resolution.y / 2.f, tilesSprites, 0, 0, GameProps::TileSize, GameProps::TileSize);
				break;
			case '?':
				break;
				GameProps::Game->DrawPartialSprite(
					(-GameProps::CameraPos.x + x) * GameProps::TileSize + GameProps::Resolution.x / 2.f,
					(-GameProps::CameraPos.y + y) * GameProps::TileSize + GameProps::Resolution.y / 2.f, 
					tilesSprites, 0, 16, GameProps::TileSize, GameProps::TileSize);
			case '[':
				GameProps::Game->DrawPartialSprite(
					(-GameProps::CameraPos.x + x) * GameProps::TileSize + GameProps::Resolution.x / 2.f,
					(-GameProps::CameraPos.y + y) * GameProps::TileSize + GameProps::Resolution.y / 2.f,
					tilesSprites, 16, 0, GameProps::TileSize, GameProps::TileSize);
				break;
			case ']':
				GameProps::Game->DrawPartialSprite(
					(-GameProps::CameraPos.x + x) * GameProps::TileSize + GameProps::Resolution.x / 2.f,
					(-GameProps::CameraPos.y + y) * GameProps::TileSize + GameProps::Resolution.y / 2.f,
					tilesSprites, 16 * 2, 0, GameProps::TileSize, GameProps::TileSize);
				break;
			case '{':
				GameProps::Game->DrawPartialSprite(
					(-GameProps::CameraPos.x + x) * GameProps::TileSize + GameProps::Resolution.x / 2.f,
					(-GameProps::CameraPos.y + y) * GameProps::TileSize + GameProps::Resolution.y / 2.f,
					tilesSprites, 16, 16, GameProps::TileSize, GameProps::TileSize);
				break;
			case '}':
				GameProps::Game->DrawPartialSprite(
					(-GameProps::CameraPos.x + x) * GameProps::TileSize + GameProps::Resolution.x / 2.f,
					(-GameProps::CameraPos.y + y) * GameProps::TileSize + GameProps::Resolution.y / 2.f,
					tilesSprites, 16*2, 16, GameProps::TileSize, GameProps::TileSize);
				break;
			case 'B':
				break;
				GameProps::Game->DrawPartialSprite(
					(-GameProps::CameraPos.x + x) * GameProps::TileSize + GameProps::Resolution.x / 2.f,
					(-GameProps::CameraPos.y + y) * GameProps::TileSize + GameProps::Resolution.y / 2.f,
					tilesSprites, 16*3, 0, GameProps::TileSize, GameProps::TileSize);
			case 'H':
				GameProps::Game->DrawPartialSprite(
					(-GameProps::CameraPos.x + x) * GameProps::TileSize + GameProps::Resolution.x / 2.f,
					(-GameProps::CameraPos.y + y) * GameProps::TileSize + GameProps::Resolution.y / 2.f,
					tilesSprites, 16*3, 16, GameProps::TileSize, GameProps::TileSize);
				break;
			case '|':
				GameProps::Game->DrawPartialSprite(
					(-GameProps::CameraPos.x + x) * GameProps::TileSize + GameProps::Resolution.x / 2.f,
					(-GameProps::CameraPos.y + y) * GameProps::TileSize + GameProps::Resolution.y / 2.f,
					tilesSprites, 16*4, 0, GameProps::TileSize, GameProps::TileSize);
				break;
			case 'o':
				GameProps::Game->DrawPartialSprite(
					(-GameProps::CameraPos.x + x) * GameProps::TileSize + GameProps::Resolution.x / 2.f,
					(-GameProps::CameraPos.y + y) * GameProps::TileSize + GameProps::Resolution.y / 2.f,
					tilesSprites, 16*4, 16, GameProps::TileSize, GameProps::TileSize);
				break;
			default:
				break;
			}
		}
	}
}

int LevelMap::GetWidth() { return m_Width; }
int LevelMap::GetHeight() { return m_Height; }