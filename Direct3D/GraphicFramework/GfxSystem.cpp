#include "GfxSystem.h"
#include <random>

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
	//_pD3D->beginScene(0.0f, 0.0f, 0.0f);

	// random background colors
	static std::default_random_engine e;
	static std::uniform_real_distribution<FLOAT> d(0.0f, 1.0f);

	_pD3D->beginScene(d(e), d(e), d(e));

	//TODO: render stuff

	_pD3D->endScene();
}

void GfxSystem::deInit()
{
	_pD3D->deInit();
	delete _pD3D;
	_pD3D = nullptr;
}
