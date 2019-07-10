#pragma once

#include "Engine.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPSTR lpCmdLine,_In_ int nShowCmd) 
{
	Engine engine(hInstance);

	if (engine.Init() == false)
		return 0;

	return engine.Run();;
}