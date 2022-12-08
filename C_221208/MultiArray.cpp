#include "MultiArray.h"
#include <stdio.h>
#include <Windows.h>
#include <conio.h> 

void ConioInputNum() {
	while (true) {
		if (_kbhit()) {					//키보드 누르면 인식
			int inputNum = _getch();	//키보드 입력을 아스키코드로 받음
			if (inputNum < 47 || inputNum > 57)
				continue; //숫자 아님
			printf("inputNum : %d\n", inputNum-'0');
			break;
		}
	}
}

void MultiArray::Run()
{
	ConioInputNum();

	Sleep(1000);	//시간 대기
	system("cls");	//화면 지우기
}
