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
	//â �ʱ�ȭ
	if (window->InitializeWindow() == false)
		return false;

	return true;
}

bool DXApp::InitializeDirect3D()
{
	//����ü�� ���� - Back/Front ���� ��ȯ��;
	//������( Descriptor).
	DXGI_SWAP_CHAIN_DESC swapDesc;
	ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapDesc.BufferCount = 1;

	return true;
}

void DXApp::SetViewport()
{

}
