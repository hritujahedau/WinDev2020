#include<windows.h>

// global function declaration

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdName, int iCmdShow) {

	WNDCLASSEX wndClassEx;
	TCHAR szClassName[] = TEXT("IDI_ASTERISK_CN");
	HWND hwnd;
	MSG msg;

	wndClassEx.cbSize = sizeof(WNDCLASSEX);
	wndClassEx.cbClsExtra = 0;
	wndClassEx.cbWndExtra = 0;
	wndClassEx.hIcon = LoadIcon(NULL, IDI_ASTERISK);
	wndClassEx.hIconSm = LoadIcon(NULL, IDI_ASTERISK);
	wndClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClassEx.hInstance = hInstance;
	wndClassEx.lpszMenuName = NULL;
	wndClassEx.lpszClassName = szClassName;
	wndClassEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClassEx.lpfnWndProc = WndProc;
	wndClassEx.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wndClassEx);

	hwnd = CreateWindow(szClassName, TEXT("IDC_ASTERISK"), WS_OVERLAPPEDWINDOW, 100, 100, 800, 600, NULL, NULL, hInstance, NULL, 0);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	//message loop

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
