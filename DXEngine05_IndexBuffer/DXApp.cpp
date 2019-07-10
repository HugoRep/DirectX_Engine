#include "DXApp.h"

DXApp::DXApp(HINSTANCE hinstance)
{
	window = new AppWindow(hinstance);
}

DXApp::~DXApp()
{
	//delete window;
	Memory::SafeDelete(window);

	//DX ���ҽ� ����.
	Memory::SafeRelease(device);
	Memory::SafeRelease(deviceContext);
	Memory::SafeRelease(swapChain);
	Memory::SafeRelease(renderTargetView);
}

bool DXApp::Init()
{
	if (window->InitializeWindow() == false)
		return false;

	if (this->InitializeDirect3D() == false)
		return false;
		

	return true;
}

bool DXApp::InitializeDirect3D()
{
	DXGI_SWAP_CHAIN_DESC swapDesc;
	ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapDesc.BufferCount = 1;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.OutputWindow = window->GetWindowHandle();
	swapDesc.Windowed = true;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	//swapDesc.Flags;

	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.Width = window->GetScreenWidth();
	swapDesc.BufferDesc.Height = window->GetScreenHeight();

	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;

	HRESULT result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL,
		NULL, NULL, D3D11_SDK_VERSION, &swapDesc, &swapChain, &device, NULL, &deviceContext);

	if (IsError(result, TEXT("��ġ ���� ����")))
		return false;

	//�����(�ؽ�ó) ����.
	ID3D11Texture2D* backBufferTexture = NULL;
	result = swapChain->GetBuffer(NULL, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTexture);

	if (IsError(result, TEXT("����� ���� ����")))
		return false;

	//���� Ÿ�� �� ����.
	result = device->CreateRenderTargetView(backBufferTexture, NULL, &renderTargetView);
	if (IsError(result, TEXT("���� Ÿ�� ���� ����")))
		return false;

	//���� Ÿ�� ����.
	deviceContext->OMSetRenderTargets(1, &renderTargetView, NULL);

	//���� ������ ���� �ڿ� ����
	Memory::SafeRelease(backBufferTexture);

	//����Ʈ ����
	SetViewport();

	return true;
}

void DXApp::SetViewport()
{
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	//����Ʈ ��ǥ 0~1;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = static_cast<float>(window->GetScreenWidth());
	viewport.Height = static_cast<float>(window->GetScreenHeight());

	//����Ʈ ����.
	deviceContext->RSSetViewports(1, &viewport);
}
