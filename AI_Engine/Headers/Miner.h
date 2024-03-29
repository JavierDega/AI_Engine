#pragma once

#include "AnimatedEntity.h"
#include "StateMachine.h"
#include "Wife.h"
class Miner :
	public AnimatedEntity
{
public:
	Miner(DirectX::SimpleMath::Vector2 screenPos = DirectX::SimpleMath::Vector2::Zero, float layerDepth = 0.4f);
	~Miner();
	//@Default animation textures
	virtual void Initialize(ID3D11Device1 * device);
	void Update(float elapsedTime);
	//Draw
	virtual void Render(DirectX::SpriteBatch * spriteBatch);


	//Variables
	//Font
	std::unique_ptr<DirectX::SpriteFont> m_font;
	std::wstring m_text;
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
	int m_tiredness;
};

