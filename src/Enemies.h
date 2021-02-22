#pragma once
#include "Player.h"
class Enemy :public DynamicCreature
{
};

class Goomba : public Enemy {
private:

	olc::vf2d spriteScale;
	int m_SState;

public:
	Goomba(olc::vf2d pos, olc::vf2d );
	~Goomba();

	void DrawSelf() override;
	void Update() override;
	bool ResolveStaticCollision(ColType type, LevelMap::Tile& tile) override;
	void CollisionCallBack(Local l) override;
	void Move(MovDirection mov) override;
	void Die() override;
};

