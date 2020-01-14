#include "System.h"
#include "Direct3D.h"
#include <sstream>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) DestroyWindow(hWnd);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool System::init(HINSTANCE hInstance, UINT screenWidth, UINT screenHeight, int nCmdShow, bool isFullscreen, bool isVsyncEnabled)
{
	if (!initWindow(hInstance, screenWidth, screenHeight, nCmdShow)) return false;

	_pGfxSystem = new GfxSystem();
	if (!_pGfxSystem->init(_hWnd, screenWidth, screenHeight, isFullscreen, isVsyncEnabled)) return false;

	if (!initHighFrequencyTimer()) return false;

	return true;
}

void System::run()
{
	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, UINT_MAX, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		updateHighFrequencyTimer();

		_pGfxSystem->update(_deltaTime);
		_pGfxSystem->render();
	}
}

void System::deInit()
{
	_pGfxSystem->deInit();
	delete _pGfxSystem;
	_pGfxSystem = nullptr;

	DestroyWindow(_hWnd);
}

bool System::initWindow(HINSTANCE hInstance, UINT screenWidth, UINT screenHeight, int nCmdShow)
{
	WNDCLASS wc = {};
	wc.hInstance = hInstance;
	wc.lpszClassName = TEXT("Direct3D Project");
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

	if (RegisterClass(&wc) == 0) return false;

	DWORD style = WS_OVERLAPPEDWINDOW;
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	int halfWidth = width / 2;
	int halfHeight = height / 2;
	int halfScreenWidth = screenWidth / 2;
	int halfScreenHeight = screenHeight / 2;
	RECT r = { halfWidth - halfScreenWidth, halfHeight - halfScreenHeight, halfWidth + halfScreenWidth, halfHeight + halfScreenHeight };
	AdjustWindowRect(&r, style, false);

	_hWnd = CreateWindow(
		wc.lpszClassName,
		wc.lpszClassName,
		style,
		r.left, r.top,
		r.right - r.left, r.bottom - r.top,
		nullptr,
		nullptr,
		hInstance,
		nullptr
	);

	if (!_hWnd) return false;

	ShowWindow(_hWnd, nCmdShow);
	SetFocus(_hWnd);

	return true;
}

bool System::initHighFrequencyTimer()
{
	LARGE_INTEGER tmp = {};
	if (!QueryPerformanceFrequency(&tmp)) return false;

	_secondsPerTick = 1.0f / tmp.QuadPart;

	if (!QueryPerformanceCounter(&_lastTickCount)) return false;

	return true;
}

void System::updateHighFrequencyTimer()
{
	LARGE_INTEGER tmp = {};

	QueryPerformanceCounter(&tmp);

	LONGLONG delta = tmp.QuadPart - _lastTickCount.QuadPart;
	_deltaTime = delta * _secondsPerTick;
	_lastTickCount = tmp;

#if UNICODE && _DEBUG
	std::wstringstream wss;
	wss << L"DeltaTime: " << _deltaTime << " // FPS: " << 1.0f / _deltaTime << std::endl;
	OutputDebugString(wss.str().c_str());
#endif // UNICODE

}
