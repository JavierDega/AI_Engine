#include "pch.h"
#include "..\Headers\CitySpawner.h"
#include "Fence.h"
#include "SteeringEntity.h"
#include "GameScene.h"

using namespace DirectX;
using namespace SimpleMath;

CitySpawner::CitySpawner()
{
	m_timeSinceLastSpawn = 0;
	m_spawnTimer = 10.f;
}

CitySpawner::~CitySpawner()
{

}

void CitySpawner::Initialize(ID3D11Device1 * device, const wchar_t * fileName)
{
	//@Dont call child's initialize
}

void CitySpawner::InitWindow(D3D11_VIEWPORT newScreenViewport)
{
	//@Do nuthing
}

void CitySpawner::Render(DirectX::SpriteBatch * spriteBatch)
{
	//@Dont draw
}

void CitySpawner::Update(float elapsedTime)
{
	//@Spawn every x time, gradually decrease timer
	m_timeSinceLastSpawn += elapsedTime;
	if (m_timeSinceLastSpawn > m_spawnTimer) {
		m_timeSinceLastSpawn = 0.f;
		m_spawnTimer *= 0.9f;
		m_spawnTimer = std::max(m_spawnTimer, 2.f);
		GameScene * gs = GameScene::GetInstance();
		//@Generate randPos;
		float rand = 360 + (std::rand() % (1560 - 360 + 1));
		Fence * spawnedFence = new Fence( Vector2( rand, 0));
		spawnedFence->Initialize(gs->m_device);
		gs->InsertEntity(spawnedFence);
		
		float rand2 = 360 + (std::rand() % (1560 - 360 + 1));
		SteeringEntity * spawnedCar = new SteeringEntity(Vector2(rand, 1000), std::rand() % (300 - 50 + 1), SteeringType::ENEMY_CAR);
		spawnedCar->Initialize(gs->m_device, L"Textures/car.dds");
		gs->InsertEntity(spawnedCar);
	}
}
