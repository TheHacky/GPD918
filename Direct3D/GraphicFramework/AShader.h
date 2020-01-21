#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;

class AShader
{
public:
	AShader();
	bool init(ID3D11Device* pDevice);
	void render(ID3D11DeviceContext* pDeviceContext, UINT indexCount);
	void deInit();

	virtual void setMatrixBufferValues(ID3D11DeviceContext* pDeviceContext, void** values);
	virtual void setShaderResources(ID3D11DeviceContext* pDeviceContext, void** values) {};

protected:
#if UNICODE
	LPCWSTR _vertexShaderFilename = L"";
	LPCWSTR _pixelShaderFilename = L"";
#else
	LPCSTR _vertexShaderFilename = "";
	LPCSTR _pixelShaderFilename = "";
#endif // UNICODE

	UINT _matrixBufferSize;

private:
	struct MatrixBuffer
	{
		XMFLOAT4X4 worldViewProjectionMatrix;
		XMFLOAT4 tilingOffset;
	};

	bool initVertexShader(ID3D11Device* pDevice);
	bool initPixelShader(ID3D11Device* pDevice);
	bool initInputLayout(ID3D11Device* pDevice, ID3DBlob* pBlob);
	bool initMatrixBuffer(ID3D11Device* pDevice);

	ID3D11VertexShader* _pVertexShader = nullptr;
	ID3D11PixelShader* _pPixelShader = nullptr;
	ID3D11InputLayout* _pInputLayout = nullptr;

	ID3D11Buffer* _pMatrixBuffer = nullptr;

};

