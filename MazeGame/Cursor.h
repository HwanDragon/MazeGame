#pragma once
#include <Windows.h>
class Cursor
{
public:
    /// <summary>
    /// �ܼ�â���� x, y ��ġ�� Ŀ�� �̵�
    /// </summary>
    /// <param name="x"></param>
    /// <param name="y"></param>
    static void gotoxy(int x, int y)
    {
        COORD pos = { x, y };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    }
};