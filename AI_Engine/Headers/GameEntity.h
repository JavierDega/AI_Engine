#pragma once
#include "BaseEntity.h"
///THIS CLASS REFERS TO ENTITIES DRAWN THROUGH a screenPos, and origin mapping. 
class GameEntity :
	public BaseEntity
{
public:
	GameEntity();
	GameEntity(ID3D11Device1 * device);
	~GameEntity();
	//Init
	virtual void Initialize(ID3D11Device1 * device, const wchar_t* fileName, DirectX::SimpleMath::Vector2 screenPos);
	void InitWindow(D3D11_VIEWPORT newScreenViewport);
	void Render(DirectX::SpriteBatch * spriteBatch);
	virtual void Update(float elapsedTime);
	
	//Variables
	DirectX::SimpleMath::Vector2 m_screenPos;
	DirectX::SimpleMath::Vector2 m_origin;
};
