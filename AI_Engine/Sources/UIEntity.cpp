#include "pch.h"
#include "..\Headers\UIEntity.h"

using namespace DirectX;
using Microsoft::WRL::ComPtr;


UIEntity::UIEntity()
{
}

UIEntity::UIEntity(ID3D11Device1 * device)
{
	Initialize(device, L"Textures/uientity.dds", 0, 1, 0, 1);
}

UIEntity::~UIEntity()
{
	bool debug;
}

void UIEntity::Initialize(ID3D11Device1 * device, const wchar_t * filename, float leftRect, float rightRect, float topRect, float bottomRect)
{
	//Load texture
	DX::ThrowIfFailed(
		CreateDDSTextureFromFile(device, filename, nullptr, m_texture.ReleaseAndGetAddressOf())
	);
	m_leftRect = leftRect;
	m_topRect = topRect;
	m_rightRect = rightRect;
	m_bottomRect = bottomRect;
}

void UIEntity::InitWindow(D3D11_VIEWPORT newScreenViewport)
{
	//Position
	m_UIRect.left = long(newScreenViewport.Width * m_leftRect);
	m_UIRect.top = long(newScreenViewport.Height * m_topRect);
	m_UIRect.right = long(newScreenViewport.Width * m_rightRect);
	m_UIRect.bottom = long(newScreenViewport.Height * m_bottomRect);
}

void UIEntity::Render(DirectX::SpriteBatch * spriteBatch)
{
	//@Note: layerDepth default = 0; Which is what we want for UIEntities*
	spriteBatch->Draw(m_texture.Get(), m_UIRect);
}

void UIEntity::Update(float elapsedTime)
{
}
