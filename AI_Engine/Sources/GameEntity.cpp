#include "pch.h"
#include "..\Headers\GameEntity.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace Microsoft::WRL;
GameEntity::GameEntity()
{
	m_screenPos = Vector2(0, 0);
	m_origin = Vector2(0, 0);
}
//Overloads
GameEntity::GameEntity(ID3D11Device1 * device)
{
	//Initialize with defaults
	Initialize(device, L"Textures/gameentity.dds", Vector2(0, 0));
}

GameEntity::~GameEntity()
{
	bool debug;
}

void GameEntity::Initialize(ID3D11Device1 * device, const wchar_t * fileName, Vector2 screenPos)
{
	ComPtr<ID3D11Resource> resource;
	//Fill m_texture
	DX::ThrowIfFailed(
		CreateDDSTextureFromFile(device, fileName,
			resource.GetAddressOf(),
			m_texture.ReleaseAndGetAddressOf())
	);
	ComPtr<ID3D11Texture2D> tex;
	DX::ThrowIfFailed(resource.As(&tex));

	CD3D11_TEXTURE2D_DESC texDesc;
	tex->GetDesc(&texDesc);

	m_origin.x = float(texDesc.Width / 2);
	m_origin.y = float(texDesc.Height / 2);

	m_screenPos = screenPos;
}

void GameEntity::InitWindow(D3D11_VIEWPORT newScreenViewport)
{
	//Windows size changed.
	//@Assumption: If we dont do anything , everything will stay as it is, meaning things might become visible once we increase window size, or invisible
	//If we reduce it
}

void GameEntity::Render(DirectX::SpriteBatch * spriteBatch)
{
	spriteBatch->Draw(m_texture.Get(), m_screenPos, nullptr, Colors::White, 0.0f, m_origin, Vector2(1,1), SpriteEffects_None, 1.0f);
}

void GameEntity::Update(float elapsedTime)
{
}
