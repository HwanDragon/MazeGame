#pragma once
#include <Windows.h>
class Cursor
{
public:
    /// <summary>
    /// 콘솔창에서 x, y 위치로 커서 이동
    /// </summary>
    /// <param name="x"></param>
    /// <param name="y"></param>
    static void gotoxy(int x, int y)
    {
        COORD pos = { x, y };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    }
};