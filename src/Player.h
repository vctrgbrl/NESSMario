#pragma once
#include "Projectile.h"

class Player : public DynamicCreature
{
public:
    float ProjectileSpeed;
    float ProjectileSize;
    bool AllowInput;

private:
    enum PlayerState {
        SMALL, BIG, SMALL_FIRE, BIG_FIRE 
    };
    enum SpriteState {
        IDLE, RUN, JUMP, DEAD
    };
    std::list<Projectile> ListProjectiles;
    PlayerState m_PState;
    SpriteState m_SState;
    olc::vf2d spriteScale;
    float FloatMultiplier;
    bool computeCollision;

public:
    Player(olc::vf2d worldPos, float health, float acceleration, float jumpMultiplier, float floatMultiplier);
    ~Player();
    void DrawSelf() override;
    void Update() override;
    void Move(MovDirection mov) override;
    void Die() override;
    void Shot();
    void DrawProjectiles();
};