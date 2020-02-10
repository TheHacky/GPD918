#include "LightingShader.h"
#include "Texture.h"

LightingShader::LightingShader()
{
	_vertexShaderFilename = TEXT("LightingVertexShader.hlsl");
	_pixelShaderFilename = TEXT("LightingPixelShader.hlsl");
	_matrixBufferSize = sizeof(LightMatrixBuffer);
}

bool LightingShader::init(ID3D11Device* pDevice)
{
	return TextureShader::init(pDevice) && initLightBuffer(pDevice);
}

void LightingShader::setMatrixBufferValues(ID3D11DeviceContext* pDeviceContext, void** values)
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
	LightMatrixBuffer* pBuffer = reinterpret_cast<LightMatrixBuffer*>(tmpMap.pData);
	XMStoreFloat4x4(&pBuffer->worldMatrix, XMMatrixTranspose(worldMatrix));
	XMStoreFloat4x4(&pBuffer->worldViewProjectionMatrix, wvpMatrix);
	pBuffer->tilingOffset = *reinterpret_cast<XMFLOAT4*>(values[3]);
	pBuffer->cameraWorldPosition = *reinterpret_cast<XMFLOAT3*>(values[4]);

	// unmap resource to write back data to video memory
	pDeviceContext->Unmap(_pMatrixBuffer, 0);
}

void LightingShader::setShaderResources(ID3D11DeviceContext* pDeviceContext, void** values)
{
	TextureShader::setShaderResources(pDeviceContext, values);

	// map video memory of constant buffer onto normal memory
	D3D11_MAPPED_SUBRESOURCE tmpMap = {};
	pDeviceContext->Map(_pLightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &tmpMap);

	// store data in memory
	LightBuffer* pBuffer = reinterpret_cast<LightBuffer*>(tmpMap.pData);
	pBuffer->ambientLight = { 0.1f, 0.1f, 0.1f, 1.0f };
	pBuffer->lightColor = { 0.7f, 0.7f, 0.7f, 1.0f };
	pBuffer->lightIntensity = 5.0f;
	XMStoreFloat3(&pBuffer->lightVector, XMVector3Normalize(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f)));
	pBuffer->lightPosition = { 0.0f, 0.0f, -0.7f };
	pBuffer->lightRange = 10.0f;
	pBuffer->lightForward = { 0.0f, 0.0f, 1.0f };
	pBuffer->lightAngle = cosf(XM_PIDIV4);
	pBuffer->type = 0;

	// unmap resource to write back data to video memory
	pDeviceContext->Unmap(_pLightBuffer, 0);

	// set constant buffer on pipeline
	pDeviceContext->PSSetConstantBuffers(0, 1, &_pLightBuffer);

	// set normal map
	Texture* pNormalMap = reinterpret_cast<Texture*>(values[1]);
	ID3D11ShaderResourceView* normalMaps[] = { pNormalMap->getTexture() };
	pDeviceContext->PSSetShaderResources(1, 1, normalMaps);
}

bool LightingShader::initLightBuffer(ID3D11Device* pDevice)
{
	D3D11_BUFFER_DESC desc = {};
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.ByteWidth = sizeof(LightBuffer);
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	return SUCCEEDED(pDevice->CreateBuffer(&desc, nullptr, &_pLightBuffer));
}
