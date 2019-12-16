#pragma once
#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

class Direct3D
{
public:
	bool init(HWND hWnd, UINT screenWidth, UINT screenHeight, BOOL isFullscreen, BOOL isVsyncEnabled);
	void beginScene();
	void endScene();
	void deInit();

private:
	bool initDevice(HWND hWnd, UINT screenWidth, UINT screenHeight, BOOL isFullscreen, BOOL isVsyncEnabled);

	ID3D11Device*			_pDevice		= nullptr;
	ID3D11DeviceContext*	_pDeviceContext = nullptr;
	IDXGISwapChain*			_pSwapChain		= nullptr;
};

