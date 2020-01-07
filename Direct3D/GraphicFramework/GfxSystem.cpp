#include "GfxSystem.h"
#include <random>
#include "Triangle.h"
#include "ColorShader.h"

bool GfxSystem::init(HWND hWnd, UINT screenWidth, UINT screenHeight, BOOL isFullscreen, BOOL isVsyncEnabled)
{
	_pD3D = new Direct3D();

	if (!_pD3D->init(hWnd, screenWidth, screenHeight, isFullscreen, isVsyncEnabled)) return false;

	_pMesh = new Triangle();
	if (!_pMesh->init(_pD3D->getDevice())) return false;

	_pShader = new ColorShader();
	if (!_pShader->init(_pD3D->getDevice())) return false;

	return true;
}

void GfxSystem::update()
{
}

void GfxSystem::render()
{
	_pD3D->beginScene(0.0f, 0.0f, 0.0f);

	//// random background colors
	//static std::default_random_engine e;
	//static std::uniform_real_distribution<FLOAT> d(0.0f, 1.0f);

	//_pD3D->beginScene(d(e), d(e), d(e));

	_pMesh->render(_pD3D->getDeviceContext());
	_pShader->render(_pD3D->getDeviceContext(), _pMesh->getIndexCount());
	
	_pD3D->endScene();
}

void GfxSystem::deInit()
{
	delete _pMesh;
	_pMesh = nullptr;

	_pD3D->deInit();
	delete _pD3D;
	_pD3D = nullptr;
}
