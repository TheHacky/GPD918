#pragma once
#include <d3d11.h>
#include "Vertex.h"
#include <DirectXMath.h>

using namespace DirectX;

class AMesh
{
public:
	bool init(ID3D11Device* pDevice);
	void update();
	void render(ID3D11DeviceContext* pDeviceContext);
	void deInit();

	UINT getIndexCount() { return _indexCount; }
	XMFLOAT4X4 getWorldMatrix() { return _worldMatrix; }

protected:
	virtual void initVertexData() = 0;
	virtual void initIndexData() = 0;

	Vertex* _pVertexData = nullptr;
	UINT* _pIndexData = nullptr;
	UINT _vertexCount = 0;
	UINT _indexCount = 0;

private:
	bool createBuffers(ID3D11Device* pDevice);

	ID3D11Buffer* _pVertexBuffer = nullptr;
	ID3D11Buffer* _pIndexBuffer = nullptr;

	UINT _stride = sizeof(Vertex);
	UINT _offset = 0;

	XMFLOAT4X4 _worldMatrix;
};

