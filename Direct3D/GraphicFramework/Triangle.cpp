#include "Triangle.h"

void Triangle::initVertexData()
{
	float halfH = static_cast<float>(sqrt(0.75)) * 0.5f;
	_vertexCount = 3;
	_pVertexData = new Vertex[_vertexCount]{
		Vertex(-0.5f, -halfH, 0.0f, 1.0f, 0.0f, 0.0f),
		Vertex(0.0f, halfH, 0.0f, 0.0f, 1.0f, 0.0f),
		Vertex(0.5f, -halfH, 0.0f, 0.0f, 0.0f, 1.0f)
	};
}

void Triangle::initIndexData()
{
	_indexCount = 3;
	_pIndexData = new UINT[_indexCount]{
		0, 1, 2
	};
}
