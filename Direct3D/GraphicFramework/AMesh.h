#pragma once
#include <d3d11.h>
#include "Vertex.h"

class AMesh
{
public:
	bool init(ID3D11Device* pDevice);
	void update();
	void render(ID3D11DeviceContext* pDeviceContext);
	void deInit();

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
};

