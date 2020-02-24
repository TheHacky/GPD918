#pragma once
#include <Windows.h>
#include "GfxSystem.h"

class System
{
public:
	bool init(HINSTANCE hInstance, UINT screenWidth, UINT screenHeight, int nCmdShow, bool isFullscreen, bool isVsyncEnabled);
	void run();
	void deInit();

	static System* Instance() { if (_pInstance == nullptr) _pInstance = new System(); return _pInstance; }
	void printKey(int key);

protected:

private:
	System();
	static System* _pInstance;

	bool initWindow(HINSTANCE hInstance, UINT screenWidth, UINT screenHeight, int nCmdShow);
	bool initHighFrequencyTimer();
	void updateHighFrequencyTimer();

	HWND _hWnd = nullptr;

	// submodules
	GfxSystem* _pGfxSystem = nullptr;

	LARGE_INTEGER _lastTickCount = {};
	FLOAT _secondsPerTick = 0.0f;
	FLOAT _deltaTime = 0.0f;
};
