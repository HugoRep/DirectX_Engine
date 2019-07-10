#include "Shader.h"

Shader::Shader()
{
	init();
}

Shader::Shader(LPCTSTR fileName)
{
	init();
	this->fileName = fileName;
	entryPoint = "main";
}

Shader::Shader(LPCTSTR fileName, LPCSTR entry, LPCSTR profile)
{
	init();
	this->fileName = fileName;
	this->entryPoint = entry;
	this->profile = profile;
}

Shader::~Shader()
{

}

void Shader::init()
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