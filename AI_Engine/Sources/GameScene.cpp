#include "pch.h"
#include "..\Headers\GameScene.h"

#include "GameEntity.h"
#include "ScrollingEntity.h"
#include "UIButton.h"
#include "ClickerButton.h"
#include "AnimatedEntity.h"
#include "GoblinSpawner.h"
#include "Goblin.h"
#include "Miner.h"
#include "Wife.h"
#include "SteeringEntity.h"
#include "CitySpawner.h"
#include "Fence.h"

#include <iostream>

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

GameScene* GameScene::m_instance = NULL;

GameScene::GameScene()
{

}

GameScene * GameScene::GetInstance()
{
	//Singleton
	if (m_instance == NULL)
	{
		m_instance = new GameScene();
	}
	return m_instance;
}

GameScene::~GameScene()
{
	m_device = nullptr;
	RemoveAllEntities();
}

//Initializes first scene (Main Menu?)
void GameScene::Initialize(ID3D11Device1* device, ID3D11DeviceContext1 * deviceContext)
{	
	m_device = device;
	//Init resources: EntityManager creation->Take data from gameScene?
	m_spriteBatch = std::make_unique<SpriteBatch>(deviceContext);
	LoadStartMenu();
}

void GameScene::InitWindow(D3D11_VIEWPORT newScreenViewport)
{
	m_currentViewport = newScreenViewport;
	//Init gamescene entities
	for (unsigned int i = 0; i < m_entities.size(); i++) {
		m_entities[i]->InitWindow(m_currentViewport);
	}
}

void GameScene::Update(float elapsedTime)
{
	//@Update NavGraph (Ideally behind a timer)
	UpdateGraph();

	for (unsigned int i = 0; i < m_entities.size(); i++) {
		m_entities[i]->Update(elapsedTime);
	}
	//Second object pass where we delete entities marked for deletion
	for (unsigned int i = 0; i < m_entities.size(); i++) {
		
		if (m_entities[i]->m_isDeleted) {
			RemoveAt(i);
			i--;
		}
	}
}

void GameScene::Render()
{
	//Use each rigidbodies position to create a worldMatrix, draw their shape against the view and projection matrices
	m_spriteBatch->Begin(SpriteSortMode_BackToFront);

	for (unsigned int i = 0; i < m_entities.size(); i++) {
		m_entities[i]->Render(m_spriteBatch.get());
	}

	m_spriteBatch->End();
}

void GameScene::Reset()
{
	//Device Lost
	m_spriteBatch.reset();
	//Destroying entities deals with smartPointer reset(Allocated in destructor)
	RemoveAllEntities();
}

void GameScene::LoadStartMenu()
{
	//Deplete vector, call destructors
	RemoveAllEntities();

	UIEntity* myUIBackground = new UIEntity(0, 1, 0, 1);
	myUIBackground->Initialize(m_device, L"Textures/menger.dds");
	UIEntity* myTitle = new UIEntity(0.25, 0.75, 0, 0.4);
	myTitle->Initialize(m_device, L"Textures/aitoolbox.dds");
	UIButton* myButton = new UIButton(ButtonType::LOADSCENE1, 0.4, 0.60, 0.5, 0.6);
	myButton->Initialize(m_device, L"Textures/goldrushbutton.dds");
	UIButton * myButton2 = new UIButton(ButtonType::LOADSCENE2, 0.4, 0.6, 0.7, 0.8);
	myButton2->Initialize(m_device, L"Textures/citychasebutton.dds");


	InsertEntity(myUIBackground);
	InsertEntity(myTitle);
	InsertEntity(myButton);
	InsertEntity(myButton2);

	InitWindow(m_currentViewport);
}

