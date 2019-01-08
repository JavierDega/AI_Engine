#include "pch.h"
#include "..\Headers\AnimatedEntity.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace Microsoft::WRL;
AnimatedEntity::AnimatedEntity()
{

}
//Overloads
AnimatedEntity::AnimatedEntity(ID3D11Device1 * device)
{
	Initialize(device, L"Textures/animatedentity.dds", Vector2(0, 0), 3, 3, 0.5f);
}

AnimatedEntity::~AnimatedEntity()
{
	m_animator.reset();
	while (!m_animatedTextures.empty())
	{
		m_animatedTextures[0].Reset();
		m_animatedTextures.erase(m_animatedTextures.begin());
	}
}

void AnimatedEntity::Initialize(ID3D11Device1 * device, const wchar_t * fileName, DirectX::SimpleMath::Vector2 screenPos, int frameCount, int fps, float layerDepth)
{
	//Original idle texture(Not animated)
	ComPtr<ID3D11Resource> resource;
	//Fill m_texture
	DX::ThrowIfFailed(
		CreateDDSTextureFromFile(device, L"Textures/animatedentitybase.dds",
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

	//Animated Textures in vector (Ruled by enum?)

	//Ideally the resurce width and height are the same
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_animTexture;
	DX::ThrowIfFailed(
		CreateDDSTextureFromFile(device, fileName,
			nullptr, m_animTexture.ReleaseAndGetAddressOf())
	);
	m_animatedTextures.push_back(m_animTexture);

	//All defaults, last argument is layerDepth
	m_animator = std::make_unique<AnimatedTexture>(XMFLOAT2(0, 0), 0.0f, 1.0f, layerDepth);
	m_animator->Load(m_animatedTextures[0].Get(), frameCount, fps);
}


void AnimatedEntity::Render(DirectX::SpriteBatch * spriteBatch)
{
	m_animator->Draw(spriteBatch, m_screenPos);
}

void AnimatedEntity::Update(float elapsedTime)
{
	m_animator->Update(elapsedTime);
}
