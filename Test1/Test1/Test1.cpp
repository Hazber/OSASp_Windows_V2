// Test1.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Figures.h"
#include "Test1.h"
#include <unordered_map>

#define MAX_LOADSTRING 100


HINSTANCE hInst;                                
WCHAR szTitle[MAX_LOADSTRING];                  
WCHAR szWindowClass[MAX_LOADSTRING];     
       
HDC hdc;
static HDC secondHDC;
PAINTSTRUCT ps;
RECT r;
HPEN pen;
HBRUSH hBrush;
LOGFONT lf;
HFONT hFont;
HPEN hPen;
HWND hwnd;


ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TEST1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEST1));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEST1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TEST1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; 

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {

    case WM_CREATE:
    {
        hdc = GetDC(hWnd);
        secondHDC = CreateCompatibleDC(hdc);
        HBITMAP bMap = CreateCompatibleBitmap(hdc, 1000, 1000);
        SelectObject(secondHDC, bMap);
    }
    case WM_PAINT:
        {
            
            HDC hdc = BeginPaint(hWnd, &ps);
         
            hBrush = CreateHatchBrush(HS_FDIAGONAL, RGB(255, 0, 0));
            SelectObject(hdc, hBrush);
           
            //текст
            lf.lfHeight = 20;
            lf.lfItalic = 1;
            lf.lfStrikeOut = 0;
            lf.lfUnderline = 0;
            lf.lfWidth = 10;
            lf.lfWeight = 40;
            lf.lfCharSet = DEFAULT_CHARSET;
            lf.lfPitchAndFamily = DEFAULT_PITCH; 
            lf.lfEscapement = 0;
            hFont = CreateFontIndirect(&lf);
            SelectObject(hdc, hFont);
            SetTextColor(hdc, RGB(255, 0, 255));
            TextOutW(hdc, 150, 270, L"Hello World", lstrlen(L"Hello World"));

            //линия
            DrawLine(hdc, 300, 250, 300, 300);

            DrawEraseHand(hdc, 500, 250, 350, 300);
           
            //эллипс
            hBrush = CreateSolidBrush(RGB(10, 200, 100));
            SelectObject(hdc, hBrush);
            Ellipse(hdc, 900, 250, 1000, 300);

            DrawRectangle(hdc,r,hPen,hBrush, 250, 700, 850, 300);
    
            //многоугольник
            POINT poly[6];
            poly[0].x = 650;
            poly[0].y = 300;
            poly[1].x = 550;
            poly[1].y = 300;
            poly[2].x = 550;
            poly[2].y = 270;
            poly[3].x = 600;
            poly[3].y = 250;
            poly[4].x = 650;
            poly[4].y = 270;
            poly[5].x = 650;
            poly[5].y = 300;
            Polyline(hdc, poly, 6);

            ValidateRect(hWnd, NULL);
            EndPaint(hWnd, &ps);
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

