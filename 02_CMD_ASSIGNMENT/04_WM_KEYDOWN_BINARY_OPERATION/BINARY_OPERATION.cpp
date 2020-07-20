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
		TEXT("On Key +,-,%,*"),
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
	int a=75,b=25; 
	TCHAR str[255] ;
	switch (uMsg)
	{
	case WM_CHAR :
		switch( wParam ) {
			case '+':
				wsprintf(str, TEXT("Addition of %d and %d is %d"), a , b , a+b);
				MessageBox(NULL, str, TEXT("Addition"), MB_OK);
				break;
			case '-':
				wsprintf(str, TEXT("Sustraction of %d and %d is %d"), a , b , a-b);
				MessageBox(NULL, str, TEXT("Addition"), MB_OK);
				break;
			case '/':
				wsprintf(str, TEXT("Division of %d and %d is %d"), a , b , a%b);
				MessageBox(NULL, str, TEXT("Addition"), MB_OK);
				break;
			case '*':
				wsprintf(str, TEXT("Multiplication of %d and %d is %d"),  a , b , a*b);
				MessageBox(NULL, str, TEXT("Addition"), MB_OK);
				break;

		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	return (DefWindowProc(hwnd, uMsg, wParam, lParam));

}