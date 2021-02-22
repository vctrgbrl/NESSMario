#pragma once
#include "olcPixelGameEngine.h"
#include "LevelMap.h"

/// <summary>
/// Everthing that moves (Projectiles, NPCs, Player, Enemies...)
/// </summary>
class Dynamic {
protected:
    float spriteTimer;
    olc::Sprite* m_Sprite = nullptr;
    olc::Decal* m_Decal = nullptr;
public:
    enum Local
    {
        TOP = 1, RIGHT, BOT, LEFT
    };
public:
    olc::vf2d WorldPos;
    olc::vf2d Velocity;
    olc::vi2d Size;

public:

    virtual void DrawSelf() = 0;
    virtual void Update() = 0;
    virtual bool ComputeStaticCollision() = 0;
    virtual void CollisionCallBack(Local l) {};
};

/// <summary>
/// Creatures, enemies, player, npcs, have hp, acceleration
/// </summary>
class DynamicCreature : public Dynamic {
protected:
    float Acceleration;
    float JumpMultiplier;
    enum class ColType {
        TOP, BOT, LEFT, RIGHT
    };
public:
    olc::vf2d futurePos;
    enum class MovDirection {
        JUMP, RIGHT, LEFT, FLOAT
    };
    bool isWalking;
    bool isOnFloor;

    virtual void Move(MovDirection mov) {};
    virtual void Die() {};
    virtual bool ResolveStaticCollision(ColType type, LevelMap::Tile& tile);
    virtual bool ComputeStaticCollision();
};

class MisteryBlock : public Dynamic {
public:
    enum class Gift {
        MUSHROOM, FLOWER, LIFE
    };
private:
    olc::vf2d initialWorldPos;
public:
    MisteryBlock(olc::vf2d position);
    ~MisteryBlock();

    void DrawSelf() override;
    void Update() override;
    bool ComputeStaticCollision() override;
    void CollisionCallBack(Local l) override;
};

class BrickBlock : public Dynamic {
private:
    olc::vf2d initialWorldPos;
public:
    BrickBlock(olc::vf2d position);
    ~BrickBlock();

    void DrawSelf() override;
    void Update() override;
    bool ComputeStaticCollision() override;
    void CollisionCallBack(Local l) override;
};