#include "DXApp.h"

DXApp::DXApp(HINSTANCE hinstance)
{
	device = NULL;
	deviceContext = NULL;
	swapChain = NULL;
	renderTargetView = NULL;

	window = new AppWindow(hinstance);
}

DXApp::~DXApp()
{
	//delete window;
	Memory::SafeDelete(window);

	//DX 리소스 해제
	Memory::SafeRelease(device);
	Memory::SafeRelease(deviceContext);
	Memory::SafeRelease(swapChain);
	Memory::SafeRelease(renderTargetView);
}

bool DXApp::Init()
{
	if (window->InitializeWindow() == false)
		return false;

	if (InitializeDirect3D() == false)
		return false;

	return true;
}

bool DXApp::InitializeDirect3D()
{
	DXGI_SWAP_CHAIN_DESC swapDesc;								// 생성하고자 하는 back buffer의 속성들을 서술하는 구조체
	ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapDesc.BufferCount = 1;									//Swap chain에 사용할 back buffer의 개수 (이중버퍼링 : 1개, 삼중 버퍼링:2개)
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;		//버퍼의 용도를 서술하는 구조체
	swapDesc.OutputWindow = window->GetWindowHandle();			//랜더링 결과를 표시할 윈도우 창의 핸들
	swapDesc.Windowed = true;									//창 모드 true , 전체 화면 모드 false;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;				//Swap 효과를 서술하는 구조체
	//swapDesc.Flags			//추가적인 플래그

	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;		//back buffer 픽셀 형식
	swapDesc.BufferDesc.Width = window->GetScreenWidth();		//
	swapDesc.BufferDesc.Height = window->GetScreenHeight();
	//swapDesc.BufferDesc.RefreshRate							//디스플레이 모드 갱신율
	//swapDesc.BufferDesc.ScanlineOrdering						//디스플레이 스캔라인 모드
	//swapDesc.BufferDesc.Scaling								//디스플레이 비례 모드

	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;

	//스왑체인 & 장치 & 장치 문맥생성
	HRESULT result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE,
		NULL, NULL, NULL, NULL,
		D3D11_SDK_VERSION, &swapDesc, &swapChain, &device, NULL, &deviceContext);

	if (IsError(result, TEXT("장치 생성 실패")))
		return false;

	ID3D11Texture2D* backBufferTexture;
	result = swapChain->GetBuffer(NULL, __uuidof(ID3D11Texture2D), (void**)& backBufferTexture);

	if (FAILED(result))
	{
		MessageBox(NULL, TEXT("백버퍼 생성 실패"), TEXT("오류"), MB_OK);
		return false;
	}

	//랜더 타겟 뷰 생성.
	result = device->CreateRenderTargetView(backBufferTexture, NULL, &renderTargetView);

	if (IsError(result, TEXT("랜더 타겟 생성 실패")))
		return false;

	deviceContext->OMSetRenderTargets(1, &renderTargetView, NULL);

	// 버퍼 생성을 위해 사용했던 자원 해제.
	Memory::SafeRelease(backBufferTexture);
	//뷰포트 설정.
	SetViewport();
	return true;
}

void DXApp::SetViewport()
{
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = static_cast<float>(window->GetScreenWidth());
	viewport.Height = static_cast<float>(window->GetScreenHeight());

	// 뷰포트 설정.
	deviceContext->RSSetViewports(1, &viewport);
}
