#pragma once
#include <d3d11.h>

class Texture
{
public:
	Texture(LPCSTR filepath);

	bool init(ID3D11Device* pDevice);
	void deInit();

	ID3D11ShaderResourceView* getTexture() { return _pTexture; }
	ID3D11SamplerState* getSampler() { return _pSampler; }

private:
	bool createTexture(ID3D11Device* pDevice);
	bool createSampler(ID3D11Device* pDevice);

	ID3D11ShaderResourceView* _pTexture = nullptr;
	ID3D11SamplerState* _pSampler = nullptr;

	LPCSTR _filepath = "";
};

