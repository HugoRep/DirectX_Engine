#pragma once
#include "AppWindow.h"
#include "DXUtil.h"

class DXApp
{
public:
	DXApp(HINSTANCE hinstance);
	virtual ~DXApp();

	virtual int Run() = 0;
	virtual bool Init();
	virtual void Update() = 0;
	virtual void Render() = 0;

protected:
	AppWindow* window;

	ID3D11Device* device = NULL;
	ID3D11DeviceContext* deviceContext = NULL;
	IDXGISwapChain* swapChain = NULL;
	ID3D11RenderTargetView* renderTargetView = NULL;

protected:
	bool InitializeDirect3D();
	void SetViewport();

};

