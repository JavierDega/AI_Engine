#pragma once
#include "UIEntity.h"

//Type id (Helps searching through GameScene vector)
enum class ButtonType {
	LOADSCENE1,
	LOADSCENE2,
	LOADMENU,
	INCREASEGOLD,
	INCREASECOOK
};
//@Interactable buttons, utilizing Types Enum to determine OnClick functionality.
class UIButton :
	public UIEntity
{
public:
	UIButton(ButtonType type, float leftRect, float rightRect, float topRect, float bottomRect);
	virtual ~UIButton();
	virtual void Initialize(ID3D11Device1 * device, const wchar_t * fileName = L"Textures/uibutton.dds");
	ButtonType GetType();
	virtual bool QueryClick( int mX, int mY);
	//Utility

	//Variables
	ButtonType m_type;

};
