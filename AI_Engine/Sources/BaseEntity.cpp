#include "pch.h"
#include "..\Headers\BaseEntity.h"

using namespace DirectX;
using Microsoft::WRL::ComPtr;

BaseEntity::BaseEntity()
{
}

BaseEntity::BaseEntity(ID3D11Device1* device)
{
	//Fill m_texture
	DX::ThrowIfFailed(
		CreateDDSTextureFromFile(device, L"Textures/baseentity.dds", nullptr, m_texture.ReleaseAndGetAddressOf())
	);
}


BaseEntity::~BaseEntity()
{
	m_texture.Reset();
}

void BaseEntity::InitWindow(D3D11_VIEWPORT newScreenViewport) {
	//CreateResources call.

}
void BaseEntity::Render(DirectX::SpriteBatch * spriteBatch)
{
	spriteBatch->Draw(m_texture.Get(), SimpleMath::Vector2::Zero);
}

void BaseEntity::Update(float elapsedTime)
{
}

