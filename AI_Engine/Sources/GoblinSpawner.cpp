#include "pch.h"
#include "..\Headers\GoblinSpawner.h"
#include "Goblin.h"
#include "GameScene.h"

#include <ctime>
using namespace std;
using namespace DirectX;
using namespace SimpleMath;

GoblinSpawner::GoblinSpawner()
	: m_timeSinceLastSpawn(0)
{
}


GoblinSpawner::~GoblinSpawner()
{
	//@Resources
	m_texture.Reset();

}

void GoblinSpawner::Initialize(ID3D11Device1 * device, const wchar_t * fileName)
{
	//Dont call child's Initialize;
}

void GoblinSpawner::InitWindow(D3D11_VIEWPORT newScreenViewport)
{
	//@Do nuthing
}

void GoblinSpawner::Render(DirectX::SpriteBatch * spriteBatch)
{
	//@Do nuthing, this entity isn't drawn
}

void GoblinSpawner::Update(float elapsedTime)
{
	GameScene * gs = GameScene::GetInstance();
	Miner * miner = gs->GetMiner();
	Wife * wife = gs->GetWife();
	m_timeSinceLastSpawn += elapsedTime;
	
	//Desirability to spawn
	float spawnConstant = 0.5f;
	//@The player's total gold, multiplied by the food and drink stack divided by hunger and thirst 
	m_playerPower = (miner->m_gold + miner->m_bankedGold + wife->m_foodStack + wife->m_drinkStack) 
		/ (1.0f + miner->m_hunger + miner->m_thirstiness + miner->m_tiredness );
	float desirabilitySpawn = spawnConstant * m_playerPower * m_timeSinceLastSpawn;

	if (desirabilitySpawn > 1.0f) {
		m_timeSinceLastSpawn = 0.f;
		//@We can add an entity to the end of GameScene's vector, because we loop while i < m_entities.size()
		//@Choose spawn pos, away from center
		Vector2 goblinSpawnPos;
		#pragma region spawnPos
		srand(time(NULL));
		bool axisBound = (rand() % 100) > 50.f;
		//Choose minimum, maximum extent within that bound
		float extentRand = rand() % 100;
		bool minMaxExtent = extentRand > 50.f;
		//Now we know in what screen bound the enemy will come from,
		if (axisBound) {
			//Vertical bound
			goblinSpawnPos = Vector2((rand()%100)/100.f * 1920, minMaxExtent*1080);
		}
		else {
			//Horizontal bound
			goblinSpawnPos = Vector2(minMaxExtent*1920, (rand()%100)/100.f * 1080);
		}
		#pragma endregion

		//Health is inversely proportional to hunger
		m_playerHealth = (wife->m_foodStack + wife->m_drinkStack) + (10.0f - miner->m_hunger) + ( 10.0f - miner->m_thirstiness) + (10.f - miner->m_tiredness);//Should work within our constrained environment (They either eat after 10 hunger, or lose.)
		m_playerWealth = (miner->m_gold + miner->m_bankedGold);
		//Possible desirabilities to assign to spawned goblin's blackboard
		const float stealFoodConstant = 1.f;
		m_desirabilityStealFood = stealFoodConstant * m_playerHealth;
		const float pickPocketConstant = 1.f;
		m_desirabilityPickPocket = pickPocketConstant * m_playerWealth;

		//For now we don't need 'Map' structures for desirabilities, since there's two
		Goblin * spawnedGoblin = new Goblin(goblinSpawnPos, m_desirabilityPickPocket >= m_desirabilityStealFood, m_desirabilityStealFood > m_desirabilityPickPocket );
		spawnedGoblin->Initialize(GameScene::GetInstance()->m_device);
		gs->InsertEntity(spawnedGoblin);
	}
}
