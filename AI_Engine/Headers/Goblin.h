#pragma once
#include "GameEntity.h"
#include "Blackboard.h"
#include "BTNodes.h"

//@Uses BT and blackboard for simple disruptive behaviour
class Goblin :
	public GameEntity
{
public:
	Goblin(DirectX::SimpleMath::Vector2 screenPos = DirectX::SimpleMath::Vector2::Zero, float layerDepth = 0.4f);
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

//@Define goblin specific nodes
class DefineGoal
	: public BTNode
{
	DefineGoal(Blackboard bb);

	virtual BTStatus Execute();

	/// <summary>
	/// Reset should be overidden in child classes as and when necessary
	/// It should be called when a node is abruptly aborted before it can finish with a success or failure
	/// i.e the node was still RUNNING when it is aborted you need to gracefully handle it to avoid unintended bugs
	/// See DelayNode, CompositeNode and DecoratorNode for examples
	/// </summary>
	virtual void Reset();

protected:
	Blackboard bb;
};
