#include<windows.h>

// Global Variable Declaration

// long _far _ pascal WndProc (unsigned int, unsigned int, unsigned int, log);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// WinMain Funcion

// int _far _pascal main(unsigned int,unsigned int,char *args, int )

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	TCHAR szClassName[] = TEXT("MessageBoxDemo");
	HWND hwnd;
	MSG msg;

	WNDCLASSEX wndClassEx;

	HICON hIcon = LoadIcon(NULL, IDI_APPLICATION);

	wndClassEx.cbSize = sizeof(WNDCLASSEX);
	wndClassEx.cbClsExtra = 0;
	wndClassEx.cbWndExtra = 0;

	wndClassEx.lpfnWndProc = WndProc;

	wndClassEx.hIcon = hIcon;
	wndClassEx.hIconSm = hIcon;
	wndClassEx.hCursor = LoadCursor(NULL, IDC_HAND);
	wndClassEx.hInstance = hInstance;

	wndClassEx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClassEx.style = CS_VREDRAW | CS_HREDRAW;
	wndClassEx.lpszMenuName = NULL;
	wndClassEx.lpszClassName = szClassName;

	RegisterClassEx(&wndClassEx);

	hwnd = CreateWindow(szClassName,TEXT("MESSAGE BOX"), WS_OVERLAPPEDWINDOW, 100, 100, 800, 600, NULL,NULL, hInstance, NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);


	// message loop

	while (GetMessage(&msg, NULL, 0, 0 )) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	return ((int)msg.wParam);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	TCHAR str[255] = TEXT("");
	switch (uMsg) {
	case WM_CREATE:
		MessageBox(NULL, TEXT("This Message box appear before window visible"), TEXT("WM_CREATE"), MB_OK);
		break;
	case WM_LBUTTONDOWN:
		MessageBox(NULL, TEXT("This Message box appear on mouse left button click"), TEXT("WM_LBUTTONDOWN"), MB_OK);
		break;
	case WM_RBUTTONDOWN:
		MessageBox(NULL, TEXT("This Message box appear on mouse right button click"), TEXT("WM_LBUTTONDOWN"), MB_OK);
		break;
	case WM_KEYDOWN:
		wsprintf(str, TEXT("This Message box appear on key down.\nYou Pressed %c"), (LPSTR)wParam);
		MessageBox(NULL, str, TEXT("WM_KEYDOWN"), MB_OK);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	return (DefWindowProc(hwnd, uMsg, wParam, lParam));
}
