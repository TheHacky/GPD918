#pragma once
#include "Direct3D.h"
#include "AMesh.h"
#include "AShader.h"
#include "Camera.h"

class GfxSystem
{
public:
	bool init(HWND hWnd, UINT screenWidth, UINT screenHeight, BOOL isFullscreen, BOOL isVsyncEnabled);
	void update();
	void render();
	void deInit();

private:
	Direct3D* _pD3D = nullptr;

	AMesh* _pMesh = nullptr;
	AShader* _pShader = nullptr;
	Camera* _pCamera = nullptr;
};