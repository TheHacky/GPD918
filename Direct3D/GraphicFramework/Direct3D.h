#pragma once
#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

class Direct3D
{
public:
	bool init(HWND hWnd, UINT screenWidth, UINT screenHeight, BOOL isFullscreen, BOOL isVsyncEnabled);
	void beginScene(FLOAT red, FLOAT green, FLOAT blue);
	void endScene();
	void deInit();

	ID3D11Device* getDevice() { return _pDevice; }
	ID3D11DeviceContext* getDeviceContext() { return _pDeviceContext; }

private:
	bool getOutputRefreshRate(UINT screenWidth, UINT screenHeight);
	bool initDevice(HWND hWnd, UINT screenWidth, UINT screenHeight, BOOL isFullscreen, BOOL isVsyncEnabled);
	bool initRenderTargetView();
	bool initDepthStencilView(UINT screenWidth, UINT screenHeight);
	bool initRasterizerState();
	bool setTarget(UINT screenWidth, UINT screenHeight);

	ID3D11Device*			_pDevice			= nullptr;
	ID3D11DeviceContext*	_pDeviceContext		= nullptr;
	IDXGISwapChain*			_pSwapChain			= nullptr;
	ID3D11RenderTargetView* _pRenderTargetView	= nullptr;
	ID3D11DepthStencilView* _pDepthStencilView = nullptr;
	ID3D11DepthStencilState* _pDepthStencilState = nullptr;
	ID3D11RasterizerState* _pRasterizerState = nullptr;

	DXGI_RATIONAL _refreshRate = {};
	bool _isVsyncEnabled = false;

	const DXGI_FORMAT PIXEL_FORMAT = DXGI_FORMAT_R8G8B8A8_UNORM;
};

