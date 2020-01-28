#pragma once
#include "TextureShader.h"

class LightingShader :
	public TextureShader
{
public:
	LightingShader();

	bool init(ID3D11Device* pDevice); 
	
	void setMatrixBufferValues(ID3D11DeviceContext* pDeviceContext, void** values); 
	void setShaderResources(ID3D11DeviceContext* pDeviceContext, void** values);

private:
	struct LightMatrixBuffer
	{
		XMFLOAT4X4 worldMatrix;
		XMFLOAT4X4 worldViewProjectionMatrix;
		XMFLOAT4 tilingOffset;
		XMFLOAT3 cameraWorldPosition;
		FLOAT dummy;
	};

	struct LightBuffer
	{							
		XMFLOAT4 ambientLight; 
		XMFLOAT3 lightVector; 
		FLOAT lightIntensity; 
		XMFLOAT4 lightColor; 
	};

	bool initLightBuffer(ID3D11Device* pDevice);

	ID3D11Buffer* _pLightBuffer = nullptr;
};

