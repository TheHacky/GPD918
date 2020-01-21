#include "Cube.h"

void Cube::initVertexData()
{
	_vertexCount = 24;
	_pVertexData = new Vertex[_vertexCount]{
		// front
		Vertex(-0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f), // 0
		Vertex(0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f), // 1
		Vertex(0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f), // 2
		Vertex(-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f), // 3

		// back
		Vertex(0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f), // 4
		Vertex(-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f), // 5
		Vertex(-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f), // 6
		Vertex(0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f), // 7
	};
}

void Cube::initIndexData()
{
	_indexCount = 36;
	_pIndexData = new UINT[_indexCount]{
		// front
		0, 1, 2,
		0, 2, 3,

		// back
		4, 5, 6,
		4, 6, 7,

		// left
		5, 0, 3,
		5, 3, 6,

		// right
		1, 4, 7,
		1, 7, 2,

		// top
		5, 4, 1,
		5, 1, 0,

		// bottom
		3, 2, 7,
		3, 7, 6,

	};
}