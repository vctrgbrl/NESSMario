#include "GameProps.h"

olc::PixelGameEngine* GameProps::Game = nullptr;
olc::vf2d GameProps::CameraPos = { 0,0 };
olc::vi2d GameProps::Resolution = { 0,0 };
int GameProps::TileSize = 0;
olc::vf2d GameProps::nVisibleTiles = { 0,0 };
LevelMap* GameProps::Level = nullptr;
float GameProps::deltaTime = 0.f;
olc::vf2d GameProps::MousePos = { 0,0 };
Player* GameProps::m_Player = nullptr;
DynamicsCollection* GameProps::dynCol = nullptr;