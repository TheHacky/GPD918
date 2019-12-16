#include <Windows.h>

// Window Proc
LRESULT CALLBACK WndProc(
	HWND hWnd, // handle to window instance
	UINT msg, // message code
	WPARAM wParam, // additional information (normally one information)
	LPARAM lParam // additional information (normally many information as bitmask)
)
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

// ANSI version
//int WINAPI WinMain(
//	HINSTANCE hInstance, // handle to own application
//	HINSTANCE hPrevInstance, // deprecated
//	LPSTR lpCmdLine, // command line
//	int nCmdShow // normal window, maximised, minimised
//)

// UNICODE version
int WINAPI wWinMain(
	_In_ HINSTANCE hInstance, // handle to own application
	_In_opt_ HINSTANCE hPrevInstance, // deprecated
	_In_ LPWSTR lpCmdLine, // command line
	_In_ int nCmdShow // normal window, maximised, minimised
)
{
	// 1. describe window class
	WNDCLASS wc = {};
	wc.hInstance = hInstance; // handle to application instance
	wc.lpszClassName = TEXT("First Window"); // class name (I used title for that)
	wc.lpfnWndProc = WndProc; // function for communication with operating system
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; // window behaviour
	wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BACKGROUND); // system color
	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)); // solid color
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION); // load system icon
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW); // load system cursor

	// 2. register window class
	if (RegisterClass(&wc) == 0) return 10;

	// 3. define window position and size (optional)
	DWORD style = WS_OVERLAPPEDWINDOW;
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	int halfWidth = width / 2;
	int halfHeight = height / 2;
	int screenWidth = 1280;
	int screenHeight = 720;
	int halfScreenWidth = screenWidth / 2;
	int halfScreenHeight = screenHeight / 2;
	RECT r = { halfWidth - halfScreenWidth, halfHeight - halfScreenHeight, halfWidth + halfScreenWidth, halfHeight + halfScreenHeight };
	AdjustWindowRect(&r, style, false);

	// 4. create window instance
	HWND hWnd = CreateWindow(
		wc.lpszClassName, // name of window class to instantiate
		wc.lpszClassName, // title of window
		style, // style of window
		r.left, r.top, // window position
		r.right - r.left, r.bottom - r.top, // window size
		nullptr, // handle to parent window
		nullptr, // handle to menu instance
		hInstance, // handle to application instance
		nullptr, // optional paramter
		);

	if (!hWnd) return 11;


	// 5. show and set focus for window instance
	ShowWindow(hWnd, nCmdShow);
	SetFocus(hWnd);

	// 6. run an application loop and evaluating of window messages
	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, UINT_MAX, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		Sleep(10);
	}

	return 0;
}