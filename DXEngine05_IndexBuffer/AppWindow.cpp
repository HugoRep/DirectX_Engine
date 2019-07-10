#include "..\DXEngine06_WVP\AppWindow.h"
#include "..\DXEngine06_WVP\AppWindow.h"
#include "..\DXEngine06_WVP\AppWindow.h"
#include "..\DXEngine06_WVP\AppWindow.h"
#include "AppWindow.h"
#include "Engine.h"

AppWindow* app = NULL;

LRESULT CALLBACK WindowProcessor(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (app != NULL)
		return app->MessageProcessor(hwnd, msg, wParam, lParam);
	else
		return DefWindowProc(hwnd, msg, wParam, lParam);
}

AppWindow::AppWindow(HINSTANCE hinstance)
{
	hwnd = NULL;
	this->hinstance = hinstance;
	screenWidth = 1600;
	screenHeight = 900;
	applicationName = TEXT("Engine05 - Index Buffer");
	windowStyle = WS_OVERLAPPEDWINDOW;
	app = this;
}


AppWindow::~AppWindow()
{
}

int AppWindow::Run(Engine* engine)
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0 , PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			engine->Update();
			engine->Render();
		}
	}

	return 0;
}

bool AppWindow::InitializeWindow()
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	//창 구조체 값 설정
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = hinstance;
	wc.hIcon = LoadIcon(hinstance, IDI_APPLICATION);
	wc.hCursor = LoadCursor(hinstance, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszClassName = TEXT("DXEngine");
	wc.lpfnWndProc = WindowProcessor;

	if (!RegisterClassEx(&wc))
		return false;

	hwnd = CreateWindow(wc.lpszClassName, applicationName,
		windowStyle, 0, 0, screenWidth, screenHeight, NULL, NULL, hinstance, NULL);

	if (hwnd == NULL)
		return false;

	ShowWindow(hwnd, SW_SHOW);

	return true;
}





LRESULT AppWindow::MessageProcessor(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_KEYDOWN:
		{
			if (wParam == VK_ESCAPE)
			{
				if (MessageBox(hwnd,
					TEXT("종료 하시겠습니까?"),
					TEXT("종료"),
					MB_YESNO | MB_ICONQUESTION) == IDYES)
				{
					DestroyWindow(this->hwnd);
				}					
			}
		}
		return 0;

		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}
