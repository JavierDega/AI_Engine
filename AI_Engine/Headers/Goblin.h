#pragma once
#include "GameEntity.h"
#include "Blackboard.h"
#include "BTNodes.h"

//@Uses BT and blackboard for simple disruptive behaviour
class Goblin :
	public GameEntity
{
public:
	Goblin(DirectX::SimpleMath::Vector2 screenPos = DirectX::SimpleMath::Vector2::Zero, bool pickPocket = false, bool stealFood = false, float layerDepth = 0.4f);
	virtual ~Goblin();
	virtual void Initialize(ID3D11Device1 * device, const wchar_t * fileName = L"Textures/goblin.dds");

	//Variables
	//@Text
	std::unique_ptr<DirectX::SpriteFont> m_font;
	std::wstring m_text;
	//@AI
	Blackboard m_bb;
	BTNode * m_rootNode;
};

//@BTNodes
/// <summary>
/// Defines the condition to enter the Combat sequence node.
/// </summary>
class PickPocketDecorator : 
	public ConditionalDecorator
{
public:
	PickPocketDecorator(BTNode * WrappedNode, Blackboard * bb);

	virtual bool CheckStatus()override;
};
