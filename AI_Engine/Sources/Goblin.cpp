#include "pch.h"
#include "..\Headers\Goblin.h"
#include "GameScene.h"
#include "MinerSM.h"
#include "WifeSM.h"
#include "TempEntity.h"

using namespace DirectX;
using namespace SimpleMath;

Goblin::Goblin(Vector2 screenPos, bool pickPocket, bool stealFood, float layerDepth)
	: GameEntity(screenPos, layerDepth), m_bb( screenPos, pickPocket, stealFood )
{
	m_execRate = 1.5f;
	m_lastExec = 0.f;
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

	CompositeNode * PickPocketSequence = new Sequence(&m_bb);
	PickPocketDecorator * PickPocketRoot = new PickPocketDecorator(PickPocketSequence, &m_bb);

	PickPocketSequence->AddChild( new MoveTowards(&m_bb));
	PickPocketSequence->AddChild(new PickPocket(&m_bb));

	CompositeNode * StealFoodSequence = new Sequence(&m_bb);
	StealFoodDecorator * StealFoodRoot = new StealFoodDecorator(StealFoodSequence, &m_bb);

	StealFoodSequence->AddChild(new MoveTowards(&m_bb));
	StealFoodSequence->AddChild(new StealFood(&m_bb));

	rootChild->AddChild(StealFoodRoot);
	rootChild->AddChild(PickPocketRoot);
}

void Goblin::Update(float elapsedTime)
{
	//Execution rate same as wife and miner
	m_lastExec += elapsedTime;
	if (m_lastExec >= m_execRate) {
		m_lastExec = 0.f;
		m_rootNode->Execute();
		m_screenPos = m_bb.m_desiredLocation;
	}
}
//Utility
bool Goblin::QueryClick(int mX, int mY)
{
	//@Arbitrary value
	if (Vector2::DistanceSquared(m_screenPos, Vector2(mX, mY)) < 500.f) {
		//@Distance is lower than 10
		//We clicked on this guy, return true, delete appropiately
		GameScene * gs = GameScene::GetInstance();

		TempEntity * deadSprite = new TempEntity(m_screenPos, 0.65f, 2.0f);
		deadSprite->Initialize(gs->m_device, L"Textures/deadgoblin.dds");
		gs->InsertEntity(deadSprite);

		//@Commit sudoku
		m_isDeleted = true;

		return true;
	}
	else return false;
}

//@BTNodes
PickPocketDecorator::PickPocketDecorator(BTNode * WrappedNode, Blackboard * bb) 
	: ConditionalDecorator(WrappedNode, bb)
{
}

bool PickPocketDecorator::CheckStatus()
{
	return bb->m_pickPocket;
}


StealFoodDecorator::StealFoodDecorator(BTNode * WrappedNode, Blackboard * bb)
	: ConditionalDecorator( WrappedNode, bb )
{
}

bool StealFoodDecorator::CheckStatus()
{
	return bb->m_stealFood;
}
MoveTowards::MoveTowards(Blackboard * bb)
	: BTNode(bb)
{
}

BTStatus MoveTowards::Execute()
{
	//@Normalized direction to desired location
	Vector2 toDesiredLocation;
	if (bb->m_pickPocket) {
		//Lerp desiredLocation to pickPocket location every execRate, return running until we reach

		toDesiredLocation = Vector2(1200, 550) - bb->m_desiredLocation;
	}
	if (bb->m_stealFood) {
		//Lerp desiredLocation to pickPocket location every execRate, return running until we reach

		toDesiredLocation = Vector2(1175, 425) - bb->m_desiredLocation;
	}
	if (toDesiredLocation.Length() <= bb->m_speed) {
		//@We reached
		return BTStatus::SUCCESS;
	}
	toDesiredLocation.Normalize();
	bb->m_desiredLocation += toDesiredLocation*bb->m_speed;
	return BTStatus::RUNNING;
}

void MoveTowards::Reset()
{
}

PickPocket::PickPocket(Blackboard * bb)
	: BTNode(bb)
{
}

BTStatus PickPocket::Execute()
{
	//If miner is mining, get one gold from it. Careful not to bring him below 0 gold
	GameScene * gs = GameScene::GetInstance();
	Miner * miner = gs->GetMiner();

	if (miner->m_stateMachine->m_charState == MinerStates::MINING_GOLD) {
		//Get one gold
		if (miner->m_gold > 0) miner->m_gold--;
		else if (miner->m_bankedGold > 0) miner->m_bankedGold--;
	}
	//Never ends til it gets killed.
	return BTStatus::RUNNING;
}

void PickPocket::Reset()
{
	//@
}

StealFood::StealFood(Blackboard * bb)
	: BTNode(bb)
{
}

BTStatus StealFood::Execute()
{
	//@If wife is cooking , get one cookState from her, Careful not to bring her below 0 cookstate.
	//If miner is mining, get one gold from it. Careful not to bring him below 0 gold
	GameScene * gs = GameScene::GetInstance();
	Wife * wife = gs->GetWife();

	if (wife->m_stateMachine->m_charState == WifeStates::COOKING) {
		if (wife->m_cookState > 0) wife->m_cookState--;
	}

	return BTStatus::RUNNING;
}

void StealFood::Reset()
{
}

