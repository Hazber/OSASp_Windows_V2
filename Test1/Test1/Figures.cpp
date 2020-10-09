#include"Figures.h"

VOID DrawLine(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);//300 250
	LineTo(hdc, x2, y2);//300 300
}

VOID DrawRectangle(HDC hdc,RECT r, HPEN hPen, HBRUSH hBrush, int top, int left, int right, int bottom)
{
           hBrush = CreateSolidBrush(RGB(250, 200, 100));
            SelectObject(hdc, hBrush);
            hPen = CreatePen(2, 2, RGB(0, 0, 255));
            SelectObject(hdc, hPen);
            r.top = 250;
            r.left = 700;
            r.right = 850;
            r.bottom = 300;
            FillRect(hdc, &r, HBRUSH(CreateSolidBrush(RGB(255, 0, 0))));
}

VOID DrawEraseHand(HDC hdc, int x1, int y1, int x2, int y2)
{
    //ломаная
    MoveToEx(hdc, 500, 250, NULL);
    LineTo(hdc, 500, 300);
    MoveToEx(hdc, 450, 250, NULL);
    LineTo(hdc, 500, 300);
    MoveToEx(hdc, 450, 250, NULL);
    LineTo(hdc, 400, 250);
    MoveToEx(hdc, 400, 250, NULL);
    LineTo(hdc, 350, 300);
    
}
