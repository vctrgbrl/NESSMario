#include "GameProps.h"

using namespace GameProps;

bool DynamicCreature::ResolveStaticCollision(ColType type, LevelMap::Tile& tile) {
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
                this->Velocity.x = 0;
                hasCollided = true;
            }
        }
        break;
    case ColType::LEFT:
        if (tile.spriteID != '.') {
            if ((tile.flags & 0x80) == 0x80) {
                this->futurePos.x = (int)this->futurePos.x + 1;
                this->Velocity.x = 0;
                hasCollided = true;
            }
        }
        break;
    default:
        break;
    }
    return hasCollided;
}

bool DynamicCreature::ComputeStaticCollision() {

    isOnFloor = false;
    bool hasCollided = false;
    if (this->Velocity.x < 0)
    {
        LevelMap::Tile tileA = Level->GetTile(this->futurePos.x + 0, this->WorldPos.y + this->Size.y * 0.00f);
        LevelMap::Tile tileB = Level->GetTile(this->futurePos.x + 0, this->WorldPos.y + this->Size.y * 0.95f);


        if (!this->ResolveStaticCollision(ColType::LEFT, tileA)) {
            hasCollided = this->ResolveStaticCollision(ColType::LEFT, tileB);
        }
        else { hasCollided = true; }
    }
    else if (this->Velocity.x > 0)
    {
        LevelMap::Tile tileA = Level->GetTile(this->futurePos.x + 1, this->WorldPos.y + this->Size.y * 0.00f);
        LevelMap::Tile tileB = Level->GetTile(this->futurePos.x + 1, this->WorldPos.y + this->Size.y * 0.95f);


        if (!this->ResolveStaticCollision(ColType::RIGHT, tileA)) {
            hasCollided = this->ResolveStaticCollision(ColType::RIGHT, tileB);
        }
        else { hasCollided = true; }
    }
    if (this->Velocity.y <= 0)
    {
        LevelMap::Tile tileA = Level->GetTile(this->futurePos.x + 0.01, this->futurePos.y);
        LevelMap::Tile tileB = Level->GetTile(this->futurePos.x + 0.99, this->futurePos.y);

        if (!this->ResolveStaticCollision(ColType::TOP, tileA)) {
            hasCollided = this->ResolveStaticCollision(ColType::TOP, tileB);
        }
        else { hasCollided = true; }
    }
    else
    {
        LevelMap::Tile tileA = Level->GetTile(this->futurePos.x + 0.1, this->futurePos.y + this->Size.y);
        LevelMap::Tile tileB = Level->GetTile(this->futurePos.x + 0.9, this->futurePos.y + this->Size.y);
        std::cout << this->WorldPos.y << "\n";
        if (!this->ResolveStaticCollision(ColType::BOT, tileA)) {
            hasCollided = this->ResolveStaticCollision(ColType::BOT, tileB);
        }
        else {
            hasCollided = true;
        }
    }
    return hasCollided;
}

Player::Player(olc::vf2d worldPos, float health, float acc, float jmpMultiplier, float flMultiplier) {
    Acceleration = acc;
    WorldPos = worldPos;
    JumpMultiplier = jmpMultiplier;
    FloatMultiplier = flMultiplier;
    isWalking = false;
    isOnFloor = true;
    ProjectileSize = 2.f;
    ProjectileSpeed = 20.f;
    spriteTimer = 0.f;
    m_Sprite = new olc::Sprite("./sprites/mario-sprites.png");
    m_Decal = new olc::Decal(m_Sprite);
    m_PState = PlayerState::SMALL;
    m_SState = SpriteState::IDLE;
    spriteScale = { 1.f,1.f };
    Size = olc::vf2d({ 1.f, 1.f });
    AllowInput = true;
    computeCollision = true;
    futurePos = {0.f,0.f};
}

Player::~Player() {
    delete m_Sprite;
    delete m_Decal;
}

