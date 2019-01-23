#pragma once
#include <vector>
#include "BaseEntity.h"


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
	~GameScene(void);
	//Game events
	void Initialize(ID3D11Device1* device, ID3D11DeviceContext1 * deviceContext);
	void InitWindow(D3D11_VIEWPORT newScreenViewport);
	void Update(float elapsedTime);
	void Render();
	void Reset();
	//Load
	void LoadStartMenu(ID3D11Device1* device);
	void LoadScene1(ID3D11Device1* device);

	//Utility functions
	void InsertEntity(BaseEntity* entity);
	void RemoveEntity(BaseEntity* entity);
	void RemoveAllEntities();
	bool ContainsEntity(BaseEntity* entity);
	bool ContainsEntity(BaseEntity* entity, int& index);
	//Singleton
	static GameScene* GetInstance();

	//Variables
	//Current viewport
	D3D11_VIEWPORT m_currentViewport;
	//SpriteBatch drawer (Begin() and End())
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	std::vector <BaseEntity*> m_entities;
};