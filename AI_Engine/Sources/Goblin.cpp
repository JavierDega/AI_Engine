#include "pch.h"
#include "..\Headers\Goblin.h"

using namespace DirectX;
using namespace SimpleMath;

Goblin::Goblin(Vector2 screenPos, bool pickPocket, bool stealFood, float layerDepth)
	: GameEntity(screenPos, layerDepth), m_bb(pickPocket, stealFood)
{
}

Goblin::~Goblin()
{
	delete m_rootNode;
}
//@Dynamically spawned, we have no device
void Goblin::Initialize(ID3D11Device1 * device, const wchar_t * fileName)
{
	GameEntity::Initialize(device, fileName);

	//@Font
	m_font = std::make_unique<SpriteFont>(device, L"Textures/myfile.spritefont");

	//@Build designed behaviour tree
	//@Root node is a sequence, regone through every frame
	//->Evaluate Strategy(Desirability? ideally set goal location)->MoveTowardsLocation(If it's there, leave it/What if two goblins overlap?)->Execute Action (Selector?)
	Selector * rootChild = new Selector(&m_bb);
	m_rootNode = rootChild;
	//rootChild->AddChild(); to add children nodes in BT
}

PickPocketDecorator::PickPocketDecorator(BTNode * WrappedNode, Blackboard * bb) 
	: ConditionalDecorator(WrappedNode, bb)
{
}

//@BTNodes
bool PickPocketDecorator::CheckStatus()
{
	return bb->m_pickPocket;
}
