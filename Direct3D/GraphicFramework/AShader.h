#pragma once
#include <Windows.h>
#include <d3d11.h>

#pragma comment(lib, "d3dcompiler.lib")

class AShader
{
public:
	bool init(ID3D11Device* pDevice);
	void render(ID3D11DeviceContext* pDeviceContext, UINT indexCount);
	void deInit();

protected:
#if UNICODE
	LPCWSTR _vertexShaderFilename = L"";
	LPCWSTR _pixelShaderFilename = L"";
#else
	LPCSTR _vertexShaderFilename = "";
	LPCSTR _pixelShaderFilename = "";
#endif // UNICODE

private:
	bool initVertexShader(ID3D11Device* pDevice);
	bool initPixelShader(ID3D11Device* pDevice);
	bool initInputLayout(ID3D11Device* pDevice, ID3DBlob* pBlob);

	ID3D11VertexShader* _pVertexShader = nullptr;
	ID3D11PixelShader* _pPixelShader = nullptr;
	ID3D11InputLayout* _pInputLayout = nullptr;
};

