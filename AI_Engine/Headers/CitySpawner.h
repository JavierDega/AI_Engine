#pragma once
#include "BaseEntity.h"
class CitySpawner :
	public BaseEntity
{
public:
	CitySpawner();
	virtual ~CitySpawner();
	virtual void Initialize(ID3D11Device1 * device = nullptr, const wchar_t * fileName = nullptr)override;
	virtual void InitWindow(D3D11_VIEWPORT newScreenViewport)override;
	virtual void Render(DirectX::SpriteBatch * spriteBatch);
	virtual void Update(float elapsedTime);

	//@Variables
	float m_timeSinceLastSpawn;
	float m_spawnTimer;

	//@Font to draw score
	std::unique_ptr<DirectX::SpriteFont> m_font;
	std::wstring m_text;
};
