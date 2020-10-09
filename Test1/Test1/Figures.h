#pragma once
#include"framework.h"

VOID DrawLine(HDC hdc, int x1, int y1, int x2, int y2);

VOID DrawRectangle(HDC hdc, RECT r, HPEN pen, HBRUSH hBrush, int top, int left, int right, int bottom);

VOID DrawEraseHand(HDC hdc, int x1, int y1, int x2, int y2);