void GameScene::LoadScene1()
{
	//Deplete vector, call destructors
	RemoveAllEntities();

	//Initialize:
	//The Scene1 consists of a static background Texture (Mine field, other stuff?)
	UIButton * myBackButton = new UIButton(ButtonType::LOADMENU, 0, 0.15, 0, 0.075);
	myBackButton->Initialize(m_device, L"Textures/backbutton.dds");

	ClickerButton * myGoldButton = new ClickerButton(ButtonType::INCREASEGOLD, 0, 0.1, 0.2, 0.25, 5);
	myGoldButton->Initialize(m_device, L"Textures/goldbutton.dds");

	ClickerButton * myCookButton = new ClickerButton(ButtonType::INCREASECOOK, 0, 0.1, 0.3, 0.35, 5);
	myCookButton->Initialize(m_device, L"Textures/cookbutton.dds");

	GameEntity* myGameBackground = new GameEntity(Vector2(1920 / 2, 1080 / 2), 0.7f);
	myGameBackground->Initialize(m_device, L"Textures/forestbackground.dds");

	GameEntity* myMineIcon = new GameEntity(Vector2(1250, 550));
	myMineIcon->Initialize(m_device, L"Textures/mine.dds");

	GameEntity* myBedIcon = new GameEntity(Vector2(675, 575));
	myBedIcon->Initialize(m_device, L"Textures/bed.dds");

	GameEntity* myChestIcon = new GameEntity(Vector2(925, 450));
	myChestIcon->Initialize(m_device, L"Textures/chest.dds");

	GameEntity* myShopIcon = new GameEntity(Vector2(925, 650));
	myShopIcon->Initialize(m_device, L"Textures/shop.dds");

	GameEntity* myBowlIcon = new GameEntity(Vector2(1220, 425));
	myBowlIcon->Initialize(m_device, L"Textures/cookstand.dds");

	AnimatedEntity* myAnimEntity = new AnimatedEntity(Vector2(500, 250), 0.35f);
	myAnimEntity->Initialize(m_device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);
	
	AnimatedEntity* myAnimEntity2 = new AnimatedEntity(Vector2(300, 550), 0.35f );
	myAnimEntity2->Initialize(m_device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);
	
	AnimatedEntity* myAnimEntity3 = new AnimatedEntity(Vector2(200, 450), 0.35f );
	myAnimEntity3->Initialize(m_device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);
	
	AnimatedEntity* myAnimEntity4 = new AnimatedEntity(Vector2(1200, 800), 0.35f );
	myAnimEntity4->Initialize(m_device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);
	
	AnimatedEntity* myAnimEntity5 = new AnimatedEntity(Vector2(1400, 100), 0.35f );
	myAnimEntity5->Initialize(m_device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);

	AnimatedEntity* myAnimEntity6 = new AnimatedEntity(Vector2(1400, 350), 0.35f);
	myAnimEntity6->Initialize(m_device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);

	AnimatedEntity* myAnimEntity7 = new AnimatedEntity(Vector2(1400, 650), 0.35f);
	myAnimEntity7->Initialize(m_device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);

	AnimatedEntity* myAnimEntity8 = new AnimatedEntity(Vector2(1450, 450), 0.35f );
	myAnimEntity8->Initialize(m_device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);

	AnimatedEntity* myAnimEntity9 = new AnimatedEntity(Vector2(1200, 150), 0.35f);
	myAnimEntity9->Initialize(m_device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);

	AnimatedEntity* myAnimEntity10 = new AnimatedEntity(Vector2(1000, 250), 0.35f );
	myAnimEntity10->Initialize(m_device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);
	
	AnimatedEntity* myAnimEntity11 = new AnimatedEntity(Vector2(750, 225), 0.35f );
	myAnimEntity11->Initialize(m_device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);

	AnimatedEntity* myAnimEntity12 = new AnimatedEntity(Vector2(600, 850), 0.35f );
	myAnimEntity12->Initialize(m_device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);

	AnimatedEntity* myAnimEntity13 = new AnimatedEntity(Vector2(400, 750), 0.35f );
	myAnimEntity13->Initialize(m_device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);

	AnimatedEntity* myAnimEntity14 = new AnimatedEntity(Vector2(800, 850), 0.35f);
	myAnimEntity14->Initialize(m_device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);

	AnimatedEntity* myAnimEntity15 = new AnimatedEntity(Vector2(850, 950), 0.35f);
	myAnimEntity15->Initialize(m_device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);

	AnimatedEntity* myAnimEntity16 = new AnimatedEntity(Vector2(1050, 950), 0.35f);
	myAnimEntity16->Initialize(m_device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);

	AnimatedEntity* myAnimEntity17 = new AnimatedEntity(Vector2(1250, 850), 0.35f);
	myAnimEntity17->Initialize(m_device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);

	AnimatedEntity* myAnimEntity18 = new AnimatedEntity(Vector2(1400, 850), 0.35f);
	myAnimEntity18->Initialize(m_device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);

	AnimatedEntity* myAnimEntity19 = new AnimatedEntity(Vector2(1500, 700), 0.35f);
	myAnimEntity19->Initialize(m_device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);

	AnimatedEntity* myAnimEntity20 = new AnimatedEntity(Vector2(1600, 500), 0.35f);
	myAnimEntity20->Initialize(m_device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);

	AnimatedEntity* myAnimEntity21 = new AnimatedEntity(Vector2(1750, 400), 0.35f);
	myAnimEntity21->Initialize(m_device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);

	AnimatedEntity* myAnimEntity22 = new AnimatedEntity(Vector2(1650, 300), 0.35f);
	myAnimEntity22->Initialize(m_device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);

	AnimatedEntity* myAnimEntity23 = new AnimatedEntity(Vector2(1450, 250), 0.35f);
	myAnimEntity23->Initialize(m_device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);

	AnimatedEntity* myAnimEntity24 = new AnimatedEntity(Vector2(1350, 150), 0.35f);
	myAnimEntity24->Initialize(m_device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);

	AnimatedEntity* myAnimEntity25 = new AnimatedEntity(Vector2(1250, 100), 0.35f);
	myAnimEntity25->Initialize(m_device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);

	AnimatedEntity* myAnimEntity26 = new AnimatedEntity(Vector2(1050, 150), 0.35f);
	myAnimEntity26->Initialize(m_device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);

	AnimatedEntity* myAnimEntity27 = new AnimatedEntity(Vector2(950, 100), 0.35f);
	myAnimEntity27->Initialize(m_device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);


	Wife* myWife = new Wife(Vector2(1220, 425), 0.5f);
	myWife->Initialize(m_device);
	
	Miner* myMiner = new Miner(Vector2(1000, 550), 0.5f);
	myMiner->Initialize(m_device);

	GoblinSpawner * myGoblinSpawner = new GoblinSpawner();
	myGoblinSpawner->Initialize(m_device);

	//Insert in vector
	InsertEntity(myGoblinSpawner);
	//Wife
	InsertEntity(myWife);
	//Miner
	InsertEntity(myMiner);

	//Background
	InsertEntity(myGameBackground);
	InsertEntity(myMineIcon);
	InsertEntity(myBedIcon);
	InsertEntity(myChestIcon);
	InsertEntity(myShopIcon);
	InsertEntity(myBowlIcon);
	//Anim entities
	InsertEntity(myAnimEntity);
	InsertEntity(myAnimEntity2);
	InsertEntity(myAnimEntity3);
	InsertEntity(myAnimEntity4);
	InsertEntity(myAnimEntity5);
	InsertEntity(myAnimEntity6);
	InsertEntity(myAnimEntity7);
	InsertEntity(myAnimEntity8);
	InsertEntity(myAnimEntity9);
	InsertEntity(myAnimEntity10);
	InsertEntity(myAnimEntity11);
	InsertEntity(myAnimEntity12);
	InsertEntity(myAnimEntity13);
	InsertEntity(myAnimEntity14);
	InsertEntity(myAnimEntity15);
	InsertEntity(myAnimEntity16);
	InsertEntity(myAnimEntity17);
	InsertEntity(myAnimEntity18);
	InsertEntity(myAnimEntity19);
	InsertEntity(myAnimEntity20);
	InsertEntity(myAnimEntity21);
	InsertEntity(myAnimEntity22);
	InsertEntity(myAnimEntity23);
	InsertEntity(myAnimEntity24);
	InsertEntity(myAnimEntity25);
	InsertEntity(myAnimEntity26);
	InsertEntity(myAnimEntity27);
	//UI
	InsertEntity(myBackButton);
	InsertEntity(myGoldButton);
	InsertEntity(myCookButton);

	InitWindow(m_currentViewport);
}

