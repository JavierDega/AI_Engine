#pragma once
#include "GameEntity.h"
#include "Blackboard.h"
#include "BTNodes.h"

//@Uses BT and blackboard for simple disruptive behaviour
//@IDEA, they drop coins on death??
class Goblin :
	public GameEntity
{
public:
	Goblin(DirectX::SimpleMath::Vector2 screenPos = DirectX::SimpleMath::Vector2::Zero, bool pickPocket = false, bool stealFood = false, float layerDepth = 0.4f);
	virtual ~Goblin();
	virtual void Initialize(ID3D11Device1 * device, const wchar_t * fileName = L"Textures/goblin.dds");
	virtual void Update(float elapsedTime);
	//Utility
	bool QueryClick( ID3D11Device1 * device, int mX, int mY);
	//Variables
	//@Text
	std::unique_ptr<DirectX::SpriteFont> m_font;
	std::wstring m_text;
	//@AI
	Blackboard m_bb;
	BTNode * m_rootNode;
	float m_execRate;
	float m_lastExec;
};

//@BTNodes
/// <summary>
/// Defines the condition to enter the pick pocket sequence node
/// </summary>
class PickPocketDecorator : 
	public ConditionalDecorator
{
public:
	PickPocketDecorator(BTNode * WrappedNode, Blackboard * bb);

	virtual bool CheckStatus()override;
};

/// <summary>
/// Defines the condition to enter the pick pocket sequence node
/// </summary>
class StealFoodDecorator :
	public ConditionalDecorator
{
public:
	StealFoodDecorator(BTNode * WrappedNode, Blackboard * bb);

	virtual bool CheckStatus()override;
};

/// <summary>
/// Move towards desired location (Handle movement communication BlackBoard->GoblinEntity.
/// </summary>
class MoveTowards :
	public BTNode
{
public:
	MoveTowards(Blackboard * bb);
	virtual BTStatus Execute()override;
	virtual void Reset()override;


};

class PickPocket :
	public BTNode
{
public:
	PickPocket(Blackboard * bb);
	virtual BTStatus Execute()override;
	virtual void Reset()override;

};

class StealFood :
	public BTNode
{
public:
	StealFood(Blackboard * bb);
	virtual BTStatus Execute()override;
	virtual void Reset()override;

};