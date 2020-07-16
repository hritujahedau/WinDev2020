#include<windows.h>

// Gloal function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdNames, int iCmdShow) {

	WNDCLASSEX wndClassEx;
	MSG msg;
	TCHAR szClassName[] = TEXT("IDI_INFORMATION");
	HWND hwnd;

	wndClassEx.cbSize = sizeof(WNDCLASSEX);
	wndClassEx.cbClsExtra = 0;
	wndClassEx.cbWndExtra = 0;

	wndClassEx.hIcon = LoadIcon(NULL, IDI_INFORMATION);
	wndClassEx.hIconSm = LoadIcon(NULL, IDI_INFORMATION);
	wndClassEx.hInstance = hInstance;
	wndClassEx.hCursor = LoadCursor(NULL, IDC_UPARROW);

	wndClassEx.lpfnWndProc = WndProc;
	wndClassEx.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wndClassEx.lpszClassName = szClassName;
	wndClassEx.lpszMenuName = NULL;
	wndClassEx.style = CS_VREDRAW | CS_HREDRAW;


	RegisterClassEx(&wndClassEx);

	hwnd = CreateWindow(szClassName, TEXT("IDI_EXCLAMATION"), WS_OVERLAPPEDWINDOW, 100, 100, 800, 600, NULL, NULL, hInstance, 0);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	//Meessage Loop
	while (GetMessage(&msg, NULL, 0, 0)) {
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

