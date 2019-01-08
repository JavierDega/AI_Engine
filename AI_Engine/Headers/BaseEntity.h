#pragma once
//THIS CLASS IS THE BASE FOR ALL UPDATEABLE ENTITIES (DRAWN ON RENDER())

class BaseEntity
{
public:
	BaseEntity();
	//Init, load texture
	BaseEntity(ID3D11Device1* device);
	virtual ~BaseEntity();
	//Window init (CreateResources())
	virtual void InitWindow(D3D11_VIEWPORT newScreenViewport);
	virtual void Render(DirectX::SpriteBatch * spriteBatch);
	virtual void Update(float elapsedTime);
	//Vars
	//Represents idle texture in animatable entities
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
};
