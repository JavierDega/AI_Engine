#pragma once
#include "UIButton.h"

//@Iterator and maxClicks, once maxClicks is reached, action takes place
class ClickerButton :
	public UIButton
{
public:
	ClickerButton(ButtonType type, float leftRect, float rightRect, float topRect, float bottomRect, unsigned int clickIterator = 1);
	virtual ~ClickerButton();
	virtual void Initialize(ID3D11Device1 * device, const wchar_t * fileName)override;
	//@We need to render font to the right of RECT
	virtual void Render(DirectX::SpriteBatch * spriteBatch)override;
	//Utility
	virtual bool QueryClick( int mX, int mY)override;
	void GoldButton();
	void CookButton();

	//Variables
	unsigned int m_clicks, m_clickIterator;
	//@Font indicating n of current clicks
	std::unique_ptr<DirectX::SpriteFont> m_font;
};
