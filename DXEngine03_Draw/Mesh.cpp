#include "Mesh.h"

Mesh::Mesh()
{
	Init();
}

Mesh::~Mesh()
{
	Memory::SafeRelease(vertexBuffer);
	Memory::SafeRelease(inputLayout);
	Init();
}

void Mesh::Init()
{
	ZeroMemory(&nVertices, sizeof(nVertices));
	ZeroMemory(&vertexBuffer, sizeof(vertexBuffer));
	ZeroMemory(&inputLayout, sizeof(inputLayout));
}

bool Mesh::InitializeBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer)
{
	Vertex vertices[] = {
		Vertex(0.0f, 0.5f, 0.5f),
		Vertex(0.5f, -0.5f, 0.5f),
		Vertex(-0.5f, -0.5f, 0.5f),
	};

	//�迭 ũ�� ����.
	//int size = sizeof(vertices)/ sizeof(vertices[0]);
	nVertices = ARRAYSIZE(vertices);

	D3D11_BUFFER_DESC vbDesc;
	ZeroMemory(&vbDesc, sizeof(D3D11_BUFFER_DESC));

	vbDesc.ByteWidth = sizeof(Vertex) * nVertices;
	vbDesc.CPUAccessFlags = 0;
	vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbDesc.MiscFlags = 0;
	vbDesc.Usage = D3D11_USAGE_DEFAULT;

	//���� �迭 ���� �־��� ����ü
	D3D11_SUBRESOURCE_DATA vbData;
	ZeroMemory(&vbData, sizeof(D3D11_SUBRESOURCE_DATA));
	vbData.pSysMem = vertices;

	HRESULT result = device->CreateBuffer(&vbDesc, &vbData, &vertexBuffer);
	if (IsError(result, TEXT("���� ���� ���� ����")))
		return false;

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0 , 0 ,D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	result = device->CreateInputLayout(layout, ARRAYSIZE(layout),
		vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(),
		&inputLayout
	);

	if (IsError(result, TEXT("�Է� ���̾ƿ� ���� ����")))
		return false;

	return true;
}

void Mesh::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	//���� ���� ����.
	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	//�Է� ���̾ƿ� ����.
	deviceContext->IASetInputLayout(inputLayout);

	//���� ����.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//�׸���.
	deviceContext->Draw(nVertices, 0);
}
