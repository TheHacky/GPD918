#pragma once
#include <DirectXMath.h> // SIMD (Single Instruction Multiple Data) compatible

using namespace DirectX;

struct Vertex
{
	XMFLOAT3 position;

	Vertex(float x, float y, float z) : position(x, y, z) {}
};