void GameScene::LoadScene2()
{
	//Deplete vector, call destructors
	RemoveAllEntities();

	UIButton * myBackButton = new UIButton(ButtonType::LOADMENU, 0, 0.15, 0, 0.075);
	myBackButton->Initialize(m_device, L"Textures/backbutton.dds");
	
	ScrollingEntity* myScrollingBg = new ScrollingEntity(Vector2(950, 540), 50.f, 0.6f);
	myScrollingBg->Initialize(m_device);
	
	SteeringEntity * myPlayer = new SteeringEntity(Vector2(1000, 500));
	myPlayer->Initialize(m_device);
	
	SteeringEntity * enemyCar = new SteeringEntity(Vector2(500, 800), 50.f, SteeringType::ENEMY_CAR);
	enemyCar->Initialize(m_device, L"Textures/car.dds");

	SteeringEntity * enemyCar = new SteeringEntity(Vector2(700, 800), 50.f, SteeringType::ENEMY_CAR);
	enemyCar->Initialize(m_device, L"Textures/car.dds");

	SteeringEntity * enemyCar = new SteeringEntity(Vector2(900, 800), 50.f, SteeringType::ENEMY_CAR);
	enemyCar->Initialize(m_device, L"Textures/car.dds");

	SteeringEntity * enemyCar = new SteeringEntity(Vector2(1100, 800), 50.f, SteeringType::ENEMY_CAR);
	enemyCar->Initialize(m_device, L"Textures/car.dds");

	CitySpawner * myCitySpawner = new CitySpawner();
	myCitySpawner->Initialize();

	InsertEntity(myBackButton);
	InsertEntity(myScrollingBg);
	InsertEntity(myPlayer);
	InsertEntity(enemyCar);
	InsertEntity(myCitySpawner);

	InitWindow(m_currentViewport);
}

