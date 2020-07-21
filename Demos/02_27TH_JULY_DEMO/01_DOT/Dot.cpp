#include<Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lszptrCommandLine, int iCmdShow) {

	// declaration
	WNDCLASSEX wndClassEx;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyWindow");

	//code
	// initilization

	wndClassEx.hInstance = hInstance;
	wndClassEx.lpszClassName = szAppName;
	wndClassEx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClassEx.cbSize = sizeof(wndClassEx);
	wndClassEx.cbClsExtra = 0;
	wndClassEx.cbWndExtra = 0;
	wndClassEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClassEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndClassEx.lpszMenuName = NULL;
	wndClassEx.style = CS_HREDRAW | CS_VREDRAW;
	wndClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClassEx.lpfnWndProc = WndProc;

	RegisterClassEx(&wndClassEx);

	hwnd = CreateWindow(
		szAppName,
		TEXT("First Assignment"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hwnd, iCmdShow );
	UpdateWindow(hwnd);

	//message loop

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}



	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;
	TCHAR str[] = TEXT("Hello World");

	switch (uMsg)
	{
	case WM_PAINT:
		
		hdc = BeginPaint(hwnd,&ps);
		SelectObject(hdc, GetStockObject(GRAY_BRUSH) );
		Ellipse ( hdc , 600 , 400 , 800 , 600 );
		EndPaint(hwnd,&ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	return (DefWindowProc(hwnd, uMsg, wParam, lParam));

}