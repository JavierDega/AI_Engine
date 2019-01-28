#pragma once
#include "GameEntity.h"
#include "AnimatedTexture.h"

class AnimatedEntity :
	public GameEntity
{
public:
	AnimatedEntity(DirectX::SimpleMath::Vector2 screenPos = DirectX::SimpleMath::Vector2::Zero, float layerDepth = 0.5f);
	//May need to be virtual , since it adds a vector of texture pointers
	virtual ~AnimatedEntity();
	//Init
	virtual void Initialize(ID3D11Device1 * device, const wchar_t * fileName, const wchar_t * fileName2, int frameCount, int fps);
	//Update
	virtual void Update(float elapsedTime);
	//Draw
	virtual void Render(DirectX::SpriteBatch * spriteBatch);

	//Variables
	std::unique_ptr<AnimatedTexture> m_animator;
	std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_animatedTextures;
};
