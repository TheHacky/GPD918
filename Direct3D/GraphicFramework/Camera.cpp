#include "Camera.h"

bool Camera::init(UINT screenWidth, UINT screenHeight)
{
	XMMATRIX matrix = XMMatrixPerspectiveFovLH(0.3333333f * XM_PI, static_cast<float>(screenWidth) / static_cast<float>(screenHeight), 0.3f, 1000.0f);
	XMStoreFloat4x4(&_projectionMatrix, matrix);

	return true;
}

void Camera::update()
{
	XMVECTOR position = XMLoadFloat3(&_position);
	XMVECTOR rotation = XMLoadFloat4(&_rotation);
	XMVECTOR forward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	forward = XMVector3Rotate(forward, rotation);
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	up = XMVector3Rotate(up, rotation);
	XMMATRIX matrix = XMMatrixLookToLH(position, forward, up);
	XMStoreFloat4x4(&_viewMatrix, matrix);
}

void Camera::deInit()
{
}

void Camera::move(FXMVECTOR vector)
{
	XMVECTOR position = XMLoadFloat3(&_position);
	position += vector;
	XMStoreFloat3(&_position, position);
}

void Camera::rotate(FXMVECTOR euler)
{
	XMVECTOR rotation = XMLoadFloat4(&_rotation);
	XMVECTOR quaternion = XMQuaternionRotationRollPitchYawFromVector(euler);
	rotation = XMQuaternionMultiply(rotation, quaternion);
	XMStoreFloat4(&_rotation, rotation);
}
