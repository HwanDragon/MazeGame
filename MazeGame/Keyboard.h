#pragma once
#include <conio.h>

class Keyboard
{
public:
	//<summary>
	//Ű���� ����Ű �Է¹���
	//</summary>
	//<returns></returns>
	static char getKeyboardArrowInput()
	{
		char c;
		if (_kbhit())
		{        //Ű���� �Է� Ȯ�� (true / false)
			c = _getch();      // ����Ű �Է½� 224 00�� ������ �Ǳ⿡ �տ� �ִ� �� 224�� ����
			if (c == -32)
			{    // -32�� �ԷµǸ�
				c = _getch();  // ���� �Է°��� �Ǻ��Ͽ� �����¿� ���
				return c;
			}
		}
		return -1;	// ����Ű �Է��� �ƴ�
	}

};