#include "pch.h"
#include "..\Headers\GameScene.h"

#include "GameEntity.h"
#include "UIButton.h"
#include "ClickerButton.h"
#include "AnimatedEntity.h"
#include "Miner.h"
#include "Wife.h"

#include <iostream>
using namespace DirectX;
using namespace DirectX::SimpleMath;

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
	RemoveAllEntities();
}

//Initializes first scene (Main Menu?)
void GameScene::Initialize(ID3D11Device1* device, ID3D11DeviceContext1 * deviceContext)
{
	//Init resources: EntityManager creation->Take data from gameScene?
	m_spriteBatch = std::make_unique<SpriteBatch>(deviceContext);
	LoadStartMenu(device);
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
	for (unsigned int i = 0; i < m_entities.size(); i++) {
		m_entities[i]->Update(elapsedTime);
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

void GameScene::LoadStartMenu(ID3D11Device1 * device)
{
	//Deplete vector, call destructors
	RemoveAllEntities();

	UIEntity* myUIBackground = new UIEntity(0, 1, 0, 1);
	myUIBackground->Initialize(device, L"Textures/menger.dds");
	UIEntity* myTitle = new UIEntity(0.25, 0.75, 0, 0.4);
	myTitle->Initialize(device, L"Textures/aitoolbox.dds");
	UIButton* myButton = new UIButton(ButtonType::LOADSCENE1, 0.4, 0.60, 0.5, 0.6);
	myButton->Initialize(device, L"Textures/goldrushbutton.dds");


	InsertEntity(myUIBackground);
	InsertEntity(myTitle);
	InsertEntity(myButton);

	InitWindow(m_currentViewport);
}

void GameScene::LoadScene1(ID3D11Device1 * device)
{
	//Deplete vector, call destructors
	RemoveAllEntities();

	//Initialize:
	//The Scene1 consists of a static background Texture (Mine field, other stuff?)
	UIButton * myBackButton = new UIButton(ButtonType::LOADMENU, 0, 0.15, 0, 0.075);
	myBackButton->Initialize(device, L"Textures/backbutton.dds");

	ClickerButton * myGoldButton = new ClickerButton(ButtonType::INCREASEGOLD, 0, 0.1, 0.2, 0.25, 5);
	myGoldButton->Initialize(device, L"Textures/goldbutton.dds");

	ClickerButton * myCookButton = new ClickerButton(ButtonType::INCREASECOOK, 0, 0.1, 0.3, 0.35, 5);
	myCookButton->Initialize(device, L"Textures/cookbutton.dds");

	GameEntity* myGameBackground = new GameEntity(Vector2(1920 / 2, 1080 / 2), 0.7f);
	myGameBackground->Initialize(device, L"Textures/forestbackground.dds");

	GameEntity* myMineIcon = new GameEntity(Vector2(1250, 550));
	myMineIcon->Initialize(device, L"Textures/mine.dds");

	GameEntity* myBedIcon = new GameEntity(Vector2(675, 575));
	myBedIcon->Initialize(device, L"Textures/bed.dds");

	GameEntity* myChestIcon = new GameEntity(Vector2(925, 450));
	myChestIcon->Initialize(device, L"Textures/chest.dds");

	GameEntity* myShopIcon = new GameEntity(Vector2(925, 650));
	myShopIcon->Initialize(device, L"Textures/shop.dds");

	GameEntity* myBowlIcon = new GameEntity(Vector2(1220, 425));
	myBowlIcon->Initialize(device, L"Textures/cookstand.dds");

	AnimatedEntity* myAnimEntity = new AnimatedEntity(Vector2(500, 250));
	myAnimEntity->Initialize(device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);
	
	AnimatedEntity* myAnimEntity2 = new AnimatedEntity(Vector2(300, 550));
	myAnimEntity2->Initialize(device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);
	
	AnimatedEntity* myAnimEntity3 = new AnimatedEntity(Vector2(200, 450));
	myAnimEntity3->Initialize(device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);
	
	AnimatedEntity* myAnimEntity4 = new AnimatedEntity(Vector2(1200, 800));
	myAnimEntity4->Initialize(device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);
	
	AnimatedEntity* myAnimEntity5 = new AnimatedEntity(Vector2(1400, 100));
	myAnimEntity5->Initialize(device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);

	AnimatedEntity* myAnimEntity6 = new AnimatedEntity(Vector2(1400, 350));
	myAnimEntity6->Initialize(device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);

	AnimatedEntity* myAnimEntity7 = new AnimatedEntity(Vector2(1400, 650));
	myAnimEntity7->Initialize(device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);

	AnimatedEntity* myAnimEntity8 = new AnimatedEntity(Vector2(1450, 450));
	myAnimEntity8->Initialize(device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);

	AnimatedEntity* myAnimEntity9 = new AnimatedEntity(Vector2(1200, 150));
	myAnimEntity9->Initialize(device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);

	AnimatedEntity* myAnimEntity10 = new AnimatedEntity(Vector2(1000, 250));
	myAnimEntity10->Initialize(device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);
	
	AnimatedEntity* myAnimEntity11 = new AnimatedEntity(Vector2(750, 225));
	myAnimEntity11->Initialize(device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);

	AnimatedEntity* myAnimEntity12 = new AnimatedEntity(Vector2(600, 850));
	myAnimEntity12->Initialize(device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);

	AnimatedEntity* myAnimEntity13 = new AnimatedEntity(Vector2(400, 750));
	myAnimEntity13->Initialize(device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);

	AnimatedEntity* myAnimEntity14 = new AnimatedEntity(Vector2(800, 850));
	myAnimEntity14->Initialize(device, L"Textures/bushanimated.dds", L"Textures/animatedentitybase.dds", 2, 2);


	Wife* myWife = new Wife(Vector2(1220, 425), 0.5f);
	myWife->Initialize(device);
	
	Miner* myMiner = new Miner(Vector2(1000, 550), 0.5f);
	myMiner->Initialize(device);


	//Insert in vector
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
	//UI
	InsertEntity(myBackButton);
	InsertEntity(myGoldButton);
	InsertEntity(myCookButton);

	InitWindow(m_currentViewport);
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

