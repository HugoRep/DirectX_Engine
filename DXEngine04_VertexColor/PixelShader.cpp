#include "PixelShader.h"

PixelShader::PixelShader()
{
	Init();
}

PixelShader::PixelShader(LPCTSTR fileName)
	:Shader(fileName)
{
	Init();
	profile = "ps_5_0";
}

PixelShader::PixelShader(LPCTSTR fileName, LPCSTR entry, LPCSTR profile)
	:Shader(fileName,entry,profile)
{
	Init();
}

PixelShader::~PixelShader()
{
	Init();
}

bool PixelShader::CompileShader(ID3D11Device* device)
{
	HRESULT result = D3DCompileFromFile(fileName, NULL, NULL,
		entryPoint, profile, NULL, NULL, &shaderBuffer, NULL
	);

	if (IsError(result, TEXT("�ȼ� ���̴� ������ ����")))
		return false;

	return true;
}

bool PixelShader::CreateShader(ID3D11Device* device)
{
	// �ȼ� ���̴� ��ü ����.
	HRESULT result = device->CreatePixelShader(
		shaderBuffer->GetBufferPointer(),
		shaderBuffer->GetBufferSize(),
		NULL,
		&pixelShader
	);

	if (IsError(result, TEXT("�ȼ� ���̴� ��ü ���� ����")))
		return false;
	return true;
}

void PixelShader::BindShader(ID3D11DeviceContext* deviceContext)
{
	deviceContext->PSSetShader(pixelShader, NULL, NULL);
}

void PixelShader::Release()
{
	// �ڿ� ����.
	Shader::Release();
	Memory::SafeRelease(pixelShader);
}

void PixelShader::Init()
{
	pixelShader = NULL;
}
