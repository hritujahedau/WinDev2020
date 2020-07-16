#include<windows.h>
#include<stdio.h>
#include "notepad.h"

#define IDB_CLOSE 3131


#define NOTEPADCLOSE "Close Notepad"
#define NOTEPADHSIZEINC "Increase Horizontal size"
#define NOTEPADHSIZEDESC "Descrease Horizontal size"
#define NOTEPADVSIZEINC "Increase Vertical size"
#define NOTEPADVSIZEDESC "Descrease Vertical size"
#define NOTEPADMOVE "Move Window (10,10,800,600)"
#define NOTEPADMOVEORIGINAL "Set To Initial Window"
#define NOTEPADREMOVEICON "Change Icon"
#define NOTEPADREMOVEMENU "Remove Menu"
#define NOTEPADWNDNAME "Rename Window Name"
#define NOTEPADFONTCHNAGE "Add Text with changes font"
#define NOTEPADUP "Move Notepad up"
#define NOTEPADDOWN "Move Notepad down"
#define NOTEPADRIGHT "Move Notepad right"
#define NOTEPADLEFT "Move Notepad left"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
RECT rcWnd,rcNotepadWnd,rcNotepadClient, rcNotepadOriginal;
HWND ButtonClose = 0, ButtonHSizeInc = 0, ButtonHSizeDesc = 0, ButtonVSizeInc = 0,
ButtonVSizeDesc = 0, ButtonMove = 0, ButtonIcon = 0, ButtonOriginal = 0, ButtonWndName = 0,
ButtonMenu = 0, ButtonFont = 0, ButtonUp = 0, ButtonDown = 0, ButtonRight = 0, ButtonLeft = 0;
HWND hNotepad = NULL;
char szSearchWindowName[255] = "Untitled - Notepad";
HMENU hMenu;
HICON hNotepadIcon;
HICON hIcon;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreviousInstance, LPSTR lszptrCammandLine, int iCmdShow) {
	
	WNDCLASSEX wndClassEx;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyWindow");
	// code 
	//initialization 
	hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	wndClassEx.hInstance = hInstance;
	wndClassEx.lpszClassName = szAppName;
	wndClassEx.lpfnWndProc = WndProc;
	wndClassEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClassEx.cbSize = sizeof(WNDCLASSEX);
	wndClassEx.cbClsExtra = 0;
	wndClassEx.cbWndExtra = 0;
	wndClassEx.hIcon = hIcon;
	wndClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClassEx.hIconSm = hIcon;
	wndClassEx.lpszMenuName = NULL;
	wndClassEx.style = CS_HREDRAW | CS_VREDRAW;


	RegisterClassEx(&wndClassEx);
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWnd, 0);
	hwnd = CreateWindow(
		szAppName, 
		TEXT("Centering Window"), 
		WS_OVERLAPPEDWINDOW, 
		(rcWnd.right / 2) - 400, 
		(rcWnd.bottom / 2) - 300, 
		800, 
		600, 
		NULL, 
		NULL,
		hInstance,
		NULL
	);

	
	ButtonMove = CreateWindow(
		TEXT("BUTTON"),  // predefined class
		TEXT(NOTEPADMOVE), // button text
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, //style
		10,
		110,
		200,
		100,
		hwnd,
		NULL,
		hInstance,
		NULL
	);

	
	ButtonHSizeInc = CreateWindow(
		TEXT("BUTTON"),  // predefined class
		TEXT(NOTEPADHSIZEINC), // button text
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, //style
		25 + 200,
		10,
		200,
		100,
		hwnd,
		NULL,
		hInstance,
		NULL
	);

	ButtonHSizeDesc = CreateWindow(
		TEXT("BUTTON"),  // predefined class
		TEXT(NOTEPADHSIZEDESC), // button text
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, //style
		30 + 400,
		10,
		200,
		100,
		hwnd,
		NULL,
		hInstance,
		NULL
	);

	ButtonVSizeInc = CreateWindow(
		TEXT("BUTTON"),  // predefined class
		TEXT(NOTEPADVSIZEINC), // button text
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, //style
		25 + 200,
		110,
		200,
		100,
		hwnd,
		NULL,
		hInstance,
		NULL
	);

	ButtonVSizeDesc = CreateWindow(
		TEXT("BUTTON"),  // predefined class
		TEXT(NOTEPADVSIZEDESC), // button text
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, //style
		30 + 400,
		110,
		200,
		100,
		hwnd,
		NULL,
		hInstance,
		NULL
	);

	//NOTEPADMOVEORIGINAL
	//	ButtonOriginal

	ButtonOriginal = CreateWindow(
		TEXT("BUTTON"),  // predefined class
		TEXT(NOTEPADMOVEORIGINAL), // button text
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, //style
		10,
		210,
		200,
		100,
		hwnd,
		NULL,
		hInstance,
		NULL
	);

	ButtonIcon = CreateWindow(
		TEXT("BUTTON"),  // predefined class
		TEXT(NOTEPADREMOVEICON), // button text
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, //style
		230,
		210,
		200,
		100,
		hwnd,
		NULL,
		hInstance,
		NULL
	);
	
	ButtonWndName = CreateWindow(
		TEXT("BUTTON"),  // predefined class
		TEXT(NOTEPADWNDNAME), // button text
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, //style
		430,
		210,
		200,
		100,
		hwnd,
		NULL,
		hInstance,
		NULL
	);

	ButtonMenu = CreateWindow(
		TEXT("BUTTON"),  // predefined class
		TEXT(NOTEPADREMOVEMENU), // button text
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, //style
		10,
		310,
		200,
		100,
		hwnd,
		NULL,
		hInstance,
		NULL
	);

	ButtonUp = CreateWindow(
		TEXT("BUTTON"),  // predefined class
		TEXT(NOTEPADUP), // button text
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, //style
		220,
		310,
		200,
		100,
		hwnd,
		NULL,
		hInstance,
		NULL
	);

	ButtonFont = CreateWindow(
		TEXT("BUTTON"),  // predefined class
		TEXT(NOTEPADFONTCHNAGE), // button text
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, //style
		420,
		310,
		200,
		100,
		hwnd,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);


	// message loop

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);
}

