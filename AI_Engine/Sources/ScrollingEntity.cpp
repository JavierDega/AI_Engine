#include "pch.h"
#include "..\Headers\ScrollingEntity.h"


using namespace DirectX;
using namespace SimpleMath;

ScrollingEntity::ScrollingEntity(Vector2 screenPos, float speed, float layerDepth)
	: GameEntity(screenPos, layerDepth), m_speed(speed)
{
}


ScrollingEntity::~ScrollingEntity()
{
	m_background.reset();
}

void ScrollingEntity::Initialize(ID3D11Device1 * device, const wchar_t * fileName)
{
	GameEntity::Initialize(device, fileName);
	// Create a ScrollingBackground helper class instance, and set it to our texture
	m_background = std::make_unique<ScrollingBackground>();
	m_background->Load(m_texture.Get());

}
//@Redundant
void ScrollingEntity::InitWindow(D3D11_VIEWPORT newScreenViewport)
{
	//Windows size changed.
	//@Assumption: If we dont do anything , everything will stay as it is, meaning things might become visible once we increase window size, or invisible
	//If we reduce it
	m_background->SetWindow(newScreenViewport.Width, newScreenViewport.Height);
}

void ScrollingEntity::Render(DirectX::SpriteBatch * spriteBatch)
{
	m_background->Draw(spriteBatch);
}

void ScrollingEntity::Update(float elapsedTime)
{
	m_background->Update(elapsedTime*m_speed);
}
