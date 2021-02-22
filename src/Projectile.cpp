#include "GameProps.h"
#include "Projectile.h"

using namespace GameProps;

Projectile::Projectile(olc::vf2d wPos, olc::vf2d vel, float siz) {
	WorldPos = wPos;
	Velocity = vel;
	Radius = siz;
}

void Projectile::DrawSelf() {
	Game->FillCircle(
		(-CameraPos.x + WorldPos.x) * TileSize + Resolution.x / 2.f,
		(-CameraPos.y + WorldPos.y) * TileSize + Resolution.y / 2.f, Radius, olc::RED);
}

void Projectile::Update() {

	WorldPos += Velocity * deltaTime;
}

bool Projectile::ComputeStaticCollision() {
	olc::vf2d futurePos = WorldPos + Velocity * deltaTime;

	if ((GameProps::Level->GetTile(futurePos.x, futurePos.y).flags & 0x80) == 0x80 ||
		futurePos.x <  0 - (Resolution.x / TileSize) ||
		futurePos.y <  0 - (Resolution.y / TileSize) ||
		futurePos.x > Level->GetWidth() + (Resolution.x / TileSize) ||
		futurePos.y > Level->GetHeight() +(Resolution.y / TileSize))
	{
		return true;
	}
	return false;
}