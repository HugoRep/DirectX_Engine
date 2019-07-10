#pragma once
#include "DXUtil.h"
class Shader
{
public:
	Shader();
	Shader(LPCTSTR fileName);
	Shader(LPCTSTR fileName, LPCSTR entry, LPCSTR profile);
	virtual ~Shader();

	virtual bool CompileShader(ID3D11Device* deviece) = 0;
	virtual bool CreateShader(ID3D11Device* device) = 0;
	virtual void BindShader(ID3D11DeviceContext* deviceContext) = 0;
	virtual void Release();

	void SetFileName(LPCTSTR fileName) { this->fileName = fileName; }

	//Getter.
	LPCTSTR GetfileName() const { return fileName; }
	LPCSTR GetEntryPoint() const { return entryPoint; }
	LPCSTR GetProfile() const { return profile; }
	ID3DBlob* GetShaderBuffer() const { return shaderBuffer; }

protected:
	LPCTSTR fileName = NULL;
	LPCSTR entryPoint = NULL;
	LPCSTR profile = NULL;
	ID3DBlob* shaderBuffer = NULL;

};

