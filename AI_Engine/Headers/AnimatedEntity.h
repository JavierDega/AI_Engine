#pragma once
#include "GameEntity.h"
#include "AnimatedTexture.h"

class AnimatedEntity :
	public GameEntity
{
public:
	AnimatedEntity();
	AnimatedEntity(ID3D11Device1 * device);
	//May need to be virtual , since it adds a vector of texture pointers
	~AnimatedEntity();
	//Init
	virtual void Initialize(ID3D11Device1 * device, const wchar_t * fileName, DirectX::SimpleMath::Vector2 screenPos, int frameCount, int fps, float layerDepth = 0.5f);
	//Draw
	void Render(DirectX::SpriteBatch * spriteBatch);
	virtual void Update(float elapsedTime);

	std::unique_ptr<AnimatedTexture> m_animator;
	std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_animatedTextures;
};
