#pragma once
#include <conio.h>

class Keyboard
{
public:
	//<summary>
	//키보드 방향키 입력받음
	//</summary>
	//<returns></returns>
	static char getKeyboardArrowInput()
	{
		char c;
		if (_kbhit())
		{        //키보드 입력 확인 (true / false)
			c = _getch();      // 방향키 입력시 224 00이 들어오게 되기에 앞에 있는 값 224를 없앰
			if (c == -32)
			{    // -32로 입력되면
				c = _getch();  // 새로 입력값을 판별하여 상하좌우 출력
				return c;
			}
		}
		return -1;	// 방향키 입력이 아님
	}

};