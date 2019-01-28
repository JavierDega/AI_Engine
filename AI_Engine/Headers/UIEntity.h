#pragma once
#include "BaseEntity.h"

///Use RECTs as a means of identifying position
class UIEntity : 
	public BaseEntity
{
public:
	UIEntity(float leftRect = 0, float rightRect = 1, float topRect = 0, float bottomRect = 1);
	virtual ~UIEntity();
	//Init
	virtual void Initialize(ID3D11Device1 * device, const wchar_t * filename = L"Textures/uientity.dds");
	virtual void InitWindow(D3D11_VIEWPORT newScreenViewport);
	virtual void Render(DirectX::SpriteBatch * spriteBatch);
	virtual void Update(float elapsedTime);
	float m_leftRect, m_topRect, m_rightRect, m_bottomRect;
	RECT m_UIRect;
};