void GameScene::GoldRushLost()
{
	//Delete miner, wife, goblinSpawner, pause all goblins, spawn MidButton
	for (int i = 0; i < m_entities.size(); i++) {
		
		GetWife()->m_isDeleted = true;
		GetMiner()->m_isDeleted = true;
		GoblinSpawner * goblinSpawner = dynamic_cast<GoblinSpawner*>(m_entities[i]);
		ClickerButton * clickerButton = dynamic_cast<ClickerButton*>(m_entities[i]);
		Goblin * goblin = dynamic_cast<Goblin*>(m_entities[i]);

		if (goblin) {
			goblin->m_bb.m_pickPocket = false;
			goblin->m_bb.m_stealFood = false;
		}

		if (goblinSpawner) {
			goblinSpawner->m_isDeleted = true;
		}

		if (clickerButton) {
			clickerButton->m_isDeleted = true;
		}
	}

	//Create UI Entity that conveys lost
	UIEntity* myLostMessage = new UIEntity(0.4, 0.6, 0.4, 0.6);
	//UI Entities need an InitWindow() call
	myLostMessage->InitWindow(m_currentViewport);
	myLostMessage->Initialize(m_device, L"Textures/YouLost.dds");
	InsertEntity(myLostMessage);
}

void GameScene::CityChaseLost()
{
	LoadStartMenu();//@For now
}

void GameScene::InsertEntity(BaseEntity* entity)
{
	m_entities.push_back(entity);
}

void GameScene::RemoveEntity(BaseEntity * entity)
{
	//Delete instance from vector and pointer
	if (entity == NULL) return;

	int index = -1;

	if (ContainsEntity(entity, index))
	{
		m_entities.erase(m_entities.begin() + index);

		delete entity;
	}
}
//Swap and pop
void GameScene::RemoveAt(int index) {
	//Swap and pop approach (NOT Needed)
	if (index < m_entities.size() - 1) {
		swap(m_entities[index], m_entities.back());
	}
	BaseEntity * entity = m_entities.back();
	m_entities.pop_back();
	delete entity;
}

void GameScene::RemoveAllEntities()
{
	//Safety check
	while (!m_entities.empty()) {
		BaseEntity * curEntity = m_entities[m_entities.size() - 1];
		//Remove from vector
		m_entities.pop_back();
		//Destructor**
		delete curEntity;
	}
}

bool GameScene::ContainsEntity(BaseEntity * entity)
{
	int size = (int)m_entities.size();
	for (int i = 0; i < size; ++i)
	{
		if (m_entities[i] == entity)
		{
			return true;
		}
	}
	std::cout << "Entity is not on the GameScene's vector" << std::endl;
	return false;
}

bool GameScene::ContainsEntity(BaseEntity *entity, int & index)
{
	//Find and return index
	index = -1;
	int size = (int)m_entities.size();
	for (int i = 0; i < size; ++i)
	{
		if (m_entities[i] == entity)
		{
			index = i;
			return true;
		}
	}
	return false;
}

