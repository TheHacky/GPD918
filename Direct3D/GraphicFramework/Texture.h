#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

class Texture
{
public:
	Texture(LPCSTR filepath);

	bool init(ID3D11Device* pDevice);
	void deInit();

	ID3D11ShaderResourceView* getTexture() { return _pTexture; }
	ID3D11SamplerState* getSampler() { return _pSampler; }
	XMFLOAT4 getTilingOffset() { return _tilingOffset; }

private:
	bool createTexture(ID3D11Device* pDevice);
	bool createSampler(ID3D11Device* pDevice);

	ID3D11ShaderResourceView* _pTexture = nullptr;
	ID3D11SamplerState* _pSampler = nullptr;

	LPCSTR _filepath = "";
	XMFLOAT4 _tilingOffset = { 1.0f, 1.0f, 0.0f, 0.0f };
};

