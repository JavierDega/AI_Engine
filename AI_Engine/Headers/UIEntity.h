#pragma once
#include "BaseEntity.h"

///Use RECTs as a means of identifying position
class UIEntity : 
	public BaseEntity
{
public:
	UIEntity();
	//Init, load texture
	UIEntity(ID3D11Device1* device);
	~UIEntity();
	//Init
	virtual void Initialize(ID3D11Device1 * device, const wchar_t * filename, float leftRect, float rightRect, float topRect, float bottomRect);
	virtual void InitWindow(D3D11_VIEWPORT newScreenViewport);
	virtual void Render(DirectX::SpriteBatch * spriteBatch);
	virtual void Update(float elapsedTime);
	float m_leftRect, m_topRect, m_rightRect, m_bottomRect;
	RECT m_UIRect;
};
