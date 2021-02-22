#pragma once
#include "Dynamics.h"

class Projectile : public Dynamic
{
private:
	float Radius;
public:
	Projectile(olc::vf2d worldPos, olc::vf2d velocity, float radius);

public:
	void DrawSelf() override;
	void Update() override;
	bool ComputeStaticCollision() override;
};
