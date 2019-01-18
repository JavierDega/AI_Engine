#pragma once
#include "BaseEntity.h"
///THIS CLASS REFERS TO ENTITIES DRAWN THROUGH a screenPos, and origin mapping. 
class GameEntity :
	public BaseEntity
{
public:
	GameEntity();
	~GameEntity();
	//Init
	virtual void Initialize(ID3D11Device1 * device, const wchar_t* fileName = L"Textures/gameentity.dds",
		DirectX::SimpleMath::Vector2 screenPos = DirectX::SimpleMath::Vector2( 0, 0));
	void InitWindow(D3D11_VIEWPORT newScreenViewport);
	void Render(DirectX::SpriteBatch * spriteBatch);
	virtual void Update(float elapsedTime);
	
	//Variables
	DirectX::SimpleMath::Vector2 m_screenPos;
	DirectX::SimpleMath::Vector2 m_origin;
};
