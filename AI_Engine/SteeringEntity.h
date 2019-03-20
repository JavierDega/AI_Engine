#pragma once
#include "GameEntity.h"
class SteeringEntity :
	public GameEntity
{
public:
	SteeringEntity(DirectX::SimpleMath::Vector2 screenPos = DirectX::SimpleMath::Vector2::Zero, float layerDepth = 0.6f);
	virtual ~SteeringEntity();
	//Init
	virtual void Initialize(ID3D11Device1 * device, const wchar_t* fileName = L"Textures/car.dds");

	DirectX::SimpleMath::Vector2 m_velocity;//@Generate rotation based on it
};

