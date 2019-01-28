#pragma once
//THIS CLASS IS THE BASE FOR ALL UPDATEABLE ENTITIES (DRAWN ON RENDER())

class BaseEntity
{
public:
	BaseEntity(float layerDepth = 1.0f);
	virtual ~BaseEntity();
	//Init, load texture
	virtual void Initialize(ID3D11Device1 * device, const wchar_t * fileName = L"Textures/baseentity.dds");
	//Window init (CreateResources())
	virtual void InitWindow(D3D11_VIEWPORT newScreenViewport) = 0;
	virtual void Render(DirectX::SpriteBatch * spriteBatch);
	virtual void Update(float elapsedTime) = 0;
	//Vars
	//Represents idle texture in animatable entities
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	float m_layerDepth;
};
