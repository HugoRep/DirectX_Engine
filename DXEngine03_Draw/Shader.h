#pragma once
#include "DXUtil.h"

class Shader
{
public:
	Shader();
	Shader(LPCTSTR fileName);
	Shader(LPCTSTR fileName, LPCSTR entry, LPCSTR profile);
	virtual ~Shader();

	virtual bool CompileShader(ID3D11Device* device) = 0;
	virtual bool CreateShader(ID3D11Device* device) = 0;
	virtual void BindShader(ID3D11DeviceContext* deviceContext) = 0;
	virtual void Release();

	void SetFileName(LPCTSTR fileName) { this->fileName = fileName; }
	//Getters
	LPCTSTR GetFileName() const { return fileName; }
	LPCSTR GetEntryPoint() const { return entryPoint; }
	LPCSTR GetProfile() const { return profile; }
	ID3DBlob* GetShaderBuffer() const { return shaderBuffer; }

protected:
	void Init();
	LPCTSTR fileName;
	LPCSTR entryPoint;
	LPCSTR profile;
	ID3DBlob* shaderBuffer;

};

