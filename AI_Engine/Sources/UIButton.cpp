#include "pch.h"
#include "..\Headers\UIButton.h"
#include "GameScene.h"

using namespace DirectX;

UIButton::UIButton(ButtonType type, float leftRect, float rightRect, float topRect, float bottomRect)
	: m_type(type), UIEntity(leftRect, rightRect, topRect, bottomRect)
{
}

UIButton::~UIButton()
{
	bool debug;
}

void UIButton::Initialize(ID3D11Device1 * device, const wchar_t * filename) {

	//Load texture
	DX::ThrowIfFailed(
		CreateDDSTextureFromFile(device, filename, nullptr, m_texture.ReleaseAndGetAddressOf())
	);
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

