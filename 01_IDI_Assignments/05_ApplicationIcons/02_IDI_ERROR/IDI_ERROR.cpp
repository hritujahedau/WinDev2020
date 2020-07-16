#include<windows.h>

//gloabl funcyion declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR nsCmdName, int iCmdShow) {

	WNDCLASSEX wndClassEx;
	TCHAR szClassName[] = TEXT("IDI_ERROR_DEMO");
	HWND hwnd;
	MSG msg;

	wndClassEx.cbSize = sizeof(WNDCLASSEX);
	wndClassEx.cbClsExtra = 0;
	wndClassEx.cbWndExtra = 0;

	wndClassEx.hInstance = hInstance;
	wndClassEx.hIcon = LoadIcon(NULL, IDI_ERROR);
	wndClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClassEx.hIconSm = LoadIcon(NULL, IDI_ERROR);

	wndClassEx.lpszClassName = szClassName;
	wndClassEx.lpszMenuName = NULL;

	wndClassEx.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wndClassEx.style = CS_HREDRAW | CS_VREDRAW;
	wndClassEx.lpfnWndProc = WndProc;

	RegisterClassEx(&wndClassEx);

	hwnd = CreateWindow(szClassName, TEXT("IDI_ERRO"), WS_OVERLAPPEDWINDOW, 100, 100, 800, 600, NULL,NULL, hInstance, 0);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	//message loop
	while(GetMessage(&msg, NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	
	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hwnd, uMsg, wParam, lParam));
}

