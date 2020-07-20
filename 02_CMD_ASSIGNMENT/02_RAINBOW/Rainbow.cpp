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
	static TCHAR str[255] =  TEXT("Hello World!!!");
	static TCHAR cPaintFlag = 'z';
	int iChangeChar = 0;

	switch (uMsg)
	{
	case WM_RBUTTONDOWN:
			cPaintFlag = 'o';
			InvalidateRgn( hwnd, NULL, TRUE);
			break;
	case WM_LBUTTONDOWN:
			cPaintFlag = 'w';
			InvalidateRgn( hwnd, NULL, TRUE);
			break;
	case WM_CHAR: 
		cPaintFlag = (TCHAR) wParam ;
		InvalidateRgn( hwnd, NULL, TRUE);
		break;
	case WM_PAINT:
		GetClientRect(hwnd,&rc);
		hdc = BeginPaint(hwnd,&ps);
		SetBkColor(hdc, RGB(0,0,0));
		switch( cPaintFlag){
			case 'R':
			case 'r':
				SetTextColor(hdc,RGB(255,0,0));
				break;
			case 'B':
			case 'b':
				SetTextColor(hdc,RGB(0,255,0));
				break;
			case 'C':
			case 'c':
				SetTextColor(hdc,RGB(0,255,255));
				break;
			case 'G':
			case 'g':
				SetTextColor(hdc,RGB(0,0,255));
				break;
			case 'M':
			case 'm':
				SetTextColor(hdc,RGB(255,0,255));
				break;
			case 'Y' : 
			case  'y':
				SetTextColor(hdc,RGB(255,255,0));
				break;
			case 'O':
			case 'o':
				SetTextColor(hdc,RGB(255,69,0));
				break;
			case 'W':
			case 'w':
				SetTextColor(hdc,RGB(255,255,255));
				break;
			case ' ':
				if( iChangeChar )
				{
					wsprintf(str,TEXT("BY World"));	
					iChangeChar  = 0;
				}else{
					wsprintf(str,TEXT("Hello World"));	
					iChangeChar  = 1;
				}
							
				SetTextColor(hdc,RGB(119,136,153));
				break;
			default :
				SetTextColor(hdc,RGB(139,69,19));
				break;
		}
		DrawText ( hdc, str,  -1,&rc, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
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