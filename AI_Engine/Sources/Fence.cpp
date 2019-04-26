#include "pch.h"
#include "..\Headers\Fence.h"
#include "GameScene.h"

using namespace DirectX;
using namespace SimpleMath;

Fence::Fence(DirectX::SimpleMath::Vector2 screenPos, float speed, float layerDepth):
	GameEntity(screenPos, layerDepth), m_scrollSpeed(speed)
{
}

Fence::~Fence()
{
}

void Fence::Initialize(ID3D11Device1 * device, const wchar_t * fileName)
{
	GameEntity::Initialize(device, fileName);
}

void Fence::Render(DirectX::SpriteBatch * spriteBatch)
{
	spriteBatch->Draw(m_texture.Get(), m_screenPos, nullptr, Colors::White, 0.0f, m_origin, Vector2(1, 1), SpriteEffects_None, m_layerDepth);
}

void Fence::Update(float elapsedTime)
{
	//@Move up on the y (down) by m_speed, disappear when at the top
	m_screenPos.y += m_scrollSpeed * elapsedTime;

	//@Collision query
	GameScene * gs = GameScene::GetInstance();
	for (int i = 0; i < gs->m_entities.size(); i++) {
		SteeringEntity * otherCar = dynamic_cast<SteeringEntity*>(gs->m_entities[i]);
		if (otherCar) {
			//@AABB Check?
			if (abs(m_screenPos.x - otherCar->m_screenPos.x) > 120) {
				continue;
			}
			if (abs(m_screenPos.y - otherCar->m_screenPos.y) > 108) {
				continue;
			}
			//@At this point they must collide
			if (otherCar->m_type == SteeringType::PLAYER_CAR) gs->CityChaseLost();//@We just crashed into a fence
			else otherCar->m_isDeleted = true;
		}
	}
	//@Disappear
	if (m_screenPos.y > 1080.f) m_isDeleted = true;
}
