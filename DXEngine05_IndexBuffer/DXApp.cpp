#include "DXApp.h"

DXApp::DXApp(HINSTANCE hinstance)
{
	window = new AppWindow(hinstance);
}

DXApp::~DXApp()
{
	//delete window;
	Memory::SafeDelete(window);

	//DX 리소스 해제.
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

	if (IsError(result, TEXT("장치 생성 실패")))
		return false;

	//백버퍼(텍스처) 생성.
	ID3D11Texture2D* backBufferTexture = NULL;
	result = swapChain->GetBuffer(NULL, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTexture);

	if (IsError(result, TEXT("백버퍼 생성 실패")))
		return false;

	//랜더 타겟 뷰 생성.
	result = device->CreateRenderTargetView(backBufferTexture, NULL, &renderTargetView);
	if (IsError(result, TEXT("랜더 타겟 생성 실패")))
		return false;

	//랜더 타겟 연결.
	deviceContext->OMSetRenderTargets(1, &renderTargetView, NULL);

	//버퍼 생성을 위한 자원 해제
	Memory::SafeRelease(backBufferTexture);

	//뷰포트 설정
	SetViewport();

	return true;
}

void DXApp::SetViewport()
{
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	//뷰포트 좌표 0~1;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = static_cast<float>(window->GetScreenWidth());
	viewport.Height = static_cast<float>(window->GetScreenHeight());

	//뷰포트 설정.
	deviceContext->RSSetViewports(1, &viewport);
}
