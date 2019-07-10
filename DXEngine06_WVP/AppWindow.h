#pragma once
#include <Windows.h>

class Engine;

class AppWindow
{
public:
	AppWindow(HINSTANCE hinstance);
	~AppWindow();

	int Run(Engine* engine);
	bool InitializeWindow();
	virtual LRESULT messageProcessor(
		HWND hwnd,
		UINT msg,
		WPARAM wParam,
		LPARAM lParam
	);

	HWND GetWindowHandle() const { return hwnd; }
	UINT GetScreenWidth() const { return screenWidth; }
	UINT GetScreenHeight() const { return screenHeight; }
	LPCTSTR GetApplicationName() const { return applicationName; }

private:
	HWND hwnd;					//������ �ڵ鷯
	HINSTANCE hinstance;		//â �ν��Ͻ�
	UINT screenWidth;
	UINT screenHeight;
	LPCTSTR applicationName;
	DWORD windowStyle;	
};

