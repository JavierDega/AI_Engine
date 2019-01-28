#include "pch.h"
#include "..\Headers\BaseEntity.h"

using namespace DirectX;
using namespace SimpleMath;
using Microsoft::WRL::ComPtr;

BaseEntity::BaseEntity(float layerDepth)
	: m_layerDepth(layerDepth)
{
}

void BaseEntity::Initialize(ID3D11Device1* device, const wchar_t * fileName)
{
	//Fill m_texture
	DX::ThrowIfFailed(
		CreateDDSTextureFromFile(device, fileName, nullptr, m_texture.ReleaseAndGetAddressOf())
	);
}

BaseEntity::~BaseEntity()
{
	m_texture.Reset();
}

void BaseEntity::Render(DirectX::SpriteBatch * spriteBatch)
{
	//@Default layerDepth = 0;
	spriteBatch->Draw(m_texture.Get(), Vector2::Zero, nullptr, Colors::White, 0.0f, Vector2::Zero, Vector2( 1, 1 ) , SpriteEffects_None, m_layerDepth);
}

