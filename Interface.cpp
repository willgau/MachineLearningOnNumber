#include <windows.h>
#include <wchar.h>
#include <string>
#include <cstring>
#include "Lab2.h"

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
LPCWSTR Edit1 = L"xx";
HWND win[15];

void AddControls(HWND);
void getValue(double*);
void createButton(HWND);
void outline(HWND, int, int, int, int, COLORREF);



int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hprevIns, LPSTR args, int ncmdshow)
{
	WNDCLASSW wc = { 0 };
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInst;
	wc.lpszClassName = L"myWindowClass";
	wc.lpfnWndProc = WindowProcedure;

	if (!RegisterClassW(&wc))
		return -1;

	win[15] = CreateWindowW(L"myWindowClass", L"Laboratoire #3: IA", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 300, 200, 1000, 570, NULL, NULL, NULL, NULL);
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}
	return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	double conf[11] = { 0,0,0,0,0,0,0,0,0,0,0 };
	LPCSTR text = "";

	PAINTSTRUCT ps;


	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		createButton(hWnd);
		AddControls(hWnd);
		break;
	case WM_PAINT:
		outline(win[10], 40, 360, 40, 20, 1);
		outline(win[10], 710, 360, 40, 360, 1);
	case WM_COMMAND:
		if (LOWORD(wp) == 1)
		{
			getValue(conf);
			text = "INIT OK";
			SetWindowText(win[11], text);

		}
		if (LOWORD(wp) == 2)
		{
			text = "ENTRY OK";
			SetWindowText(win[11], text);
		}
		if (LOWORD(wp) == 3)
		{
			xyz();
			text = "LEARN OK";
			SetWindowText(win[11], text);
		}
		if (LOWORD(wp) == 4)
		{
			text = "VC OK";
			SetWindowText(win[11], text);
		}
		if (LOWORD(wp) == 5)
		{
			text = "TEST OK";
			SetWindowText(win[11], text);
		}
		if (LOWORD(wp) == 6)
		{
			text = "SAVE CONFIG OK";
			SetWindowText(win[11], text);
		}
		if (LOWORD(wp) == 7)
		{
			text = "SAVE NETWORK OK";
			SetWindowText(win[11], text);
		}
		if (LOWORD(wp) == 8)
		{
			DestroyWindow(hWnd);
		};
		for (int i = 0; i < 16; i++)
		{
			UpdateWindow(win[i]);
		}
		break;
	default:
		{
			for (int i = 0; i < 16; i++)
			{
				UpdateWindow(win[i]);
			}
			return DefWindowProcW(hWnd, msg, wp, lp);
			break;
		}
	}

}
void AddControls(HWND hWnd)
{
	CreateWindowW(L"static", L"Nombre d'entrée", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 10, 10, 100, 50, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"Nombre de sortie", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 10, 55, 100, 50, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"Nombre de couche", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 10, 100, 100, 50, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"Nombre de neurone/couche", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 10, 145, 100, 50, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"type de fonction", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 10, 190, 100, 50, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"taux d'apprentissage", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 10, 235, 100, 50, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"poids min", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 10, 280, 100, 50, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"poids max", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 10, 325, 100, 50, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"seuils min", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 10, 370, 100, 50, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"seuils max", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 10, 415, 100, 50, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"epoque", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 10, 460, 100, 50, hWnd, NULL, NULL, NULL);// axis label x
	

	win[0] = CreateWindowW(L"Edit", L"1", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 120, 10, 100, 50, hWnd, NULL, NULL, NULL);
	win[1] = CreateWindowW(L"Edit", L"1", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 120, 55, 100, 50, hWnd, NULL, NULL, NULL);
	win[2] = CreateWindowW(L"Edit", L"1", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 120, 100, 100, 50, hWnd, NULL, NULL, NULL);
	win[3] = CreateWindowW(L"Edit", L"1", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 120, 145, 100, 50, hWnd, NULL, NULL, NULL);
	win[4] = CreateWindowW(L"Edit", L"0", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 120, 190, 100, 50, hWnd, NULL, NULL, NULL);
	win[5] = CreateWindowW(L"Edit", L"0.1", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 120, 235, 100, 50, hWnd, NULL, NULL, NULL);
	win[6] = CreateWindowW(L"Edit", L"-0.10", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 120, 280, 100, 50, hWnd, NULL, NULL, NULL);
	win[7] = CreateWindowW(L"Edit", L"0.10", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 120, 325, 100, 50, hWnd, NULL, NULL, NULL);
	win[8] = CreateWindowW(L"Edit", L"-10", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 120, 370, 100, 50, hWnd, NULL, NULL, NULL);
	win[9] = CreateWindowW(L"Edit", L"10", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 120, 415, 100, 50, hWnd, NULL, NULL, NULL);
	win[10] = CreateWindowW(L"static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 230, 120, 740, 390, hWnd, NULL, NULL, NULL);//graphique
	SetWindowPos(CreateWindowW(L"static", L"100", WS_VISIBLE | SS_CENTER | WS_CHILD, 240, 150, 25, 15, hWnd, NULL, NULL, NULL), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	SetWindowPos(CreateWindowW(L"static", L"erreur", WS_VISIBLE | SS_CENTER | WS_CHILD, 240, 125, 40, 15, hWnd, NULL, NULL, NULL), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	SetWindowPos(CreateWindowW(L"static", L"epoque", WS_VISIBLE | SS_CENTER | WS_CHILD, 550, 480, 50, 20, hWnd, NULL, NULL, NULL), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	win[11] = CreateWindowW(L"static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 650, 10, 320, 100, hWnd, NULL, NULL, NULL);//console
	win[12] = CreateWindowW(L"Edit", L"10", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 120, 460, 100, 50, hWnd, NULL, NULL, NULL);
	win[13] = CreateWindowW(L"static", L"10", WS_VISIBLE | SS_CENTER | WS_CHILD, 750, 480, 100, 20, hWnd, NULL, NULL, NULL);
	SetWindowPos(win[13], HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);	

}

void getValue(double *conf)
{
	wchar_t text[100];
	wchar_t * pEnd;

	GetWindowTextW(win[0], text, 100);
	conf[0] = wcstod(text, &pEnd);

	GetWindowTextW(win[1], text, 100);
	conf[1] = wcstod(text, &pEnd);

	GetWindowTextW(win[2], text, 100);
	conf[2] = wcstod(text, &pEnd);

	GetWindowTextW(win[3], text, 100);
	conf[3] = wcstod(text, &pEnd);

	GetWindowTextW(win[4], text, 100);
	conf[4] = wcstod(text, &pEnd);

	GetWindowTextW(win[5], text, 100);
	conf[5] = wcstod(text, &pEnd);

	GetWindowTextW(win[6], text, 100);
	conf[6] = wcstod(text, &pEnd);

	GetWindowTextW(win[7], text, 100);
	conf[7] = wcstod(text, &pEnd);

	GetWindowTextW(win[8], text, 100);
	conf[8] = wcstod(text, &pEnd);

	GetWindowTextW(win[9], text, 100);
	conf[9] = wcstod(text, &pEnd);

	GetWindowTextW(win[12], text, 100);
	conf[10] = wcstod(text, &pEnd);

	wchar_t text1;
	char k[100];
	for (int i = 0; i<100; i++)
	{
		k[i] = text[i];
	}

	SetWindowText(win[13], (LPCSTR)k);	
}

void createButton(HWND hWnd)
{
	CreateWindow(TEXT("button"), TEXT("INIT"), WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 230, 10, 100, 50, hWnd, (HMENU)1, NULL, NULL);
	CreateWindow(TEXT("button"), TEXT("Entry"), WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 330, 10, 100, 50, hWnd, (HMENU)2, NULL, NULL);
	CreateWindow(TEXT("button"), TEXT("Learn"), WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 430, 10, 100, 50, hWnd, (HMENU)3, NULL, NULL);
	CreateWindow(TEXT("button"), TEXT("Test"), WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 530, 10, 100, 50, hWnd, (HMENU)4, NULL, NULL);
	CreateWindow(TEXT("button"), TEXT("Load"), WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 230, 60, 100, 50, hWnd, (HMENU)5, NULL, NULL);
	CreateWindow(TEXT("button"), TEXT("Save config"), WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 330, 60, 100, 50, hWnd, (HMENU)6, NULL, NULL);
	CreateWindow(TEXT("button"), TEXT("Save Network"), WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 430, 60, 100, 50, hWnd, (HMENU)7, NULL, NULL);
	CreateWindow(TEXT("button"), TEXT("Quit"), WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 530, 60, 100, 50, hWnd, (HMENU)8, NULL, NULL);

}


/*---------------------------------------------------------------------------------------*/
void outline(HWND hwnd, int startX, int startY, int endX, int endY, COLORREF color)
{

	HDC hdc;                        /*  get a graphics device context */
	hdc = GetDC(hwnd);

	HPEN pencolor;             /*  set pen color and style  */
	pencolor = CreatePen(PS_SOLID, 1, color);      /* width 0, = 1 pixel thick */
	SelectObject(hdc, pencolor);

	MoveToEx(hdc, startX, startY, NULL);    /* Set starting pen, drawing position */
	LineTo(hdc, endX, endY);

	ReleaseDC(hwnd, hdc);

	return;
}
/*----------------------------------------------------------------------------------------*/






