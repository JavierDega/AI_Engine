#include "pch.h"
#include "..\Headers\Input.h"

#include "GameScene.h"
#include "UIButton.h"

extern void ExitGame();

using namespace DirectX;
//Singleton init at compile time
Input* Input::m_instance = NULL;

Input::Input()
{
}


Input::~Input()
{
}

void Input::Initialize(HWND window)
{
	m_keyboard = std::make_unique<Keyboard>();
	m_mouse = std::make_unique<Mouse>();
	m_mouse->SetWindow(window);
}

void Input::UpdateInput(ID3D11Device1* device) {
	//Keyboard and Mouse are singletons
	auto kb = m_keyboard->GetState();
	if (kb.Escape)
	{
		ExitGame();
	}
	auto mouse = m_mouse->GetState();
	m_tracker.Update(mouse);
	//ON CLICK
	if (m_tracker.leftButton  == Mouse::ButtonStateTracker::PRESSED) {
		//Iterate through UI elements to find possible clicked UI Button
		GameScene* gs = GameScene::GetInstance();
		for (unsigned int i = 0; i < gs->m_entities.size(); i++) {
			//Look for entities which can be mouse pressed
			UIButton * button = dynamic_cast<UIButton *>(gs->m_entities[i]);
			if (button) {
				button->QueryClick(device, mouse.x, mouse.y);
			}
		}
	}
}

void Input::Reset()
{
	//Device Lost
	m_tracker.Reset();
}

Input * Input::GetInstance()
{
	//Singleton
	if (m_instance == NULL)
	{
		m_instance = new Input();
	}
	return m_instance;
}
