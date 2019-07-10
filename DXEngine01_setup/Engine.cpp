#include "Engine.h"


Engine::Engine(HINSTANCE hinstance)
	: DxApp(hinstance)
{

}

Engine::~Engine()
{
}

int Engine::Run()
{
	return window->Run(this);
}

bool Engine::Init()
{
	if (DxApp::Init() == false)
		return false;

	return true;
}

void Engine::Update()
{
}

void Engine::Render()
{
}
