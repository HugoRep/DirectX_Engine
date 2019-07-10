#include "Shader.h"

Shader::Shader()
{
	Init();
}

Shader::Shader(LPCTSTR fileName)
{
	Init();
	this->fileName = fileName;
	entryPoint = "main";
}

Shader::Shader(LPCTSTR fileName, LPCSTR entry, LPCSTR profile)
{
	Init();
	this->fileName = fileName;
	this->entryPoint = entry;
	this->profile = profile;
}

Shader::~Shader()
{

}

void Shader::Init()
{
	fileName = NULL;
	entryPoint = NULL;
	profile = NULL;
	shaderBuffer = NULL;
}
void Shader::Release()
{
	Memory::SafeRelease(shaderBuffer);
}