void GameScene::UpdateGraph()
{
	//@Get all obstacle entities, perform standard rules for edge generation
	//@Plus distance function to all obstacles (So edges aren't generated for them)
	vector<Vector2> fencePositions;

	for (int i = 0; i < m_entities.size(); i++) {
		Fence * fenceEntity = dynamic_cast<Fence*>(m_entities[i]);
		if (fenceEntity) fencePositions.push_back(fenceEntity->m_screenPos);
	}
	//@They all occupy a 3by2 grid
	
	//@DEFAULT GRAPH
	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			GraphNode * node = &m_graph.m_nodes[x][y];
			node->m_edges.clear();
			node->m_index = x + y * 20;
			
			if (y > 0) {
				//@Check there's no barrier directly up  (close by one and a half grid on the x),(one grid pixels less).
				bool nodeCollides = false;
				Vector2 nodeToPos = Vector2(x * 60 - 360, (y - 1) * 54);
				for (Vector2 fencePosition : fencePositions) {
					if (abs(fencePosition.x - nodeToPos.x) > 120) {
						continue;
					}
					if (abs(fencePosition.y - nodeToPos.y) > 108) {
						continue;
					}
					//@Else its quite close
					nodeCollides = true;
				}
				if (!nodeCollides)node->m_edges.push_back(GraphEdge(node->m_index, node->m_index - 20));
			}
			if (y < 19) {
				//@Check there's no barrier directly down (close by one and a half grid on the x), (one grid pixels more).
				bool nodeCollides = false;
				Vector2 nodeToPos = Vector2(x * 60 - 360, (y + 1) * 54);
				for (Vector2 fencePosition : fencePositions) {
					if (abs(fencePosition.x - nodeToPos.x) > 120) {
						continue;
					}
					if (abs(fencePosition.y - nodeToPos.y) > 108) {
						continue;
					}
					//@Else its quite close
					nodeCollides = true;
				}
				if (!nodeCollides)node->m_edges.push_back(GraphEdge(node->m_index, node->m_index + 20));
			}
			if (x > 0) {
				//@Check there's no barrier directly to the left (close by one grid on the y),(one and a half grid to the left).
				bool nodeCollides = false;
				Vector2 nodeToPos = Vector2((x - 1) * 60 - 360, y * 54);
				for (Vector2 fencePosition : fencePositions) {
					if (abs(fencePosition.x - nodeToPos.x) > 120) {
						continue;
					}
					if (abs(fencePosition.y - nodeToPos.y) > 108) {
						continue;
					}
					//@Else its quite close
					nodeCollides = true;
				}
				if (!nodeCollides) node->m_edges.push_back(GraphEdge(node->m_index, node->m_index - 1));
			}
			if (x < 19) {
				//@Check there's no barrier directly to the right (close by one grid on the y),(one and a half grid to the right).
				bool nodeCollides = false;
				Vector2 nodeToPos = Vector2((x + 1) * 60 - 360, y * 54);
				for (Vector2 fencePosition : fencePositions) {
					if (abs(fencePosition.x - nodeToPos.x) > 120) {
						continue;
					}
					if (abs(fencePosition.y - nodeToPos.y) > 108) {
						continue;
					}
					//@Else its quite close
					nodeCollides = true;
				}
				if (!nodeCollides) node->m_edges.push_back(GraphEdge(node->m_index, node->m_index + 1));
			}
		}
	}
}

Wife * GameScene::GetWife()
{
	for (unsigned int i = 0; i < m_entities.size(); i++) {
		//Look for entities which can be mouse pressed
		Wife * wife = dynamic_cast<Wife *>(m_entities[i]);
		if (wife) {
			return wife;
		}
	}
	return nullptr;
}

Miner * GameScene::GetMiner()
{
	for (unsigned int i = 0; i < m_entities.size(); i++) {
		//Look for entities which can be mouse pressed
		Miner * miner = dynamic_cast<Miner *>(m_entities[i]);
		if (miner) {
			return miner;
		}
	}
	return nullptr;
}

SteeringEntity * GameScene::GetPlayerCar() {
	for (unsigned int i = 0; i < m_entities.size(); i++) {
		//Look for entities which can be mouse pressed
		SteeringEntity * player = dynamic_cast<SteeringEntity *>(m_entities[i]);
		if (player) {
			if (player->m_type == SteeringType::PLAYER_CAR) {
				return player;
			}
		}
	}
	return nullptr;
}
