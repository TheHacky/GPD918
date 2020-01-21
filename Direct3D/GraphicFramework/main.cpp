#include <Windows.h>
#include "System.h"

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR szCmdLine, _In_ int nCmdShow)
{
	System sys = {};
	if (sys.init(hInstance, 1280, 720, nCmdShow, false, false))
	{
		sys.run();
	}

	sys.deInit();

	return 0;
}