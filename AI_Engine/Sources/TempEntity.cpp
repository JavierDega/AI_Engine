#include "pch.h"
#include "..\Headers\TempEntity.h"
#include "GameScene.h"

using namespace DirectX;
using namespace SimpleMath;

TempEntity::TempEntity( Vector2 screenPos, float layerDepth, float lifeTime )
	: GameEntity(screenPos, layerDepth), m_lifeTime(lifeTime), m_timeSinceSpawn(0)
{
}


TempEntity::~TempEntity()
{
}

void TempEntity::Update(float elapsedTime)
{
	m_timeSinceSpawn += elapsedTime;
	if (m_timeSinceSpawn >= m_lifeTime) {
		//@Alt+Delete yourself
		m_isDeleted = true;
	}
}
