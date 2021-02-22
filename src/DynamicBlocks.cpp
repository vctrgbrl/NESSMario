#include "GameProps.h"

using namespace GameProps;
// Mistery Block
MisteryBlock::MisteryBlock(olc::vf2d position) {

	WorldPos = position;
	initialWorldPos = position;
	Velocity = olc::vf2d({ 0.f, 0.f });
	Size = olc::vf2d({ 1.f, 1.f });
	m_Sprite = new olc::Sprite("./sprites/level1-tiles.png");
	m_Decal = new olc::Decal(m_Sprite);
}

MisteryBlock::~MisteryBlock() {
	delete m_Sprite;
}

void MisteryBlock::DrawSelf() {
	GameProps::Game->DrawPartialDecal(
		olc::vf2d({ (-GameProps::CameraPos.x + WorldPos.x) * GameProps::TileSize + GameProps::Resolution.x / 2.f,
		(-GameProps::CameraPos.y + WorldPos.y) * GameProps::TileSize + GameProps::Resolution.y / 2.f }), m_Decal, olc::vf2d({ 0,16 }), Size * 16);
};

void MisteryBlock::Update() {
	
	WorldPos += Velocity * deltaTime;
	Velocity.y += 44.f * deltaTime;
	if (WorldPos.y >= initialWorldPos.y)
	{
		WorldPos = initialWorldPos;
		Velocity.y = 0;
	}
};

bool MisteryBlock::ComputeStaticCollision() {
	return true;
};
void MisteryBlock::CollisionCallBack(Local l) {
	switch (l)
	{
	case Dynamic::TOP:
		m_Player->futurePos.y = (int)m_Player->futurePos.y + 1;
		m_Player->isOnFloor = false;
		m_Player->Velocity.y = 0;
		Velocity.y -= 7.f;
		std::cout << "misterybox\n";
		break;
	case Dynamic::RIGHT:
		m_Player->futurePos.x = (int)m_Player->futurePos.x;
		m_Player->Velocity.x = 0;
		break;
	case Dynamic::BOT:
		m_Player->futurePos.y = (int)m_Player->futurePos.y;
		m_Player->isOnFloor = true;
		m_Player->Velocity.y = 0;
		break;
	case Dynamic::LEFT:
		m_Player->futurePos.x = (int)m_Player->futurePos.x + 1;
		m_Player->Velocity.x = 0;
		break;
	default:
		break;
	}
};


// Brick Block

BrickBlock::BrickBlock(olc::vf2d position) {

	WorldPos = position;
	initialWorldPos = position;
	Velocity = olc::vf2d({ 0.f, 0.f });
	Size = olc::vf2d({ 1.f, 1.f });
	m_Sprite = new olc::Sprite("./sprites/level1-tiles.png");
	m_Decal = new olc::Decal(m_Sprite);
}

BrickBlock::~BrickBlock() {
	delete m_Sprite;
}

void BrickBlock::DrawSelf() {
	GameProps::Game->DrawPartialDecal(
		olc::vf2d({ (-GameProps::CameraPos.x + WorldPos.x) * GameProps::TileSize + GameProps::Resolution.x / 2.f,
		(-GameProps::CameraPos.y + WorldPos.y) * GameProps::TileSize + GameProps::Resolution.y / 2.f }), m_Decal, olc::vf2d({ 16*3, 0 }), Size * 16);
};

void BrickBlock::Update() {

	WorldPos += Velocity * deltaTime;
	Velocity.y += 44.f * deltaTime;
	if (WorldPos.y >= initialWorldPos.y)
	{
		WorldPos = initialWorldPos;
		Velocity.y = 0;
	}
};

bool BrickBlock::ComputeStaticCollision() {
	return true;
};
void BrickBlock::CollisionCallBack(Local l) {
	switch (l)
	{
	case Dynamic::TOP:
		m_Player->futurePos.y = (int)m_Player->futurePos.y + 1;
		m_Player->isOnFloor = false;
		m_Player->Velocity.y = 0;
		Velocity.y -= 7.f;
		break;
	case Dynamic::RIGHT:
		m_Player->futurePos.x = (int)m_Player->futurePos.x;
		m_Player->Velocity.x = 0;
		break;
	case Dynamic::BOT:
		m_Player->futurePos.y = (int)m_Player->futurePos.y;
		m_Player->isOnFloor = true;
		m_Player->Velocity.y = 0;
		break;
	case Dynamic::LEFT:
		m_Player->futurePos.x = (int)m_Player->futurePos.x + 1;
		m_Player->Velocity.x = 0;
		break;
	default:
		break;
	}
};