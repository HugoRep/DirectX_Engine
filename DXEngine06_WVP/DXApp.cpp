#include "DXApp.h"

DXApp::DXApp(HINSTANCE hinstance)
{

	window = new AppWindow(hinstance);
}

DXApp::~DXApp()
{
	Memory::SafeDelete(window);	
}

bool DXApp::Init()
{
	//창 초기화
	if (window->InitializeWindow() == false)
		return false;

	return true;
}

bool DXApp::InitializeDirect3D()
{
	//스왑체인 생성 - Back/Front 버퍼 교환용;
	//서술자( Descriptor).
	DXGI_SWAP_CHAIN_DESC swapDesc;
	ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapDesc.BufferCount = 1;

	return true;
}

void DXApp::SetViewport()
{

}
