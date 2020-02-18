#include "GfxSystem.h"
#include <random>
#include "Triangle.h"
#include "Quad.h"
#include "Cube.h"
#include "ColorShader.h"
#include "TextureShader.h"
#include "LightingShader.h"

bool GfxSystem::init(HWND hWnd, UINT screenWidth, UINT screenHeight, BOOL isFullscreen, BOOL isVsyncEnabled)
{
	_pD3D = new Direct3D();

	if (!_pD3D->init(hWnd, screenWidth, screenHeight, isFullscreen, isVsyncEnabled)) return false;

	_pMesh = new Cube();
	if (!_pMesh->init(_pD3D->getDevice())) return false;
	_pMesh->rotate(XMVectorSet(XM_PIDIV4, 0.0f, 0.0f, 0.0f));

	_pMesh2 = new Cube();
	if (!_pMesh2->init(_pD3D->getDevice())) return false;
	_pMesh2->move(XMVectorSet(0.5f, 0.5f, 0.5f, 0.0f));
	_pMesh2->rotate(XMVectorSet(-XM_PIDIV4, -XM_PIDIV4, 0.0f, 0.0f));

	_pShader = new LightingShader();
	if (!_pShader->init(_pD3D->getDevice())) return false;

	_pCamera = new Camera();
	if (!_pCamera->init(screenWidth, screenHeight)) return false;
	_pCamera->move(XMVectorSet(0.0f, 0.0f, -2.0f, 0.0f));

	_pTexture = new Texture("brick_wall.jpg");
	if (!_pTexture->init(_pD3D->getDevice())) return false;

	_pNormalMap = new Texture("brick_wall_norm.png");
	if (!_pNormalMap->init(_pD3D->getDevice())) return false;

	return true;
}

void GfxSystem::update(FLOAT dt)
{
	_pCamera->update();

	static float scale = 1.0f;
	static float delta = 0.1f;
	if (scale >= 1.0f || scale <= 0.0f) delta *= -1.0f;
	scale += delta * dt;

	_pMesh->rotate(XMVectorSet(0.0f, XM_PIDIV4 * 0.25f, 0.0f, 0.0f) * dt);
	//_pMesh->scale(XMVectorSet(scale, scale, scale, 0.0f));
	_pMesh->update();

	_pMesh2->update();
}

void GfxSystem::render()
{
	_pD3D->beginScene(0.2f, 0.2f, 0.2f);

	//// random background colors
	//static std::default_random_engine e;
	//static std::uniform_real_distribution<FLOAT> d(0.0f, 1.0f);

	//_pD3D->beginScene(d(e), d(e), d(e));

	_pMesh->render(_pD3D->getDeviceContext());

	void* matrices[] = {
		reinterpret_cast<void*>(&_pMesh->getWorldMatrix()),
		reinterpret_cast<void*>(&_pCamera->getViewMatrix()),
		reinterpret_cast<void*>(&_pCamera->getProjectionMatrix()),
		reinterpret_cast<void*>(&_pTexture->getTilingOffset()),
		reinterpret_cast<void*>(&_pCamera->getPosition()),
	};

	void* resources[] = {
		reinterpret_cast<void*>(_pTexture),
		reinterpret_cast<void*>(_pNormalMap),
	};
	_pShader->setMatrixBufferValues(_pD3D->getDeviceContext(), matrices);
	_pShader->setShaderResources(_pD3D->getDeviceContext(), resources);
	_pShader->render(_pD3D->getDeviceContext(), _pMesh->getIndexCount());
	

	matrices[0] = reinterpret_cast<void*>(&_pMesh2->getWorldMatrix());
	_pShader->setMatrixBufferValues(_pD3D->getDeviceContext(), matrices);
	_pShader->render(_pD3D->getDeviceContext(), _pMesh2->getIndexCount());

	_pD3D->endScene();
}

void GfxSystem::deInit()
{
	delete _pCamera;
	_pCamera = nullptr;

	delete _pShader;
	_pShader = nullptr;

	delete _pMesh;
	_pMesh = nullptr;

	_pD3D->deInit();
	delete _pD3D;
	_pD3D = nullptr;
}
