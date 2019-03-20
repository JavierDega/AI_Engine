#pragma once
#include <vector>
#include "BaseEntity.h"
#include "Wife.h"
#include "Miner.h"

//This class holds the data of the current GameScene
//Update / Render / Find / Delete entities
//Data should be common to ALL scenes (Polymorphism should help)
//-Common GameScene data:
//-A background texture
//-A spriteBatch for drawing
//-A different entity vector for each sorted layer?
class GameScene
{
private:
	/*Here will be the instance stored*/
	static GameScene* m_instance;
	/*Private constructor to prevent instancing*/
	GameScene(void);
public:
	//Singleton
	static GameScene* GetInstance();
	~GameScene(void);
	//Game events
	void Initialize(ID3D11Device1* device, ID3D11DeviceContext1 * deviceContext);
	void InitWindow(D3D11_VIEWPORT newScreenViewport);
	void Update(float elapsedTime);
	void Render();
	void Reset();
	//Load
	void LoadStartMenu();
	void LoadScene1();
	void LoadScene2();
	void GoldRushLost();//In this mini-game we always, eventually, lose.

	//Utility functions
	void InsertEntity(BaseEntity* entity);
	void RemoveEntity(BaseEntity* entity);
	void RemoveAt(int index);
	void RemoveAllEntities();
	bool ContainsEntity(BaseEntity* entity);
	bool ContainsEntity(BaseEntity* entity, int& index);
	Wife * GetWife();
	Miner * GetMiner();

	//Variables
	ID3D11Device1 * m_device;
	//Current viewport
	D3D11_VIEWPORT m_currentViewport;
	//SpriteBatch drawer (Begin() and End())
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	std::vector <BaseEntity*> m_entities;
};