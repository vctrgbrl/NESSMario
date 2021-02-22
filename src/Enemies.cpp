#include "GameProps.h"

using namespace GameProps;

Goomba::Goomba(olc::vf2d pos, olc::vf2d vel) {
	WorldPos = pos;
	Size = olc::vf2d({ 1.f , 1.f });
	Velocity = vel;
	isWalking = false;
	isOnFloor = true;
	Acceleration =  0.f;
	JumpMultiplier = 4.f;
    m_SState = 0;
	m_Sprite = new olc::Sprite("./sprites/enemies-tiles.png");
	m_Decal = new olc::Decal(m_Sprite);
    spriteScale = olc::vf2d({ 1.f,1.f });
    futurePos = olc::vf2d({ 0,0 });
}

Goomba::~Goomba() {
	delete m_Sprite;
	delete m_Decal;
}

void Goomba::DrawSelf() {
    spriteTimer += deltaTime;
    float interval = 0.12f;
    olc::vf2d sourcePos = { 0,0 };
    olc::vf2d sourceSize = { 16,16 };
    float cicleTime = 0.12f * 4.f;

    switch (m_SState)
    {
    case 0:
        if (spriteTimer >= interval)
        {
            spriteScale.x *= -1;
            spriteTimer = 0;
        }
        sourcePos.x = 0;
        break;
    case 1:
        sourcePos.x = 16 * 1;
        break;
    default:
        break;
    }
    olc::vf2d pos({ (WorldPos.x - CameraPos.x) * TileSize + Resolution.x / 2 - (spriteScale.x - 1) * 8.f,
        (WorldPos.y - CameraPos.y) * TileSize + Resolution.y / 2 });

    GameProps::Game->DrawPartialDecal(pos, m_Decal, sourcePos, sourceSize, spriteScale);
}

void Goomba::Update() {
    float v = Velocity.x;
    futurePos = WorldPos + Velocity * deltaTime;
    ComputeStaticCollision();
    WorldPos = futurePos;
}

bool Goomba::ResolveStaticCollision(ColType type, LevelMap::Tile& tile) {
    bool hasCollided = false;
    switch (type)
    {
    case ColType::TOP:
        if (tile.spriteID != '.') {
            if ((tile.flags & 0x80) == 0x80) {
                this->futurePos.y = (int)this->futurePos.y + 1;
                this->isOnFloor = false;
                this->Velocity.y = 0;
                hasCollided = true;
            }
        }
        break;
    case ColType::BOT:
        if (tile.spriteID != '.') {
            if ((tile.flags & 0x80) == 0x80) {
                std::cout << this->JumpMultiplier << "\n";
                this->futurePos.y = (int)this->futurePos.y;
                this->isOnFloor = true;
                this->Velocity.y = 0;
                hasCollided = true;
            }
            if ((tile.flags & 0x40) == 0x40) {
                this->Die();
            }
        }
        break;
    case ColType::RIGHT:
        if (tile.spriteID != '.') {
            if ((tile.flags & 0x80) == 0x80) {
                this->futurePos.x = (int)this->futurePos.x;
                this->Velocity.x *= -1;
                hasCollided = true;
            }
        }
        break;
    case ColType::LEFT:
        if (tile.spriteID != '.') {
            if ((tile.flags & 0x80) == 0x80) {
                this->futurePos.x = (int)this->futurePos.x + 1;
                this->Velocity.x *= -1;
                hasCollided = true;
            }
        }
        break;
    default:
        break;
    }
    return hasCollided;
}

void Goomba::Move(MovDirection mov) {
}

void Goomba::CollisionCallBack(Local l) {
	switch (l)
	{
	case Dynamic::TOP:
		break;
	case Dynamic::RIGHT:
		m_Player->Velocity.x = 0;
        m_Player->Die();
		break;
	case Dynamic::BOT:
		m_Player->futurePos.y = (int)m_Player->futurePos.y;
		m_Player->isOnFloor = true;
		m_Player->Velocity.y = 0;
        this->Die();
		break;
	case Dynamic::LEFT:
		m_Player->Velocity.x = 0;
        m_Player->Die();
		break;
	default:
		break;
	}
}

void Goomba::Die() {
    Velocity.x = 0;
    m_SState = 1;
    
    std::vector<Dynamic*>::iterator it = GameProps::dynCol->dynamicsVector.begin();
    for(; it < GameProps::dynCol->dynamicsVector.end(); it++)
    {
        if ((*it)==this)
        {
            GameProps::dynCol->dynamicsVector.erase(it);
            break;
        }
    }
    
}
