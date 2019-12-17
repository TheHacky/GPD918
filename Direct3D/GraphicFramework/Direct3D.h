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
	bool getOutputRefreshRate(UINT screenWidth, UINT screenHeight);
	bool initDevice(HWND hWnd, UINT screenWidth, UINT screenHeight, BOOL isFullscreen, BOOL isVsyncEnabled);

	ID3D11Device*			_pDevice		= nullptr;
	ID3D11DeviceContext*	_pDeviceContext = nullptr;
	IDXGISwapChain*			_pSwapChain		= nullptr;

	DXGI_RATIONAL _refreshRate = {};

	const DXGI_FORMAT PIXEL_FORMAT = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
};

