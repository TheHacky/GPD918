#pragma once
#include <DirectXMath.h>
#include <Windows.h>

using namespace DirectX;

class Camera
{
public:
	bool init(UINT screenWidth, UINT screenHeight);
	void update();
	void deInit();

	XMFLOAT4X4 getViewMatrix() { return _viewMatrix; }
	XMFLOAT4X4 getProjectionMatrix() { return _projectionMatrix; }
	XMFLOAT3 getPosition() { return _position; }

	void move(FXMVECTOR vector);
	void rotate(FXMVECTOR euler);

private:
	XMFLOAT4X4 _viewMatrix;
	XMFLOAT4X4 _projectionMatrix;

	XMFLOAT3 _position = { 0.0f, 0.0f, 0.0f };
	XMFLOAT4 _rotation = { 0.0f, 0.0f, 0.0f, 1.0f };
};

