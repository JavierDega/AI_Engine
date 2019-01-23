#include "pch.h"
#include "..\Headers\GameScene.h"

#include "GameEntity.h"
#include "UIButton.h"
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

	UIEntity* myUIBackground = new UIEntity(device);

	UIEntity* myTitle = new UIEntity();
	myTitle->Initialize(device, L"Textures/aititle.dds", 0.25, 0.75, 0, 0.5);
	UIButton* myButton = new UIButton();
	myButton->Initialize(device, L"Textures/fsmbutton.dds", ButtonType::LOADSCENE1, 0.3, 0.55, 0.5, 0.6);


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
	UIButton * myBackButton = new UIButton();
	myBackButton->Initialize(device, L"Textures/backbutton.dds", ButtonType::LOADMENU, 0, 0.1, 0, 0.1);

	GameEntity* myGameBackground = new GameEntity();
	myGameBackground->Initialize(device, L"Textures/forestbackground.dds", Vector2(1920 / 2, 1080 / 2));

	AnimatedEntity* myAnimEntity = new AnimatedEntity();
	myAnimEntity->Initialize(device, L"Textures/bushanimated.dds", Vector2(500, 250), 3, 2);
	
	AnimatedEntity* myAnimEntity2 = new AnimatedEntity();
	myAnimEntity2->Initialize(device, L"Textures/bushanimated.dds", Vector2(300, 550), 3, 2);
	
	AnimatedEntity* myAnimEntity3 = new AnimatedEntity();
	myAnimEntity3->Initialize(device, L"Textures/bushanimated.dds", Vector2(200, 450), 3, 2);
	
	AnimatedEntity* myAnimEntity4 = new AnimatedEntity();
	myAnimEntity4->Initialize(device, L"Textures/bushanimated.dds", Vector2(1200, 800), 3, 2);
	
	AnimatedEntity* myAnimEntity5 = new AnimatedEntity();
	myAnimEntity5->Initialize(device, L"Textures/bushanimated.dds", Vector2(1400, 650), 3, 2);
	
	Miner* myMiner = new Miner();
	myMiner->Initialize(device, Vector2(1000, 550), 0.5f);

	Wife* myWife = new Wife();
	myWife->Initialize(device, Vector2(950, 550), 0.5f);
	//Insert in vector
	//Wife
	InsertEntity(myWife);
	//Miner
	InsertEntity(myMiner);
	//Anim entities
	InsertEntity(myAnimEntity);
	InsertEntity(myAnimEntity2);
	InsertEntity(myAnimEntity3);
	InsertEntity(myAnimEntity4);
	InsertEntity(myAnimEntity5);
	//Background
	InsertEntity(myGameBackground);
	//UI
	InsertEntity(myBackButton);

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

GameScene * GameScene::GetInstance()
{
	//Singleton
	if (m_instance == NULL)
	{
		m_instance = new GameScene();
	}
	return m_instance;
}
