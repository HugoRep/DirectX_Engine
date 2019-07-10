#include "DxApp.h"

DxApp::DxApp()
{
	window = NULL;
}

DxApp::DxApp(HINSTANCE hinstance)
{
	window = new AppWindow(hinstance);
}

DxApp::~DxApp()
{

}

bool DxApp::Init()
{
	if (window->InitializeWindow() == false)
		return false;
	return true;
}