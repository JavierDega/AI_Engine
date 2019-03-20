#pragma once
#include "GameEntity.h"
#include "ScrollingBackground.h"

class ScrollingEntity :
	public GameEntity
{
public:
	ScrollingEntity(DirectX::SimpleMath::Vector2 screenPos = DirectX::SimpleMath::Vector2::Zero, float speed = 300.f, float layerDepth = 0.6f);
	//May need to be virtual , since it adds a vector of texture pointers
	virtual ~ScrollingEntity();
	//Init
	virtual void Initialize(ID3D11Device1 * device, const wchar_t* fileName = L"Textures/citybackground.dds");
	void InitWindow(D3D11_VIEWPORT newScreenViewport);
	void Render(DirectX::SpriteBatch * spriteBatch);
	virtual void Update(float elapsedTime);

	//Variables
	std::unique_ptr<ScrollingBackground> m_background;
	float m_speed;
};
