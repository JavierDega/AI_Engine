#include "pch.h"
#include "..\Headers\AnimatedEntity.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace Microsoft::WRL;
AnimatedEntity::AnimatedEntity(Vector2 screenPos, float layerDepth)
	: GameEntity(screenPos, layerDepth)
{
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

void AnimatedEntity::Initialize(ID3D11Device1 * device, const wchar_t * fileName, const wchar_t * fileName2, int frameCount, int fps)
{
	GameEntity::Initialize(device, fileName2);

	//Animated Textures in vector (Ruled by enum?)

	//Ideally the resurce width and height are the same
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_animTexture;
	DX::ThrowIfFailed(
		CreateDDSTextureFromFile(device, fileName,
			nullptr, m_animTexture.ReleaseAndGetAddressOf())
	);
	m_animatedTextures.push_back(m_animTexture);

	//Make with layerDepth
	m_animator = std::make_unique<AnimatedTexture>(m_origin, 0.0f, 1.0f, m_layerDepth);
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
