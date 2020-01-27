#pragma once
#include <DirectXMath.h> // SIMD (Single Instruction Multiple Data) compatible

using namespace DirectX;

struct Vertex
{
	XMFLOAT3 position;
	XMFLOAT4 color;
	XMFLOAT2 uv;
	XMFLOAT3 normal;

	Vertex(float x, float y, float z) : position(x, y, z), color(1.0f, 1.0f, 1.0f, 1.0f), uv(0.0f, 0.0f), normal(0.0f, 0.0f, 0.0f) {}
	Vertex(float x, float y, float z, float r, float g, float b) : position(x, y, z), color(r, g, b, 1.0f), uv(0.0f, 0.0f), normal(0.0f, 0.0f, 0.0f) {}
	Vertex(float x, float y, float z, float u, float v) : position(x, y, z), color(1.0f, 1.0f, 1.0f, 1.0f), uv(u, v), normal(0.0f, 0.0f, 0.0f) {}
	Vertex(float x, float y, float z, float r, float g, float b, float u, float v) : position(x, y, z), color(r, g, b, 1.0f), uv(u, v), normal(0.0f, 0.0f, 0.0f) {}
	Vertex(XMFLOAT3 pos, XMFLOAT3 nor, XMFLOAT2 tex) : position(pos), color(1.0f, 1.0f, 1.0f, 1.0f), uv(tex), normal(nor) {}
};