void Player::DrawSelf() {
    
    spriteTimer += deltaTime;
    float interval = 0.12f;
    olc::vf2d sourcePos = { 0,0 };
    olc::vf2d sourceSize = { 16,16 };
    float cicleTime = 0.12f * 4.f;

    switch (m_PState)
    {
    case Player::SMALL:
        sourcePos.y = 0;
        break;
    case Player::BIG:
        sourceSize.y = 32;
        sourcePos.y = 16;
        break;
    case Player::SMALL_FIRE:
        sourcePos.y = 16 * 3;
        break;
    case Player::BIG_FIRE:
        sourcePos.y = 16 * 4;
        break;
    default:
        break;
    }

    if (spriteTimer >= cicleTime) { spriteTimer = 0; }

    switch (m_SState)
    {
    case Player::IDLE:
        sourcePos.x = 0;
        break;
    case Player::RUN:
        if (spriteTimer < interval)
            sourcePos.x = 16 * 2;
        else if (spriteTimer < interval * 2)
            sourcePos.x = 16 * 3;
        else if (spriteTimer < interval * 3)
            sourcePos.x = 16 * 4;
        else if (spriteTimer < interval * 4)
            sourcePos.x = 16 * 3;
        break;
    case Player::JUMP:
        sourcePos.x = 16 * 6;
        break;
    case Player::DEAD:
        sourcePos.x = 16 * 1;
        break;
    default:
        break;
    }
    olc::vf2d pos({ (WorldPos.x - CameraPos.x) * TileSize + Resolution.x / 2 - (spriteScale.x - 1) * 8.f,
        (WorldPos.y - CameraPos.y) * TileSize + Resolution.y / 2 });

    GameProps::Game->DrawPartialDecal(pos, m_Decal, sourcePos, sourceSize, spriteScale);
}

void Player::Update() {

    futurePos = WorldPos + Velocity * deltaTime;
    if (computeCollision)
        ComputeStaticCollision();
        GameProps::dynCol->ResolveDynamicCollision();

    // See if in the future position has some dynamic
    WorldPos = futurePos;

    Velocity.y += 44.f * deltaTime;

    Velocity.x = (Velocity.x >= +8) ? +8 : Velocity.x;
    Velocity.x = (Velocity.x <= -8) ? -8 : Velocity.x;
    Velocity.y = (Velocity.y >= +40) ? +40 : Velocity.y;

    if (!isWalking && isOnFloor && m_SState != SpriteState::DEAD)
    {
        m_SState = SpriteState::IDLE;
        Velocity.x += -6.f * Velocity.x* deltaTime;
        if(abs(Velocity.x) <= 1) 
            Velocity.x = 0;
    }
}

void Player::Move(MovDirection mov) {
    switch (mov)
    {
    case DynamicCreature::MovDirection::JUMP:
        if (isOnFloor)
        {
            FloatMultiplier = 30.f;
            Velocity.y = -1 * JumpMultiplier;
            isOnFloor = false;
            m_SState = SpriteState::JUMP;
        }
        break;
    case DynamicCreature::MovDirection::FLOAT:
        if (!isOnFloor)
        {
            FloatMultiplier -= deltaTime * 20;
            if (FloatMultiplier <= 0)
            {
                FloatMultiplier = 0;
            }
            Velocity.y += -1 * FloatMultiplier * deltaTime;
        }
        break;
    case DynamicCreature::MovDirection::RIGHT:
        if (isOnFloor)
        {
            spriteScale.x = 1.f;
            Velocity.x += +1 * Acceleration * deltaTime; isWalking = true;
            m_SState = SpriteState::RUN;
            break;
        }
        Velocity.x += +1 * Acceleration * deltaTime / 4.f; isWalking = true;
        break;
    case DynamicCreature::MovDirection::LEFT:
        if (isOnFloor)
        {
            spriteScale.x = -1.f;
            Velocity.x += -1 * Acceleration * deltaTime; isWalking = true;
            m_SState = SpriteState::RUN;
            break;
        }
        Velocity.x += -1 * Acceleration * deltaTime / 4.f; isWalking = true;
        break;
    default:
        break;
    }
}

void Player::Die() {
    m_SState = SpriteState::DEAD;
    AllowInput = false;
    computeCollision = false;
    Velocity.x = 0;
    Velocity.y -= 20.f;
}

void Player::Shot() {
    float angle = atan2(
        MousePos.y * GameProps::TileSize - ((-CameraPos.y + WorldPos.y) * TileSize + Resolution.y / 2.f),
        MousePos.x * GameProps::TileSize - ((-CameraPos.x + WorldPos.x) * TileSize + Resolution.x / 2.f)
    );

    ListProjectiles.push_back(Projectile({
        { WorldPos.x + 0.5f, WorldPos.y + 0.5f },
        { cos(angle) * ProjectileSpeed, sin(angle) * ProjectileSpeed}, ProjectileSize
        }));
}

void Player::DrawProjectiles() {
    std::list<Projectile>::iterator it = ListProjectiles.begin();
    while (it != ListProjectiles.end())
    {
        if ((*it).ComputeStaticCollision()) {
            ListProjectiles.erase(it++);
            continue;
        }
        (*it).Update();
        (*it).DrawSelf();
        it++;
    }
}