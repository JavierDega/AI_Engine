#include "pch.h"
#include "..\Headers\CitySpawner.h"
#include "Fence.h"
#include "SteeringEntity.h"
#include "GameScene.h"

using namespace DirectX;
using namespace SimpleMath;
using namespace std;

CitySpawner::CitySpawner()
{
	m_timeSinceLastSpawn = 0;
	m_spawnTimer = 6.f;
	m_score = 0.f;
	m_paused = false;
}

CitySpawner::~CitySpawner()
{
	m_font.reset();
}

void CitySpawner::Initialize(ID3D11Device1 * device, const wchar_t * fileName)
{
	//@Dont call child's initialize
	m_font = std::make_unique<SpriteFont>(device, L"Textures/myfile.spritefont");
}

void CitySpawner::InitWindow(D3D11_VIEWPORT newScreenViewport)
{
	//@Do nuthing
}

void CitySpawner::Render(DirectX::SpriteBatch * spriteBatch)
{
	//@Dont draw
	wstring text = L"Current score: " + to_wstring(m_score);
	const wchar_t * output = text.c_str();
	Vector2 m_fontPos = Vector2(930, 50);
	Vector2 origin = m_font->MeasureString(output) / 2.f;

	m_font->DrawString(spriteBatch, output,
		m_fontPos, (m_paused) ? (Colors::Red) : (Colors::White), 0.f, origin);
}

void CitySpawner::Update(float elapsedTime)
{
	if (m_paused) return;
	m_score += elapsedTime;
	//@Spawn every x time, gradually decrease timer
	m_timeSinceLastSpawn += elapsedTime;
	if (m_timeSinceLastSpawn > m_spawnTimer) {
		m_timeSinceLastSpawn = 0.f;
		m_spawnTimer *= 0.9f;
		m_spawnTimer = std::max(m_spawnTimer, 6.f);
		GameScene * gs = GameScene::GetInstance();
		//@Generate randPos;
		float rand = 360 + (std::rand() % (1560 - 360 + 1));
		Fence * spawnedFence = new Fence( Vector2( rand, 0), 50.f, 0.5f);
		spawnedFence->Initialize(gs->m_device);
		gs->InsertEntity(spawnedFence);
		
		float rand2 = 360 + (std::rand() % (1530 - 360 + 1));//@Avoid overflows reducin the max X range
		SteeringEntity * spawnedCar = new SteeringEntity(Vector2(rand2, 1000), std::rand() % (300 - 100 + 1), SteeringType::ENEMY_CAR, 0.5f);
		spawnedCar->Initialize(gs->m_device, L"Textures/car.dds");
		gs->InsertEntity(spawnedCar);
	}
}
