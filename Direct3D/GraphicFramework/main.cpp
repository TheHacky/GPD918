#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <Windows.h>
#include "System.h"

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR szCmdLine, _In_ int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	System sys = {};
	if (sys.init(hInstance, 1280, 720, nCmdShow, false, false))
	{
		sys.run();
	}

	sys.deInit();

	_CrtDumpMemoryLeaks();

	return 0;
}