#include "pch.h"
#include "..\Headers\Goblin.h"

using namespace DirectX;
using namespace SimpleMath;

Goblin::Goblin(DirectX::SimpleMath::Vector2 screenPos, float layerDepth)
{
}

Goblin::~Goblin()
{
	delete m_rootNode;
}

void Goblin::Initialize(ID3D11Device1 * device, const wchar_t * fileName)
{
	GameEntity::Initialize(device, fileName);

	//@Font
	m_font = std::make_unique<SpriteFont>(device, L"Textures/myfile.spritefont");

	//@Build designed behaviour tree
	//@Root node is a sequence, regone through every frame
	//->Evaluate Strategy(Desirability? ideally set goal location)->MoveTowardsLocation(If it's there, leave it/What if two goblins overlap?)->Execute Action (Selector?)
	Sequence * rootChild = new Sequence(m_bb);
	m_rootNode = rootChild;
	


	//rootChild->AddChild(); to add children nodes in BT
}

//@BTNodes
//DefineGoal
DefineGoal::DefineGoal(Blackboard bb)
	: BTNode(bb)
{
	//Possible goals:
	//@To pickpocket miner
	//@To harass wife
}

BTStatus DefineGoal::Execute()
{
	return BTStatus();
}

void DefineGoal::Reset()
{
}
