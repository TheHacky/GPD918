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

private:
	XMFLOAT4X4 _viewMatrix;
	XMFLOAT4X4 _projectionMatrix;
};

