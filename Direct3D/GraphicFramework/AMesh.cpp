#include "AMesh.h"

bool AMesh::init(ID3D11Device* pDevice)
{
	initVertexData();
	initIndexData();

	calculateTangentSpace();

	return createBuffers(pDevice);
}

void AMesh::update()
{

	XMMATRIX matrix = XMMatrixTransformation(XMVectorZero(), XMVectorZero(), XMLoadFloat3(&_scale), XMVectorZero(), XMLoadFloat4(&_rotation), XMLoadFloat3(&_position));
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

void AMesh::move(FXMVECTOR vector)
{
	XMVECTOR position = XMLoadFloat3(&_position);
	position += vector;
	XMStoreFloat3(&_position, position);
}

void AMesh::rotate(FXMVECTOR euler)
{
	XMVECTOR rotation = XMLoadFloat4(&_rotation);
	XMVECTOR quaternion = XMQuaternionRotationRollPitchYawFromVector(euler);
	rotation = XMQuaternionMultiply(rotation, quaternion);
	XMStoreFloat4(&_rotation, rotation);
}

void AMesh::scale(FXMVECTOR scale)
{
	XMStoreFloat3(&_scale, scale);
}

void AMesh::calculateTangentSpace()
{
	for (UINT i = 0; i < _indexCount; i += 3)
	{
		UINT iV1 = _pIndexData[i];
		UINT iV2 = _pIndexData[i + 1];
		UINT iV3 = _pIndexData[i + 2];

		Vertex v1 = _pVertexData[iV1];
		Vertex v2 = _pVertexData[iV2];
		Vertex v3 = _pVertexData[iV3];

		XMVECTOR pos1 = XMLoadFloat3(&v1.position);
		XMVECTOR pos2 = XMLoadFloat3(&v2.position);
		XMVECTOR pos3 = XMLoadFloat3(&v3.position);

		XMVECTOR uv1 = XMLoadFloat2(&v1.uv);
		XMVECTOR uv2 = XMLoadFloat2(&v2.uv);
		XMVECTOR uv3 = XMLoadFloat2(&v3.uv);

		XMVECTOR vec1 = pos2 - pos1;
		XMVECTOR vec2 = pos3 - pos1;
		XMVECTOR uvVec1 = uv2 - uv1;
		XMVECTOR uvVec2 = uv3 - uv1;

		XMFLOAT2 uvVec1Store;
		XMStoreFloat2(&uvVec1Store, uvVec1);
		XMFLOAT2 uvVec2Store;
		XMStoreFloat2(&uvVec2Store, uvVec2);

		float div = 1.0f / (uvVec1Store.x * uvVec2Store.y - uvVec1Store.y * uvVec2Store.x);
		XMVECTOR tangent = XMVector3Normalize((vec1 * uvVec2Store.y - vec2 * uvVec1Store.y) * div);
		XMVECTOR binormal = XMVector3Normalize((vec2 * uvVec1Store.x - vec1 * uvVec2Store.x) * div);

		XMStoreFloat3(&_pVertexData[iV1].tangent, tangent);
		XMStoreFloat3(&_pVertexData[iV2].tangent, tangent);
		XMStoreFloat3(&_pVertexData[iV3].tangent, tangent);
		XMStoreFloat3(&_pVertexData[iV1].binormal, binormal);
		XMStoreFloat3(&_pVertexData[iV2].binormal, binormal);
		XMStoreFloat3(&_pVertexData[iV3].binormal, binormal);
	}
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
