#include "GfxSystem.h"

bool GfxSystem::init(HWND hWnd, UINT screenWidth, UINT screenHeight, BOOL isFullscreen, BOOL isVsyncEnabled)
{
	_pD3D = new Direct3D();

	return _pD3D->init(hWnd, screenWidth, screenHeight, isFullscreen, isVsyncEnabled);
}

void GfxSystem::update()
{
}

void GfxSystem::render()
{
	_pD3D->beginScene();

	//TODO: render stuff

	_pD3D->endScene();
}

void GfxSystem::deInit()
{
	_pD3D->deInit();
	delete _pD3D;
	_pD3D = nullptr;
}
