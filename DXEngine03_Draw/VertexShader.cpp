#include "VertexShader.h"
VertexShader::VertexShader()
{
	Init();
}

VertexShader::VertexShader(LPCTSTR fileName) :Shader(fileName)
{
	Init();
	profile = "vs_5_0";
}

VertexShader::VertexShader(LPCTSTR fileName, LPCSTR entry, LPCSTR profile)
{
	Init();
}

VertexShader::~VertexShader()
{
}

void VertexShader::Init()
{
	vertexShader = NULL;
}


bool VertexShader::CompileShader(ID3D11Device* device)
{
	HRESULT result = D3DCompileFromFile(fileName, NULL, NULL, entryPoint
		, profile , NULL, NULL, &shaderBuffer, NULL);
	if (IsError(result, TEXT("정점 셰이더 컴파일 오류")))
		return  false;

	return true;
}

bool VertexShader::CreateShader(ID3D11Device* device)
{
	HRESULT result = device->CreateVertexShader(
		shaderBuffer->GetBufferPointer(),
		shaderBuffer->GetBufferSize(),
		NULL,
		&vertexShader
	);

	if (IsError(result, TEXT("정점 셰이더 객체 생성 실패")))
		return false;

	return true;
}

void VertexShader::BindShader(ID3D11DeviceContext* deviceContext)
{
	deviceContext->VSSetShader(vertexShader, NULL, NULL);
}

void VertexShader::Release()
{
	Shader::Release();
	Memory::SafeRelease(vertexShader);
}

