#include "Cube.h"

void Cube::initVertexData()
{
	_vertexCount = 24;
	_pVertexData = new Vertex[_vertexCount]{
		// front
		Vertex(-0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f), // 0
		Vertex(0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f), // 1
		Vertex(0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f), // 2
		Vertex(-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f), // 3

		// back
		Vertex(0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f), // 4
		Vertex(-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f), // 5
		Vertex(-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f), // 6
		Vertex(0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f), // 7

		// left
		Vertex(-0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f), // 8 (5)
		Vertex(-0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f), // 9 (0)
		Vertex(-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f), // 10 (3)
		Vertex(-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f), // 11 (6)

		// right
		Vertex(0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f), // 12 (1)
		Vertex(0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f), // 13 (4)
		Vertex(0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f), // 14 (7)
		Vertex(0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f), // 15 (2)

		// top
		Vertex(-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f), // 16 (5)
		Vertex(0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f), // 17 (4)
		Vertex(0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f), // 18 (1)
		Vertex(-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f), // 19 (0)

		// bottom
		Vertex(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f), // 20 (3)
		Vertex(0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f), // 21 (2)
		Vertex(0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f), // 22 (7)
		Vertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f), // 23 (6)
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
		8, 9, 10,
		8, 10, 11,

		// right
		12, 13, 14, 
		12, 14, 15,

		// top
		16, 17, 18,
		16, 18, 19,

		// bottom
		20, 21, 22,
		20, 22, 23,

	};
}