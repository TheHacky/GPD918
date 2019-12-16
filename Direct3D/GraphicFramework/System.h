#pragma once
#include <Windows.h>

class System
{
public:
	bool init(HINSTANCE hInstance, UINT screenWidth, UINT screenHeight, int nCmdShow);
	void run();
	void deInit();

protected:

private:
	bool initWindow(HINSTANCE hInstance, UINT screenWidth, UINT screenHeight, int nCmdShow);

	HWND _hWnd = nullptr;
};
