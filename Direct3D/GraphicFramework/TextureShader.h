#pragma once
#include "AShader.h"
class TextureShader :
	public AShader
{
public:
	TextureShader();

	void setShaderResources(ID3D11DeviceContext* pDeviceContext, void** values);
};

