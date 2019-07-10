#pragma once
#include "AppWindow.h"

class DxApp
{
public:
	DxApp();
	DxApp(HINSTANCE hinstance);
	virtual ~DxApp();

	virtual int Run() = 0;
	virtual bool Init();
	virtual void Update() = 0;
	virtual void Render() = 0;

protected:
	AppWindow* window;
};

