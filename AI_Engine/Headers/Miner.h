#pragma once

#include "AnimatedEntity.h"
#include "StateMachine.h"
class Miner :
	public AnimatedEntity
{
public:
	Miner();
	Miner(ID3D11Device1 * device, DirectX::SimpleMath::Vector2 screenPos);
	Miner(ID3D11Device1 * device, DirectX::SimpleMath::Vector2 screenPos, float layerDepth);
	~Miner();
	virtual void Initialize(ID3D11Device1 * device, DirectX::SimpleMath::Vector2 screenPos, float layerDepth = 0.5f);
	void Update(float elapsedTime);

	//SM
	StateMachine<Miner> * m_stateMachine;
	//Anim control values
	bool m_startMoving;
	bool m_isMoving;
	float m_fracT;
	//Values
	int m_gold;
	int m_bankedGold;
	int m_thirstiness;
	int m_hunger;
};

