#include "AMesh.h"

bool AMesh::init(ID3D11Device* pDevice)
{
	initVertexData();
	initIndexData();

	return createBuffers(pDevice);
}

void AMesh::update()
{

	XMMATRIX matrix = XMMatrixScaling(1.0f, 1.0f, 1.0f) * XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f) * XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	XMStoreFloat4x4(&_worldMatrix, matrix);
}

void AMesh::render(ID3D11DeviceContext* pDeviceContext)
{
	pDeviceContext->IASetVertexBuffers(0, 1, &_pVertexBuffer, &_stride, &_offset); // IA - Input Assembler
	pDeviceContext->IASetIndexBuffer(_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void AMesh::deInit()
{
	_pVertexBuffer->Release();
	_pVertexBuffer = nullptr;

	_pIndexBuffer->Release();
	_pIndexBuffer = nullptr;

	delete[] _pVertexData;
	_pVertexData = nullptr;

	delete[] _pIndexData;
	_pIndexData = nullptr;
}

bool AMesh::createBuffers(ID3D11Device* pDevice)
{
	// Vertexbuffer
	D3D11_BUFFER_DESC desc = {};
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.ByteWidth = _vertexCount * sizeof(Vertex);

	D3D11_SUBRESOURCE_DATA data = {};
	data.pSysMem = _pVertexData;

	HRESULT hr = pDevice->CreateBuffer(&desc, &data, &_pVertexBuffer);
	if (FAILED(hr)) return false;

	// Indexbuffer
	desc = {};
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.ByteWidth = _indexCount * sizeof(UINT);

	data = {};
	data.pSysMem = _pIndexData;

	hr = pDevice->CreateBuffer(&desc, &data, &_pIndexBuffer);
	if (FAILED(hr)) return false;

	return true;
}
