#include<Windows.h>
#define MYTIMER  105

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
	static int iPaintFlag = 0;
	static HBRUSH hbrush[8] ;

	switch (uMsg)
	{
	case WM_CREATE:
			hbrush[0] = CreateSolidBrush(RGB(255,0,0));
			hbrush[1] = CreateSolidBrush(RGB(0,255,0));
			hbrush[2] = CreateSolidBrush(RGB(0,255,255));
			hbrush[3] = CreateSolidBrush(RGB(0,0,255));
			hbrush[4] = CreateSolidBrush(RGB(255,255,0));
			hbrush[5] = CreateSolidBrush(RGB(255,69,0));
			hbrush[6] = CreateSolidBrush(RGB(255,255,255));
			hbrush[7] = CreateSolidBrush(RGB(119,136,153));
			SetTimer(hwnd, MYTIMER , 1000, NULL);
			break;

	case WM_TIMER:
			KillTimer(hwnd, MYTIMER);
			if(iPaintFlag >7) 
				iPaintFlag = 0;
			else
				 iPaintFlag++;
			InvalidateRect ( hwnd, NULL , TRUE ) ;
			SetTimer(hwnd, MYTIMER , 100, NULL);
			break;
	case WM_PAINT:
		GetClientRect(hwnd,&rc);
		hdc = BeginPaint(hwnd,&ps);
		SelectObject ( hdc , hbrush[iPaintFlag] );
		FillRect ( hdc , &rc, hbrush[iPaintFlag]) ;
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