#include "GameProps.h"

using namespace GameProps;

DynamicsCollection::DynamicsCollection() {
	dynamicsVector = std::vector<Dynamic*>();
}

DynamicsCollection::~DynamicsCollection() {
	for (int i = 0; i < dynamicsVector.size(); i++)
	{
		delete dynamicsVector[i];
	}
}

bool DynamicsCollection::ResolveDynamicCollision() {

	// for each dynamic that is different from the one I am comparing check if it is colliding
	for (int i = 0; i < dynamicsVector.size(); i++)
	{
		if (dynamicsVector[i] != m_Player)
		{
			// Top Collision
			if (	m_Player->futurePos.y							<= dynamicsVector[i]->WorldPos.y + dynamicsVector[i]->Size.y &&
					m_Player->futurePos.x + 0.1						<= dynamicsVector[i]->WorldPos.x + dynamicsVector[i]->Size.x &&
					m_Player->futurePos.x + m_Player->Size.x - 0.1	>= dynamicsVector[i]->WorldPos.x && 
					m_Player->futurePos.y + m_Player->Size.y	- 0.5	>= dynamicsVector[i]->WorldPos.y )
			{
				dynamicsVector[i]->CollisionCallBack(Dynamic::Local::TOP);
				return true;
			}
			// Bot Collision
			if (m_Player->futurePos.y + 0.5						<= dynamicsVector[i]->WorldPos.y + dynamicsVector[i]->Size.y &&
				m_Player->futurePos.x + 0.1						<= dynamicsVector[i]->WorldPos.x + dynamicsVector[i]->Size.x &&
				m_Player->futurePos.x + m_Player->Size.x - 0.1	>= dynamicsVector[i]->WorldPos.x &&
				m_Player->futurePos.y + m_Player->Size.y			>= dynamicsVector[i]->WorldPos.y)
			{
				dynamicsVector[i]->CollisionCallBack(Dynamic::Local::BOT);
				return true;
			}
			// Left Collision
			if (m_Player->futurePos.y + 0.5						<= dynamicsVector[i]->WorldPos.y + dynamicsVector[i]->Size.y &&
				m_Player->futurePos.x							<= dynamicsVector[i]->WorldPos.x + dynamicsVector[i]->Size.x &&
				m_Player->futurePos.x + m_Player->Size.x - 0.3	>= dynamicsVector[i]->WorldPos.x &&
				m_Player->futurePos.y + m_Player->Size.y	* 0.8	>= dynamicsVector[i]->WorldPos.y)
			{
				dynamicsVector[i]->CollisionCallBack(Dynamic::Local::LEFT);
				return true;
			}
//			// Right Collision
			if (m_Player->futurePos.y + 0.5						<= dynamicsVector[i]->WorldPos.y + dynamicsVector[i]->Size.y &&
				m_Player->futurePos.x + 0.3						<= dynamicsVector[i]->WorldPos.x + dynamicsVector[i]->Size.x &&
				m_Player->futurePos.x + m_Player->Size.x		>= dynamicsVector[i]->WorldPos.x &&
				m_Player->futurePos.y + m_Player->Size.y * 0.8	>= dynamicsVector[i]->WorldPos.y)
			{
				dynamicsVector[i]->CollisionCallBack(Dynamic::Local::RIGHT);
				return true;
			}
		}
	}
}