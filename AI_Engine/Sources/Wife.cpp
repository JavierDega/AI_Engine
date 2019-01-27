#include "pch.h"
#include "..\Headers\Wife.h"
#include "WifeSM.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace Microsoft::WRL;

Wife::Wife()
{
	//@Note: default constructor wont set attachedCharacter and might cause crashes
	m_text = L"Provide us wealth my lord!";
	m_stateMachine = new WifeSM(this);
	m_cookState = 0;
	m_foodStack = 0;
	m_drinkStack = 0;
}


Wife::~Wife()
{
	delete m_stateMachine;
	m_stateMachine = nullptr;
	m_font.reset();
	m_foodStackTexture.Reset();
}

void Wife::Initialize(ID3D11Device1 * device, DirectX::SimpleMath::Vector2 screenPos, float layerDepth)
{
	//Original idle texture(Not animated)
	ComPtr<ID3D11Resource> resource;
	//Fill m_texture
	DX::ThrowIfFailed(
		CreateDDSTextureFromFile(device, L"Textures/wifeidle.dds",
			resource.GetAddressOf(),
			m_texture.ReleaseAndGetAddressOf())
	);
	DX::ThrowIfFailed(
		CreateDDSTextureFromFile(device, L"Textures/foodStack.dds",
			resource.GetAddressOf(),
			m_foodStackTexture.ReleaseAndGetAddressOf())
	);
	ComPtr<ID3D11Texture2D> tex;
	DX::ThrowIfFailed(resource.As(&tex));

	CD3D11_TEXTURE2D_DESC texDesc;
	tex->GetDesc(&texDesc);

	m_origin.x = float(texDesc.Width / 2);
	m_origin.y = float(texDesc.Height / 2);
	m_screenPos = screenPos;

	//Animated Textures in vector (Ruled by MinerSM enum)
	//Ideally the resurce width and height are the same
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_animTexture;
	DX::ThrowIfFailed(CreateDDSTextureFromFile(device, L"Textures/wifecooking.dds",
		nullptr, m_animTexture.ReleaseAndGetAddressOf()));
	m_animatedTextures.push_back(m_animTexture);

	DX::ThrowIfFailed(CreateDDSTextureFromFile(device, L"Textures/wifedeliveringfood.dds",
		nullptr, m_animTexture.ReleaseAndGetAddressOf()));
	m_animatedTextures.push_back(m_animTexture);

	//All defaults, last argument is layerDepth
	m_animator = std::make_unique<AnimatedTexture>(XMFLOAT2(0, 0), 0.0f, 1.0f, layerDepth);
	m_animator->Load(m_animatedTextures[0].Get(), 2, 2);

	//@Font
	m_font = std::make_unique<SpriteFont>(device, L"Textures/myfile.spritefont");
}

void Wife::Update(float elapsedTime)
{
	AnimatedEntity::Update(elapsedTime);
	//State transitions, state execution
	m_stateMachine->Update(elapsedTime);

	//Movement based on state
	if (m_startMoving) {
		m_startMoving = false;
		m_isMoving = true;
		m_fracT = 0;
		//@Load walking animation
	}

	//Handles state transitions
	if (m_isMoving)
	{
		m_fracT += elapsedTime/m_stateMachine->m_execRate;
		switch (m_stateMachine->m_charState)
		{
		case COOKING:
			//Lerp to goal position
			m_screenPos = Vector2::Lerp(m_screenPos, Vector2(1220, 425), m_fracT);
			break;
		case DELIVERING_FOOD:
			m_screenPos = Vector2::Lerp(m_screenPos, Vector2(1020, 425), m_fracT);
			break;
		}
		//Check that lerp ended
		if (m_fracT >= 1) {
			m_isMoving = false;
			//@Load right animation based on state, here
		}
	}
}

void Wife::Render(DirectX::SpriteBatch * spriteBatch)
{
	AnimatedEntity::Render(spriteBatch);
	//@Optionally, render foodStack
	if (!(m_foodStack + m_drinkStack == 0)) {
		//@m_origin is the same, location is static
		spriteBatch->Draw(m_foodStackTexture.Get(), Vector2 (1020, 425));
	}
	//@Extra: draw font
	const wchar_t * output = m_text.c_str();
	Vector2 m_fontPos = Vector2(m_screenPos.x, m_screenPos.y - 50);
	Vector2 origin = m_font->MeasureString(output) / 2.f;

	m_font->DrawString(spriteBatch, output,
		m_fontPos, Colors::White, 0.f, origin);

}
