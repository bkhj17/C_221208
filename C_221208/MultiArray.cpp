#include "MultiArray.h"
#include <stdio.h>
#include <Windows.h>
#include <conio.h> 

void ConioInputNum() {
	while (true) {
		if (_kbhit()) {					//Ű���� ������ �ν�
			int inputNum = _getch();	//Ű���� �Է��� �ƽ�Ű�ڵ�� ����
			if (inputNum < 47 || inputNum > 57)
				continue; //���� �ƴ�
			printf("inputNum : %d\n", inputNum-'0');
			break;
		}
	}
}

void MultiArray::Run()
{
	ConioInputNum();

	Sleep(1000);	//�ð� ���
	system("cls");	//ȭ�� �����
}
