#pragma once
#include "BaseEntity.h"

//@Desirability to spawn goblins, at different positions, with different goals?
//Dictionaries, default desirability?
class GoblinSpawner :
	public BaseEntity
{
public:
	GoblinSpawner();
	virtual ~GoblinSpawner();
	virtual void Initialize(ID3D11Device1 * device = nullptr, const wchar_t * fileName = nullptr )override;
	virtual void InitWindow(D3D11_VIEWPORT newScreenViewport)override;
	virtual void Render(DirectX::SpriteBatch * spriteBatch);
	virtual void Update(float elapsedTime);
	//Variables
	//@makes game hard for player, but not too hard
	float m_playerHealth;//From thirstiness, hunger
	float m_playerWealth;//From gold
	float m_playerPower;//Overall how good the player is doing
	float m_timeSinceLastSpawn;
	//Desirabilities
	float m_desirabilityStealFood;//From wife
	float m_desirabilityPickPocket;//From miner
	float m_desirabilityDisrupt;//Interactable buttons?

	std::shared_ptr<ID3D11ShaderResourceView> m_goblinTexture;

};
