#pragma once
#include <Windows.h>
#include "GfxSystem.h"

class System
{
public:
	bool init(HINSTANCE hInstance, UINT screenWidth, UINT screenHeight, int nCmdShow, bool isFullscreen, bool isVsyncEnabled);
	void run();
	void deInit();

protected:

private:
	bool initWindow(HINSTANCE hInstance, UINT screenWidth, UINT screenHeight, int nCmdShow);

	HWND _hWnd = nullptr;

	GfxSystem* _pGfxSystem = nullptr;
};
