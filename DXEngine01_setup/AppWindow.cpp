#include "AppWindow.h"
#include "Engine.h"
#include <iostream>

AppWindow* app = NULL;

//윈도우 메세지 프로시저 ( 메세지 처리자);
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
	applicationName = TEXT("Engine001 - Window Setup");
	windowStyle = WS_OVERLAPPEDWINDOW;
	app = this;
}


AppWindow::~AppWindow()
{

}

int AppWindow::Run(Engine* engine)
{
	MSG msg;								//메시지 변수
	ZeroMemory(&msg, sizeof(MSG));			//메모리 초기화

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
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

	//창 구조체 값 설정.

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszClassName = TEXT("DXEngine");
	wc.lpfnWndProc = WindowProcessor;


	if (!RegisterClassEx(&wc))
	{
		return false;
	}
	//창 핸들 만들기
	hwnd = CreateWindow(wc.lpszClassName, applicationName, windowStyle, 0, 0, screenWidth, screenHeight, NULL, NULL, hinstance, NULL);

	if (hwnd == NULL)
	{
		return false;
	}
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
			if (MessageBox(NULL,
				TEXT("종료 하시겠습니까?"),
				TEXT("종료"), MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				//예 버튼 눌리면 창 삭제
				DestroyWindow(this->hwnd);
			}
		}
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}