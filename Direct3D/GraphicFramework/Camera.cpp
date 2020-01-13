#include "Camera.h"

bool Camera::init(UINT screenWidth, UINT screenHeight)
{
	XMMATRIX matrix = XMMatrixPerspectiveFovLH(0.3333333f * XM_PI, static_cast<float>(screenWidth) / static_cast<float>(screenHeight), 0.3f, 1000.0f);
	XMStoreFloat4x4(&_projectionMatrix, matrix);

	return true;
}

void Camera::update()
{
	XMVECTOR position = XMVectorSet(0.0f, 0.0f, -1.0f, 1.0f);
	XMVECTOR forward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMMATRIX matrix = XMMatrixLookToLH(position, forward, up);
	XMStoreFloat4x4(&_viewMatrix, matrix);
}

void Camera::deInit()
{
}
