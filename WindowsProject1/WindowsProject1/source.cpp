#include<iostream>
#include <windows.h>
#include "graphics_stuff.h"
#include "directx_stuff.h"
#include "source.h"
#include "defines.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
using namespace GraphicsProj;
directx_stuff* directx_handle;
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT paintStruct;
	HDC hDc;

	switch (message)
	{
	case WM_PAINT:
		//hDc = BeginPaint(hwnd, &paintStruct);
		//EndPaint(hwnd, &paintStruct);
		break;
	case WM_DESTROY:
		delete directx_handle;
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		
	
		break;
	default:

		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)

{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		float width = 800.0f;
	float height = 800.0f;
	float screen_depth = 1000.0f;
	float screen_near = 0.1f;
	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( iCmdshow );
	
	WNDCLASSEX wndClass = { 0 }; 
	wndClass.cbSize = sizeof( WNDCLASSEX ) ; 
	wndClass.style = CS_HREDRAW | CS_VREDRAW; 
	wndClass.lpfnWndProc = WndProc; 
	wndClass.hInstance = hInstance; 
	wndClass.hCursor = LoadCursor( NULL, IDC_ARROW ); 
	wndClass.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 ); 
	wndClass.lpszMenuName = NULL; 
	wndClass.lpszClassName = L"Graphics Project";

	if (!RegisterClassEx(&wndClass))
	{
		return -1;
	}
	RECT rc = {0,0, width, height};

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	HWND hwnd = CreateWindowA("Graphics Project", " ", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance, NULL);
	if ( !hwnd)
	{
		return -1;
	}

	ShowWindow(hwnd, iCmdshow);

	graphics_stuff* graphics_handle = new graphics_stuff;

	
	graphics_handle->init(hwnd);

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//TODO: Update
		graphics_handle->render();
		//TODO: Draw
		
	}

	//TODO: Shudown
	graphics_handle->clean_up();
	directx_handle = graphics_handle->get_directx_handle();
	delete graphics_handle;	
	_CrtDumpMemoryLeaks();
	return static_cast<int>(msg.wParam);
	
}

