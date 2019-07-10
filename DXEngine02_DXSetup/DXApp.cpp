#include "DXApp.h"

DXApp::DXApp(HINSTANCE hinstance)
{
	window = new AppWindow(hinstance);

	device = NULL;
	deviceContext = NULL;
	swapChain = NULL;
	renderTargetView = NULL;
}

DXApp::~DXApp()
{
	//delete window;
	Memory::SafeDelete(window);

	//DX ���ҽ� ����
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
	//DXGI_SWAP_CHAIN_DESC::DXGI_USAGE    // ������ �뵵
	//{
	//	DXGI_USAGE_SHADER_INPUT         // ���̴� �Է�
	//	DXGI_USAGE_RENDER_TARGET_OUTPUT // ���� Ÿ�� ������� surface �Ǵ� �ڿ��� ���
	//	DXGI_USAGE_BACK_BUFFER          // surface �Ǵ� �ڿ��� back buffer�� ���.
	//									//swap chain�� ������ �� DXGI_USAGE_BACK_BUFFER�� ������ �ʿ�� ����.
	//	DXGI_USAGE_SHARED               // surface �Ǵ� �ڿ��� ����
	//	DXGI_USAGE_READ_ONLY            // surface �Ǵ� �ڿ��� �б� �������� ���
	//	DXGI_USAGE_DISCARD_ON_PRESENT   // DXGI ��⿡�� ���������� ���
	//	DXGI_USAGE_UNORDERED_ACCESS     // surface �Ǵ� �ڿ��� ������ ������ ���� ���
	//}

	DXGI_SWAP_CHAIN_DESC swapDesc;								// �����ϰ��� �ϴ� back buffer�� �Ӽ����� �����ϴ� ����ü
	ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapDesc.BufferCount = 1;									//Swap chain�� ����� back buffer�� ���� (���߹��۸� : 1��, ���� ���۸�:2��)
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;		//������ �뵵�� �����ϴ� ����ü
	swapDesc.OutputWindow = window->GetWindowHandle();			//������ ����� ǥ���� ������ â�� �ڵ�
	swapDesc.Windowed = true;									//â ��� true , ��ü ȭ�� ��� false;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;				//Swap ȿ���� �����ϴ� ����ü
	//swapDesc.Flags			//�߰����� �÷���

	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;		//back buffer �ȼ� ����
	swapDesc.BufferDesc.Width = window->GetScreenWidth();		//
	swapDesc.BufferDesc.Height = window->GetScreenHeight();
	//swapDesc.BufferDesc.RefreshRate							//���÷��� ��� ������
	//swapDesc.BufferDesc.ScanlineOrdering						//���÷��� ��ĵ���� ���
	//swapDesc.BufferDesc.Scaling								//���÷��� ��� ���

	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;

	//����ü�� & ��ġ & ��ġ ���ƻ���
	HRESULT result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE,
		NULL, NULL, NULL, NULL,
		D3D11_SDK_VERSION, &swapDesc, &swapChain, &device, NULL, &deviceContext);

	if (IsError(result, TEXT("��ġ ���� ����")))
		return false;

	ID3D11Texture2D* backBufferTexture;
	result = swapChain->GetBuffer(NULL, __uuidof(ID3D11Texture2D), (void**)& backBufferTexture);

	if (FAILED(result))
	{
		MessageBox(NULL, TEXT("����� ���� ����"), TEXT("����"), MB_OK);
		return false;
	}

	//���� Ÿ�� �� ����.
	result = device->CreateRenderTargetView(backBufferTexture, NULL, &renderTargetView);

	if (IsError(result, TEXT("���� Ÿ�� ���� ����")))
		return false;

	deviceContext->OMSetRenderTargets(1, &renderTargetView, NULL);

	// ���� ������ ���� ����ߴ� �ڿ� ����.
	Memory::SafeRelease(backBufferTexture);

	return true;
}
