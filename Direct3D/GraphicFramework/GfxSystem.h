#pragma once
#include "Direct3D.h"

class GfxSystem
{
public:
	bool init(HWND hWnd, UINT screenWidth, UINT screenHeight, BOOL isFullscreen, BOOL isVsyncEnabled);
	void update();
	void render();
	void deInit();

private:
	Direct3D* _pD3D = nullptr;
};