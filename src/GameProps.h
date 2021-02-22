#pragma once
#include "DynamicsCollection.h"

namespace GameProps {
	extern olc::PixelGameEngine* Game;
	extern olc::vf2d CameraPos;
	extern olc::vi2d Resolution;
	extern int TileSize;
	extern olc::vf2d nVisibleTiles;
	extern LevelMap* Level;
	extern float deltaTime;
	extern olc::vf2d MousePos;
	extern Player* m_Player;
	extern DynamicsCollection* dynCol;
}