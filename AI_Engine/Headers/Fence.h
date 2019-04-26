#pragma once
#include "GameEntity.h"

class Fence :
	public GameEntity
{
public:
	Fence(DirectX::SimpleMath::Vector2 screenPos = DirectX::SimpleMath::Vector2::Zero, float speed = 50.f,
		float layerDepth = 0.6f);
	virtual ~Fence();
	//Init
	virtual void Initialize(ID3D11Device1 * device, const wchar_t * fileName = L"Textures/fence.dds");
	virtual void Render(DirectX::SpriteBatch * spriteBatch);
	virtual void Update(float elapsedTime);

	float m_scrollSpeed;
};
