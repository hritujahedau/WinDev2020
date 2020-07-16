#include<windows.h>

// int _far _pascal WindProc (unisgned int,unsigned int,unsined int,log);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//int _far _pascal WinMain(unisgned int, usigned int,char *name,int)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstnace, LPSTR szCmdName, int iCmdShow) {

	//varible declaration

	WNDCLASSEX wndClassEx;
	TCHAR szClassName[] = TEXT("Show Window");
	HWND hwnd;
	MSG msg;

	//intitalization
	wndClassEx.cbSize = sizeof(wndClassEx);
	wndClassEx.cbClsExtra = 0;
	wndClassEx.cbWndExtra = 0;

	wndClassEx.hInstance = hInstance;
	wndClassEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClassEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	wndClassEx.lpszClassName = szClassName;
	wndClassEx.lpszMenuName = NULL;

	wndClassEx.lpfnWndProc = WndProc;
	wndClassEx.style = CS_HREDRAW | CS_VREDRAW;
	wndClassEx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	//code
	RegisterClassEx(&wndClassEx);

	hwnd = CreateWindow(szClassName, TEXT("SW_SHOWMINIMIZED"), WS_OVERLAPPEDWINDOW,
		100, 100, 800, 600, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, SW_SHOWMINIMIZED);
	UpdateWindow(hwnd);

	//Message loop
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	switch (iMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
