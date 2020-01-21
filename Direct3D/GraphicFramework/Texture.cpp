#include "Texture.h"
#include <cfloat>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(LPCSTR filepath) : _filepath(filepath)
{
}

bool Texture::init(ID3D11Device* pDevice)
{
	return createTexture(pDevice) && createSampler(pDevice);
}

void Texture::deInit()
{
	_pSampler->Release();
	_pSampler = nullptr;

	_pTexture->Release();
	_pTexture = nullptr;
}

bool Texture::createTexture(ID3D11Device* pDevice)
{
	// 1. load pixel data from harddisk
	int width = 0;
	int height = 0;
	int channels = 0;

	stbi_uc* pixels = nullptr;

	pixels = stbi_load(_filepath, &width, &height, &channels, 4);
	if (pixels == nullptr || width == 0 || height == 0 || channels == 0) return false;

	// 2. create texture object
	ID3D11Texture2D* pTexture = nullptr;
	D3D11_TEXTURE2D_DESC desc = {};
	desc.ArraySize = 1;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.SampleDesc.Count = 1;

	D3D11_SUBRESOURCE_DATA data = {};
	data.pSysMem = pixels;
	data.SysMemPitch = sizeof(stbi_uc) * 4 * width;

	HRESULT hr = pDevice->CreateTexture2D(&desc, &data, &pTexture);
	if (FAILED(hr)) return false;

	// 3. create shader resource view
	pDevice->CreateShaderResourceView(pTexture, nullptr, &_pTexture);
	if (FAILED(hr)) return false;

	pTexture->Release();
	pTexture = nullptr;

	stbi_image_free(pixels);

	return true;
}

bool Texture::createSampler(ID3D11Device* pDevice)
{
	D3D11_SAMPLER_DESC desc = {};
	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.BorderColor[0] = 1.0f;
	desc.BorderColor[1] = 0.0f;
	desc.BorderColor[2] = 1.0f;
	desc.BorderColor[3] = 1.0f;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	desc.MinLOD = FLT_MIN;
	desc.MaxLOD = FLT_MAX;

	return SUCCEEDED(pDevice->CreateSamplerState(&desc, &_pSampler));
}
