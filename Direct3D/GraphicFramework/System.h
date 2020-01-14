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
	bool initHighFrequencyTimer();
	void updateHighFrequencyTimer();

	HWND _hWnd = nullptr;

	GfxSystem* _pGfxSystem = nullptr;

	LARGE_INTEGER _lastTickCount = {};
	FLOAT _secondsPerTick = 0.0f;
	FLOAT _deltaTime = 0.0f;
};