int GetTCHARLength(TCHAR* str) {
	int i = 0;

	for (; str[i] != '\0'; i++);

	return i;
}

void GetCharStringFromTcharString(TCHAR* str, char* szCharString) {
	int i;
	for (i = 0; str[i] == '\0'; i++) {
		szCharString[i] = (char)((int)str[i]);
	}
}

bool CompareTcharStringAndCharString(TCHAR* str,const char* szCharString) {
	int i;
	int lenStr, lenCharString;
	int eqaul = 1;
	for (i = 0; str[i] != '\0'; i++);
	lenStr = i;
	for (i = 0; szCharString[i] != '\0'; i++);
	lenCharString = i;
	if (lenStr != lenCharString) {
		return false;
	}
	for (i = 0; str[i] != '\0'; i++) {
		if (szCharString[i] == (char)((int)str[i])) {
			continue;
		}
		else {
			eqaul = 0;
			break;
		}
	}
	if (!eqaul) {
		return false;
	}
	return true;
}


BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
	TCHAR windowName[255] = TEXT("");
	GetWindowText(hwnd, windowName, 50);
	if (CompareTcharStringAndCharString(windowName, szSearchWindowName)) {
		hNotepad = hwnd;
		return FALSE;
	}
	return TRUE;
}

BOOL CALLBACK EnumChildWindowsProc(HWND hwnd, LPARAM lParam) {	
	RECT  rc;
	TCHAR str[50];
	HFONT hFont;
	LOGFONT logFont;
	int i = 0;
	ZeroMemory(&logFont, sizeof(LOGFONT));
	HDC hdc = GetDC(hNotepad);
	logFont.lfHeight = 30;
	logFont.lfItalic = TRUE;
	logFont.lfUnderline = TRUE;
	logFont.lfWeight = FW_EXTRABOLD;
	GetClientRect(hNotepad, &rc);
	hFont = CreateFontIndirect(&logFont);
	SendMessage(hwnd, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)(LPCSTR)str);
	ReleaseDC(hNotepad, hdc);
	return FALSE;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	TCHAR strWindow[50];
	switch (uMsg)
	{
	case WM_CREATE:
		ButtonClose = CreateWindow(
			TEXT("BUTTON"),  // predefined class
			TEXT(NOTEPADCLOSE), // button text
			WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, //style
			10,
			10,
			200,
			100,
			hwnd,
			(HMENU)IDB_CLOSE,
			NULL,
			NULL
		);
		EnumWindows(EnumWindowsProc, lParam);
		GetWindowRect(hNotepad, &rcNotepadWnd);
		GetClientRect(hNotepad, &rcNotepadClient);
		rcNotepadOriginal.left = rcNotepadWnd.left;
		rcNotepadOriginal.top = rcNotepadWnd.top;
		rcNotepadOriginal.right = rcNotepadClient.right;
		rcNotepadOriginal.bottom = rcNotepadClient.bottom;
		hMenu = GetMenu(hNotepad);
		hNotepadIcon = (HICON) SendMessage(hNotepad, WM_GETICON, ICON_BIG, 0);		
		MoveWindow(hNotepad, rcNotepadWnd.left, rcNotepadWnd.top, rcNotepadClient.right, rcNotepadClient.bottom, TRUE);
		break;
	case WM_COMMAND:		
		if (hNotepad == NULL) {
			break;
		}
		switch (LOWORD(wParam)) {
		case IDB_CLOSE:
			PostMessage(hNotepad, WM_DESTROY, 0, 0);
			break;
		}
		if (HIWORD(wParam) == BN_CLICKED) {
			GetWindowText((HWND)lParam, strWindow, 50);
			if (CompareTcharStringAndCharString(strWindow, NOTEPADCLOSE)) {		
				PostMessage(hNotepad, WM_DESTROY, 0, 0);
			}else if (CompareTcharStringAndCharString(strWindow, NOTEPADHSIZEINC)) {
				rcNotepadClient.bottom = rcNotepadClient.bottom + 100;
				MoveWindow(hNotepad, rcNotepadWnd.left, rcNotepadWnd.top, rcNotepadClient.right, rcNotepadClient.bottom, TRUE);
			}
			else if (CompareTcharStringAndCharString(strWindow, NOTEPADHSIZEDESC)) {
				rcNotepadClient.bottom = rcNotepadClient.bottom - 100;
				MoveWindow(hNotepad, rcNotepadWnd.left, rcNotepadWnd.top, rcNotepadClient.right, rcNotepadClient.bottom, TRUE);			
			}
			else if (CompareTcharStringAndCharString(strWindow, NOTEPADVSIZEINC)) {
				rcNotepadClient.right = rcNotepadClient.right + 100;
				MoveWindow(hNotepad, rcNotepadWnd.left, rcNotepadWnd.top, rcNotepadClient.right, rcNotepadClient.bottom, TRUE);
			}
			else if (CompareTcharStringAndCharString(strWindow, NOTEPADVSIZEDESC)) {
				rcNotepadClient.right = rcNotepadClient.right - 100;
				MoveWindow(hNotepad, rcNotepadWnd.left, rcNotepadWnd.top, rcNotepadClient.right, rcNotepadClient.bottom, TRUE);
			}
			else if (CompareTcharStringAndCharString(strWindow, NOTEPADMOVE)) {
				MoveWindow(hNotepad, 10, 10, 800, 600, TRUE);
				rcNotepadWnd.left = 10;
				rcNotepadWnd.top = 10;
				rcNotepadClient.right = 800;
				rcNotepadClient.bottom = 600;
			}else if (CompareTcharStringAndCharString(strWindow, NOTEPADMOVEORIGINAL)) {
				SendMessage(hNotepad, WM_SETICON, ICON_BIG, (LPARAM)hNotepadIcon);
				SetMenu(hNotepad, hMenu);
				DrawMenuBar(hNotepad);				
				MoveWindow(hNotepad, rcNotepadOriginal.left, rcNotepadOriginal.top, rcNotepadOriginal.right, rcNotepadOriginal.bottom, TRUE);
				rcNotepadWnd.left = rcNotepadOriginal.left;
				rcNotepadWnd.top = rcNotepadOriginal.top;
				rcNotepadClient.right = rcNotepadOriginal.right;
				rcNotepadClient.bottom = rcNotepadOriginal.bottom;
				EnumChildWindows(hNotepad, EnumChildWindowsProc, (LPARAM)TEXT(""));
			}else if (CompareTcharStringAndCharString(strWindow, NOTEPADREMOVEICON)) {
				SendMessage(hNotepad, WM_SETICON, ICON_BIG,(LPARAM) hIcon);
			}else if (CompareTcharStringAndCharString(strWindow, NOTEPADWNDNAME)) {
				SendMessage(hNotepad, WM_SETTEXT, 0, (LPARAM)TEXT("Hrituja Window"));
			}
			else if (CompareTcharStringAndCharString(strWindow, NOTEPADREMOVEMENU)) {
				SetMenu(hNotepad, NULL);
			}if (CompareTcharStringAndCharString(strWindow, NOTEPADFONTCHNAGE)) {
				EnumChildWindows(hNotepad, EnumChildWindowsProc, (LPARAM)TEXT("This is sample text"));
			}
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
