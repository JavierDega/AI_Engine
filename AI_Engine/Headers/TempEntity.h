#pragma once
#include "GameEntity.h"

class TempEntity :
	public GameEntity
{
public:
	TempEntity(DirectX::SimpleMath::Vector2 screenPos = DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2 speed = DirectX::SimpleMath::Vector2::Zero,
		float layerDepth = 0.6f, float lifeTime = 2.f);
	~TempEntity();
	//Update
	virtual void Update(float elapsedTime = 0.f)override;

	//Variables
	float m_timeSinceSpawn;
	float m_lifeTime;
	DirectX::SimpleMath::Vector2 m_speed;
};
