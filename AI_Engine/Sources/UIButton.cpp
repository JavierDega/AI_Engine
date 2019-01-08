#include "pch.h"
#include "..\Headers\UIButton.h"

#include "GameScene.h"
using namespace DirectX;

UIButton::UIButton()
{
}

UIButton::UIButton(ID3D11Device1 * device)
{
	//Default?
	Initialize(device, L"Textures/fsmbutton.dds", ButtonType::LOADMENU , 0.25, 0.75, 0.25, 0.75);
}

UIButton::~UIButton()
{
	bool debug;
}

void UIButton::Initialize(ID3D11Device1 * device, const wchar_t * filename, ButtonType type, float leftRect, float rightRect, float topRect, float bottomRect) {

	//Load texture
	DX::ThrowIfFailed(
		CreateDDSTextureFromFile(device, filename, nullptr, m_texture.ReleaseAndGetAddressOf())
	);
	m_type = type;
	m_leftRect = leftRect;
	m_topRect = topRect;
	m_rightRect = rightRect;
	m_bottomRect = bottomRect;
}


ButtonType UIButton::GetType()
{
	return m_type;
}

//@Unfinished: To define functions for each specific buttonType enum.
bool UIButton::QueryClick(ID3D11Device1 * device, int mX, int mY)
{
	//Then we compare to see if the mouse's position is inside the UIButton's Rect.
	if ((mX < m_UIRect.right && mX > m_UIRect.left) && (mY > m_UIRect.top && mY < m_UIRect.bottom)) {
		//Clicked
		switch (m_type) {
		case ButtonType::LOADMENU:
			GameScene::GetInstance()->LoadStartMenu(device);
			break;
		case ButtonType::LOADSCENE1:
			GameScene::GetInstance()->LoadScene1(device);
			break;
		}
		return true;
	}
	return false;
}