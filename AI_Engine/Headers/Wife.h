#pragma once

#include "AnimatedEntity.h"
#include "StateMachine.h"

class Wife :
	public AnimatedEntity
{
public:
	Wife(DirectX::SimpleMath::Vector2 screenPos = DirectX::SimpleMath::Vector2::Zero , float layerDepth = 0.4f);
	~Wife();
	virtual void Initialize(ID3D11Device1 * device);
	void Update(float elapsedTime);
	//Draw
	virtual void Render(DirectX::SpriteBatch * spriteBatch);

	//Variables
	//Graphic
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_foodStackTexture;
	//Font
	std::unique_ptr<DirectX::SpriteFont> m_font;
	std::wstring m_text;
	//SM
	StateMachine<Wife> * m_stateMachine;
	//Anim control values
	bool m_startMoving;
	bool m_isMoving;
	float m_fracT;
	//Values
	int m_cookState;
	int m_foodStack, m_drinkStack;
};
