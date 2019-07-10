#pragma once
#include "Shader.h"
class VertexShader :public Shader
{
public:
	VertexShader();
	VertexShader(LPCTSTR fileName);
	VertexShader(LPCTSTR fileName, LPCSTR entry, LPCSTR profile);
	~VertexShader();

	virtual bool CompileShader(ID3D11Device* device) override;
	virtual bool CreateShader(ID3D11Device* device) override;
	virtual void BindShader(ID3D11DeviceContext* deviceContext) override;
	virtual void Release() override;

	//Getter
	ID3D11VertexShader* GetVertextShader() const { return vertexShader; }

private:
	ID3D11VertexShader* vertexShader;
	void Init();
};

