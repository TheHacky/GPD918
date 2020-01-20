#include "TextureShader.h"
#include "Texture.h"

TextureShader::TextureShader()
{
	_vertexShaderFilename = TEXT("TextureVertexShader.hlsl");
	_pixelShaderFilename = TEXT("TexturePixelShader.hlsl");
}

void TextureShader::setShaderResources(ID3D11DeviceContext* pDeviceContext, void** values)
{
	Texture* pTexture = reinterpret_cast<Texture*>(values[0]);

	ID3D11ShaderResourceView* textures[] = { pTexture->getTexture() };
	pDeviceContext->PSSetShaderResources(0, 1, textures);

	ID3D11SamplerState* samplers[] = { pTexture->getSampler() };
	pDeviceContext->PSSetSamplers(0, 1, samplers);
}
