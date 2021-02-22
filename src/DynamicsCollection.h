#pragma once
#include "Enemies.h"

class DynamicsCollection {
public:
	std::vector<Dynamic*> dynamicsVector;
public:
	DynamicsCollection();
	~DynamicsCollection();

	bool ResolveDynamicCollision();
};
