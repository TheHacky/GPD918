#include "AShader.h"
#include <d3dcompiler.h>

bool AShader::init(ID3D11Device* pDevice)
{
	return initVertexShader(pDevice) && initPixelShader(pDevice);
}

void AShader::render(ID3D11DeviceContext* pDeviceContext, UINT indexCount)
{
	// set up render pipeline stages
	pDeviceContext->IASetInputLayout(_pInputLayout);
	pDeviceContext->VSSetShader(_pVertexShader, nullptr, 0);
	pDeviceContext->PSSetShader(_pPixelShader, nullptr, 0);

	// render
	pDeviceContext->DrawIndexed(indexCount, 0, 0);
}

void AShader::deInit()
{
	_pInputLayout->Release();
	_pInputLayout = nullptr;

	_pPixelShader->Release();
	_pPixelShader = nullptr;

	_pVertexShader->Release();
	_pVertexShader = nullptr;
}

bool AShader::initVertexShader(ID3D11Device* pDevice)
{
	ID3DBlob* pBlob = nullptr;

	HRESULT hr = D3DCompileFromFile(
		_vertexShaderFilename, // shader filename
		nullptr, // optional, shader macros
		nullptr, // optional, shader includes
		"main", // name of entry point function
		"vs_4_0", // shader type and version
#if _DEBUG
		D3DCOMPILE_DEBUG |
#endif
		D3DCOMPILE_PACK_MATRIX_COLUMN_MAJOR, // optional flags
		0, // optional effect flags
		&pBlob, // target object
		nullptr // optional error object
	);

	if (FAILED(hr)) return false;

	hr = pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &_pVertexShader);

	if (FAILED(hr)) return false;

	if (!initInputLayout(pDevice, pBlob)) return false;

	pBlob->Release();
	pBlob = nullptr;

	return true;
}

bool AShader::initPixelShader(ID3D11Device* pDevice)
{
	ID3DBlob* pBlob = nullptr;

	HRESULT hr = D3DCompileFromFile(_pixelShaderFilename, nullptr, nullptr, "main", "ps_4_0",
#if _DEBUG
		D3DCOMPILE_DEBUG |
#endif
		D3DCOMPILE_PACK_MATRIX_COLUMN_MAJOR, 0, &pBlob, nullptr);

	if (FAILED(hr)) return false;

	hr = pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &_pPixelShader);

	if (FAILED(hr)) return false;

	pBlob->Release();
	pBlob = nullptr;

	return true;
}

bool AShader::initInputLayout(ID3D11Device* pDevice, ID3DBlob* pBlob)
{
	// https://docs.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-semantics

	D3D11_INPUT_ELEMENT_DESC desc = {};
	desc.SemanticName = "POSITION";
	desc.Format = DXGI_FORMAT_R32G32B32_FLOAT;

	HRESULT hr = pDevice->CreateInputLayout(&desc, 1, pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &_pInputLayout);

	if (FAILED(hr)) return false;

	return true;
}
