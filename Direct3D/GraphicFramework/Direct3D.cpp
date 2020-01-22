#include "Direct3D.h"

bool Direct3D::init(HWND hWnd, UINT screenWidth, UINT screenHeight, BOOL isFullscreen, BOOL isVsyncEnabled)
{
	_isVsyncEnabled = isVsyncEnabled && isFullscreen;

	if (_isVsyncEnabled)
	{
		if (!getOutputRefreshRate(screenWidth, screenHeight)) return false;
	}

	if (!initDevice(hWnd, screenWidth, screenHeight, isFullscreen, _isVsyncEnabled)) return false;

	if (!initRenderTargetView()) return false;

	if (!initDepthStencilView(screenWidth, screenHeight)) return false;

	if (!initRasterizerState()) return false;

	if (!setTarget(screenWidth, screenHeight)) return false;

	return true;
}

void Direct3D::beginScene(FLOAT red, FLOAT green, FLOAT blue)
{
	FLOAT color[4] = { red, green, blue, 1.0f };
	_pDeviceContext->ClearRenderTargetView(_pRenderTargetView, color);
	_pDeviceContext->ClearDepthStencilView(_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Direct3D::endScene()
{
	if (_isVsyncEnabled)
		_pSwapChain->Present(1, 0); // vsync enabled, 1 = sync every frame, 2 = sync every second frame, values of 1 - 4
	else
		_pSwapChain->Present(0, 0); // vsync disabled
}

void Direct3D::deInit()
{
	_pRenderTargetView->Release();
	_pRenderTargetView = nullptr;

	_pDevice->Release();
	_pDevice = nullptr;

	_pDeviceContext->Release();
	_pDeviceContext = nullptr;

	_pSwapChain->Release();
	_pSwapChain = nullptr;
}

bool Direct3D::getOutputRefreshRate(UINT screenWidth, UINT screenHeight)
{
	// 1. get graphics factory (object for instantiating graphic card objects)
	IDXGIFactory* pFactory = nullptr;
	HRESULT result = {};

	result = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pFactory));
	if (FAILED(result)) return false;

	// 2. get graphic card adapter
	IDXGIAdapter* pAdapter = nullptr;
	result = pFactory->EnumAdapters(0, &pAdapter); // get a specific adapter (graphic card)
	if (FAILED(result)) return false;

	// 3. get an output of graphic card adapter
	IDXGIOutput* pOutput = nullptr;
	result = pAdapter->EnumOutputs(0, &pOutput); // get a specific output (monitor)
	if (FAILED(result)) return false;

	// 4. get all available display modes
	UINT numModes = 0;
	pOutput->GetDisplayModeList(PIXEL_FORMAT, 0, &numModes, nullptr); // get count of list items

	DXGI_MODE_DESC* desc = new DXGI_MODE_DESC[numModes];
	pOutput->GetDisplayModeList(PIXEL_FORMAT, 0, &numModes, desc); // get list items

	// 5. iterate through display modes and search for our actual desired display mode
	BOOL isFound = false;
	for (UINT i = 0; i < numModes; i++)
	{
		if (desc[i].Width == screenWidth && desc[i].Height == screenHeight)
		{
			_refreshRate = desc[i].RefreshRate;
			isFound = true;
			break;
		}
	}

	// 6. clean up all temporary objects
	// a little unclean because we only release objects if everything run through
	delete[] desc;
	desc = nullptr;

	pOutput->Release(); // we have to call release because it is a COM (Component Object Model) object
	pOutput = nullptr;

	pAdapter->Release();
	pAdapter = nullptr;

	pFactory->Release();
	pFactory = nullptr;

	return isFound;
}

bool Direct3D::initDevice(HWND hWnd, UINT screenWidth, UINT screenHeight, BOOL isFullscreen, BOOL isVsyncEnabled)
{
	// ID3D11Device - used to create other Direct3D object
	// ID3D11DeviceContext - used to render and setup render pipeline
	// IDXGISwapChain - holds front and back buffer and swap them for presentation

	DXGI_SWAP_CHAIN_DESC desc = {};
	desc.BufferCount = 1; // count of back buffer
	desc.BufferDesc.Format = PIXEL_FORMAT; // pixel format of back buffer (red, green, blue and alpha with 8bit depth, unsigned, normalized float, sRGB color mode)
	desc.BufferDesc.Width = screenWidth; // back buffer width
	desc.BufferDesc.Height = screenHeight; // back buffer height
	if (isVsyncEnabled)
	{
		desc.BufferDesc.RefreshRate = _refreshRate;
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

	if (FAILED(result))
		return false;

	return true;
}

bool Direct3D::initRenderTargetView()
{
	ID3D11Texture2D* pBackbuffer = nullptr;
	HRESULT result = _pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackbuffer));
	if (FAILED(result)) return false;

	result = _pDevice->CreateRenderTargetView(pBackbuffer, nullptr, &_pRenderTargetView);
	if (FAILED(result)) return false;

	pBackbuffer->Release();
	pBackbuffer = nullptr;

	return true;
}

bool Direct3D::initDepthStencilView(UINT screenWidth, UINT screenHeight)
{
	ID3D11Texture2D* pTexture = nullptr;
	D3D11_TEXTURE2D_DESC textureDesc = {};
	textureDesc.ArraySize = 1;
	textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	textureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	textureDesc.Width = screenWidth;
	textureDesc.Height = screenHeight;
	textureDesc.MipLevels = 1;
	textureDesc.SampleDesc.Count = 1;

	HRESULT hr = _pDevice->CreateTexture2D(&textureDesc, nullptr, &pTexture);
	if (FAILED(hr)) return false;

	hr = _pDevice->CreateDepthStencilView(pTexture, nullptr, &_pDepthStencilView);
	if (FAILED(hr)) return false;

	pTexture->Release();
	pTexture = nullptr;

	D3D11_DEPTH_STENCIL_DESC depthDesc = {};
	depthDesc.DepthEnable = true;
	depthDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;

	hr = _pDevice->CreateDepthStencilState(&depthDesc, &_pDepthStencilState);
	if (FAILED(hr)) return false;

	return true;
}

bool Direct3D::initRasterizerState()
{
	D3D11_RASTERIZER_DESC desc = {};
	desc.CullMode = D3D11_CULL_BACK;
	desc.FillMode = D3D11_FILL_SOLID;

	return SUCCEEDED(_pDevice->CreateRasterizerState(&desc, &_pRasterizerState));
}

bool Direct3D::setTarget(UINT screenWidth, UINT screenHeight)
{
	_pDeviceContext->OMSetRenderTargets(1, &_pRenderTargetView, _pDepthStencilView); // OM - Output Merger
	_pDeviceContext->OMSetDepthStencilState(_pDepthStencilState, 0);

	D3D11_VIEWPORT viewport = {};
	viewport.Width = static_cast<FLOAT>(screenWidth);
	viewport.Height = static_cast<FLOAT>(screenHeight);
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	_pDeviceContext->RSSetViewports(1, &viewport); // RS - Rasterizer Stage
	_pDeviceContext->RSSetState(_pRasterizerState);

	return true;
}
