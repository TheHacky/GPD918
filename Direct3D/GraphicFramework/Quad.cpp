#include "Quad.h"

void Quad::initVertexData()
{
	_vertexCount = 4;
	_pVertexData = new Vertex[_vertexCount]{
		Vertex(-0.5f, 0.5f, 0.0f, 0.0f, 0.0f), // 0
		Vertex(0.5f, 0.5f, 0.0f, 1.0f, 0.0f), // 1
		Vertex(0.5f, -0.5f, 0.0f, 1.0f, 1.0f), // 2
		Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 1.0f) // 3
	};
}

void Quad::initIndexData()
{
	_indexCount = 6;
	_pIndexData = new UINT[_indexCount]{
		0, 1, 2,
		0, 2, 3
	};
}
