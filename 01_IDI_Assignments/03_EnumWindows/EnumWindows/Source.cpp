#include<Windows.h>
#include<stdio.h>
#define CLASS_NAME_BUFFER 50

FILE* gpFile = NULL;

typedef struct _EnumStruct {
	HWND hwnd;
	unsigned short wLword;
}EnumStruct;

HWND gHwnd = NULL;
char szSearchWindowName[255] = "Untitled - Notepad";
TCHAR wn[255] = TEXT("");

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lszptrCommandLine, int iCmdShow) {

	// declaration
	WNDCLASSEX wndClassEx;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyWindow");


	//code
	if (fopen_s(&gpFile, "windowsFile.log", "a") != 0) {
		MessageBox(NULL, TEXT("Not Able To Open File"), TEXT("File Open Failed"), MB_OK);
		exit(0);
	}

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
		TEXT("MyWindow"),
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

void GetCharStringFromTcharString(TCHAR *str, char * szCharString) {
	int i;
	for (i = 0; str[i] == '\0'; i++) {
		szCharString[i] = (char) ((int)str[i]);
	}
	fprintf(gpFile, "In GetCharStringFromTcharString\n");
	fprintf(gpFile, szCharString);
}

bool CompareTcharStringAndCharString(TCHAR* str, char* szCharString) {
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
	fprintf(gpFile, "In GetCharStringFromTcharString\n");
	fprintf(gpFile, szCharString);
	return true;
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
	TCHAR windowName[255] = TEXT("");
	char str[255] ;
	GetWindowText(hwnd, windowName, 50);	
	if (CompareTcharStringAndCharString(windowName, szSearchWindowName)) {
		//MessageBox(NULL, TEXT("Found NotePad"), TEXT("Notepad"), MB_OK);
		MessageBox(NULL, windowName, TEXT("Notepad name"), MB_OK);
		gHwnd = hwnd;
		return FALSE;
	}
	return TRUE;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	TCHAR str[255] = TEXT("");
	TCHAR windowName[255] = TEXT("");
	switch (uMsg)
	{
	case WM_CREATE:	
		EnumWindows(EnumWindowsProc, lParam);
		//gHwnd = FindWindow(0, str);
		if (gHwnd != NULL) {
			PostMessage(gHwnd, WM_DESTROY, 0, 0);
		}
		//iHwnd = FindWindow(0, str);
		//GetCharStringFromTcharString(strname, szCharString);
		/*if (CompareTcharStringAndCharString(strname, szSearchWindowName))
		{
			MessageBox(NULL, strname, TEXT("Notepad name"), MB_OK);
		}*/
		fprintf(gpFile, "Exiting from WndProc: Closing Window\n");
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	return (DefWindowProc(hwnd, uMsg, wParam, lParam));

}
