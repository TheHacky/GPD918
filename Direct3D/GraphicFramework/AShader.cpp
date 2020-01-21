#include "AShader.h"
#include <d3dcompiler.h>

AShader::AShader()
{
	_matrixBufferSize = sizeof(MatrixBuffer);
}

bool AShader::init(ID3D11Device* pDevice)
{
	return initVertexShader(pDevice) && initPixelShader(pDevice) && initMatrixBuffer(pDevice);
}

void AShader::render(ID3D11DeviceContext* pDeviceContext, UINT indexCount)
{
	// set up render pipeline stages
	pDeviceContext->IASetInputLayout(_pInputLayout);
	pDeviceContext->VSSetShader(_pVertexShader, nullptr, 0);
	pDeviceContext->PSSetShader(_pPixelShader, nullptr, 0);

	// set values
	pDeviceContext->VSSetConstantBuffers(0, 1, &_pMatrixBuffer);

	// render
	pDeviceContext->DrawIndexed(indexCount, 0, 0);
}

void AShader::deInit()
{
	_pMatrixBuffer->Release();
	_pMatrixBuffer = nullptr;

	_pInputLayout->Release();
	_pInputLayout = nullptr;

	_pPixelShader->Release();
	_pPixelShader = nullptr;

	_pVertexShader->Release();
	_pVertexShader = nullptr;
}

void AShader::setMatrixBufferValues(ID3D11DeviceContext* pDeviceContext, void** values)
{
	// map video memory of constant buffer onto normal memory
	D3D11_MAPPED_SUBRESOURCE tmpMap = {};
	pDeviceContext->Map(_pMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &tmpMap);

	// calculate world-view-projection-matrix
	XMMATRIX worldMatrix = XMLoadFloat4x4(reinterpret_cast<XMFLOAT4X4*>(values[0]));
	XMMATRIX viewMatrix = XMLoadFloat4x4(reinterpret_cast<XMFLOAT4X4*>(values[1]));
	XMMATRIX projectionMatrix = XMLoadFloat4x4(reinterpret_cast<XMFLOAT4X4*>(values[2]));
	XMMATRIX wvpMatrix = worldMatrix * viewMatrix * projectionMatrix;

	// transpose matrix, because gpu work with column major
	wvpMatrix = XMMatrixTranspose(wvpMatrix);

	// store data in memory
	MatrixBuffer* pBuffer = reinterpret_cast<MatrixBuffer*>(tmpMap.pData);
	XMStoreFloat4x4(&pBuffer->worldViewProjectionMatrix, wvpMatrix);
	pBuffer->tilingOffset = *reinterpret_cast<XMFLOAT4*>(values[3]);

	// unmap resource to write back data to video memory
	pDeviceContext->Unmap(_pMatrixBuffer, 0);
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

	D3D11_INPUT_ELEMENT_DESC desc[3] = {};
	
	// POSITION
	desc[0].SemanticName = "POSITION";
	desc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;

	// COLOR
	desc[1].SemanticName = "COLOR";
	desc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	desc[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	// UV
	desc[2].SemanticName = "TEXCOORD";
	desc[2].Format = DXGI_FORMAT_R32G32_FLOAT;
	desc[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	HRESULT hr = pDevice->CreateInputLayout(desc, 3, pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &_pInputLayout);

	if (FAILED(hr)) return false;

	return true;
}

bool AShader::initMatrixBuffer(ID3D11Device* pDevice)
{
	D3D11_BUFFER_DESC desc = {};
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.ByteWidth = _matrixBufferSize;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	return SUCCEEDED(pDevice->CreateBuffer(&desc, nullptr, &_pMatrixBuffer));
}
