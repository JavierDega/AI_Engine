#include "pch.h"
#include "..\Headers\ClickerButton.h"
#include "GameScene.h"

using namespace DirectX;
using namespace SimpleMath;

ClickerButton::ClickerButton(ButtonType type, float leftRect, float rightRect, float topRect, float bottomRect, unsigned int clickIterator)
	: UIButton(type, leftRect, rightRect, topRect, bottomRect), m_clickIterator(clickIterator), m_clicks(0)
{

}


ClickerButton::~ClickerButton()
{
	m_font.reset();
}

void ClickerButton::Initialize(ID3D11Device1 * device, const wchar_t * fileName)
{
	//Load texture
	DX::ThrowIfFailed(
		CreateDDSTextureFromFile(device, fileName, nullptr, m_texture.ReleaseAndGetAddressOf())
	);

	//@Font
	m_font = std::make_unique<SpriteFont>(device, L"Textures/myfile.spritefont");
}

void ClickerButton::Render(DirectX::SpriteBatch * spriteBatch)
{
	UIEntity::Render(spriteBatch);
	//@Now draw font
	std::wstring m_text = L" " + std::to_wstring(m_clicks) + L" / " + std::to_wstring(m_clickIterator);
	const wchar_t * output = m_text.c_str();
	Vector2 m_fontPos = Vector2(m_UIRect.right, m_UIRect.top + (m_UIRect.bottom - m_UIRect.top)/2 );
	Vector2 origin = m_font->MeasureString(output) / 2.f;

	m_font->DrawString(spriteBatch, output,
		m_fontPos);
}

bool ClickerButton::QueryClick(ID3D11Device1 * device, int mX, int mY)
{
	//Then we compare to see if the mouse's position is inside the UIButton's Rect.
	if ((mX < m_UIRect.right && mX > m_UIRect.left) && (mY > m_UIRect.top && mY < m_UIRect.bottom)) {
		//Clicked
		m_clicks++;
		if (m_clicks == m_clickIterator) {
			m_clicks = 0;
			switch (m_type) {
			case ButtonType::INCREASEGOLD:
				GoldButton();
				break;
			case ButtonType::INCREASECOOK:
				CookButton();
				break;
			}
		}
		return true;
	}
	return false;
}

void ClickerButton::GoldButton()
{
	//@Cookie clicker, increase iterator for gold
	GameScene::GetInstance()->GetMiner()->m_bankedGold++;
}

void ClickerButton::CookButton()
{
		GameScene::GetInstance()->GetWife()->m_cookState++;
}
