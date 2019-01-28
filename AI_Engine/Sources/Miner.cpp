#include "pch.h"
#include "Miner.h"
#include "MinerSM.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace Microsoft::WRL;

Miner::Miner(DirectX::SimpleMath::Vector2 screenPos, float layerDepth)
	: AnimatedEntity(screenPos, layerDepth)
{
	//@Note: default constructor wont set attachedCharacter and might cause crashes
	m_text = L"Hello my trusty overlord!";
	m_stateMachine = new MinerSM(this);
	m_gold = 0;
	m_bankedGold = 0;
	m_thirstiness = 0;
	m_hunger = 0;
	m_tiredness = 0;
	m_startMoving = true;
	m_isMoving = false;
	m_fracT = 0;
}

Miner::~Miner()
{
	delete m_stateMachine;
	m_stateMachine = nullptr;
	m_font.reset();
}

void Miner::Initialize(ID3D11Device1 * device)
{
	AnimatedEntity::Initialize(device, L"Textures/mineridle.dds", L"Textures/animatedentitybase.dds", 2, 2);

	//Animated Textures in vector (Ruled by MinerSM enum)
	//Ideally the resurce width and height are the same
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_animTexture;
	DX::ThrowIfFailed(CreateDDSTextureFromFile(device, L"Textures/minermining.dds",
		nullptr, m_animTexture.ReleaseAndGetAddressOf()));
	m_animatedTextures.push_back(m_animTexture);

	DX::ThrowIfFailed(CreateDDSTextureFromFile(device, L"Textures/minerbanking.dds",
		nullptr, m_animTexture.ReleaseAndGetAddressOf()));
	m_animatedTextures.push_back(m_animTexture);

	DX::ThrowIfFailed(CreateDDSTextureFromFile(device, L"Textures/minerresting.dds",
		nullptr, m_animTexture.ReleaseAndGetAddressOf()));
	m_animatedTextures.push_back(m_animTexture);

	DX::ThrowIfFailed(CreateDDSTextureFromFile(device, L"Textures/minerdrinking.dds",
		nullptr, m_animTexture.ReleaseAndGetAddressOf()));
	m_animatedTextures.push_back(m_animTexture);

	DX::ThrowIfFailed(CreateDDSTextureFromFile(device, L"Textures/minerhavingmeal.dds",
		nullptr, m_animTexture.ReleaseAndGetAddressOf()));
	m_animatedTextures.push_back(m_animTexture);

	//@Font
	m_font = std::make_unique<SpriteFont>(device, L"Textures/myfile.spritefont");
	m_animator->Load(m_animatedTextures[1].Get(), 2, 2);
}

void Miner::Update(float elapsedTime)
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
		case MINING_GOLD:
			//Lerp to goal position
			m_screenPos = Vector2::Lerp(m_screenPos, Vector2( 1200, 550 ), m_fracT);
			break;
		case BANKING_GOLD:
			m_screenPos = Vector2::Lerp(m_screenPos, Vector2( 900, 450 ), m_fracT);
			break;
		case RESTING:
			m_screenPos = Vector2::Lerp(m_screenPos, Vector2( 650, 550 ), m_fracT);
			break;
		case DRINKING:
			m_screenPos = Vector2::Lerp(m_screenPos, Vector2( 900, 650 ), m_fracT);
			break;
		case HAVING_MEAL:
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

void Miner::Render(DirectX::SpriteBatch * spriteBatch)
{
	AnimatedEntity::Render(spriteBatch);
	//@Extra: draw font
	const wchar_t * output = m_text.c_str();
	Vector2 m_fontPos = Vector2(m_screenPos.x, m_screenPos.y - 50);
	Vector2 origin = m_font->MeasureString(output) / 2.f;
	
	m_font->DrawString(spriteBatch, output,
		m_fontPos , Colors::White, 0.f, origin);
}
