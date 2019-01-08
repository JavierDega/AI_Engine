#pragma once
#include "UIEntity.h"
#include "GameScene.h"
//Type id (Helps searching through GameScene vector)
enum class ButtonType {
	LOADSCENE1,
	LOADMENU,
};
//Interactable buttons, utilizing Types Enum to determine functionality.
class UIButton :
	public UIEntity
{
public:
	UIButton();
	UIButton(ID3D11Device1 * device);
	~UIButton();
	virtual void Initialize(ID3D11Device1 * device, const wchar_t * filename, ButtonType type, float leftRect, float rightRect, float topRect, float bottomRect);
	ButtonType GetType();
	bool QueryClick(ID3D11Device1 * device, int mX, int mY);
private:
	ButtonType m_type;
};
