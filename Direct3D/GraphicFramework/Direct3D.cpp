#include "Direct3D.h"

bool Direct3D::init(HWND hWnd, UINT screenWidth, UINT screenHeight, BOOL isFullscreen, BOOL isVsyncEnabled)
{
	return initDevice(hWnd, screenWidth, screenHeight, isFullscreen, isVsyncEnabled);
}

void Direct3D::beginScene()
{
}

void Direct3D::endScene()
{
}

void Direct3D::deInit()
{
}

bool Direct3D::initDevice(HWND hWnd, UINT screenWidth, UINT screenHeight, BOOL isFullscreen, BOOL isVsyncEnabled)
{
	// ID3D11Device - used to create other Direct3D object
	// ID3D11DeviceContext - used to render and setup render pipeline
	// IDXGISwapChain - holds front and back buffer and swap them for presentation

	DXGI_SWAP_CHAIN_DESC desc = {};
	desc.BufferCount = 1; // count of back buffer
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // pixel format of back buffer (red, green, blue and alpha with 8bit depth, unsigned, normalized float, sRGB color mode)
	desc.BufferDesc.Width = screenWidth; // back buffer width
	desc.BufferDesc.Height = screenHeight; // back buffer height
	if (isVsyncEnabled)
	{
		// TODO: set refresh rate of output
		desc.BufferDesc.RefreshRate.Denominator = 1;  
		desc.BufferDesc.RefreshRate.Numerator = 0;  
	}
	else
	{
		desc.BufferDesc.RefreshRate.Denominator = 1; // set denominator to 1 because of division with 0
	}
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // type of buffer
	desc.OutputWindow = hWnd; // handle to window ressource
	desc.SampleDesc.Count = 1; // MSAA setup, count at least 1
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // what should happen with front buffer after swapping? (Standard: DXGI_SWAP_EFFECT_DISCARD)
	desc.Windowed = !isFullscreen; // windowed mode yes or no

	D3D_FEATURE_LEVEL supportedFeatureLevels[] = { 
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};

	D3D_FEATURE_LEVEL featureLevel = {};

	HRESULT result = D3D11CreateDeviceAndSwapChain(
		nullptr, // optional - choose an explicit graphic adapter 
		D3D_DRIVER_TYPE_HARDWARE, // renderer driver type (use graphic card or a software renderer)
		nullptr, // only used for D3D_DRIVER_TYPE_SOFTWARE
#ifdef _DEBUG
		D3D11_CREATE_DEVICE_DEBUG, // optional flags, e.g. debug device
#else // _DEBUG
		0,
#endif // _DEBUG
		supportedFeatureLevels, 6, // supported Direct3D versions as array and array count
		D3D11_SDK_VERSION,
		&desc, // DXGI_SWAP_CHAIN_DESC - description structure for creation process
		&_pSwapChain, // pointer pointer to swap chain object
		&_pDevice, // pointer pointer device object
		&featureLevel, // initialised feature level
		&_pDeviceContext // pointer pointer device context object
	);

	if (FAILED(result) || _pDevice == nullptr || _pDeviceContext == nullptr || _pSwapChain == nullptr)
		return false;

	return true;
}
