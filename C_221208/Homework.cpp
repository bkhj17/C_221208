#include "Homework.h"
#include "UsefulFunc.h"
#include <time.h>
#include <Windows.h>

void Homework::PrintAttempt()
{
	renderMessage += std::to_string(cnt_attempt+1)+"��° �õ�\n";
}

void Homework::PrintLog()
{
	if (cnt_attempt == 0)
		return;
	renderMessage += "���� �Է� : ";

	for (int i = 0; i < cnt_attempt; i++) {
		renderMessage += std::to_string(logArr[i]) + " ";
	}
	renderMessage += "\n";
}

void Homework::PrintBoard()
{
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			
			if (hitBoard[i][j])
				printf("%3d ", board[i][j]);
			else
				printf(" �� ");
		}
		printf("\n");
	}
}

int Homework::GetCountBingo()
{
	int bingo = 0;
	for (int i = 0; i < BOARD_SIZE; i++) {
		int cntRight = 0, cntDown = 0;
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (hitBoard[i][j])
				cntRight++;
			if (hitBoard[j][i])
				cntDown++;
		}

		if (cntRight == BOARD_SIZE)
			bingo++;

		if (cntDown == BOARD_SIZE)
			bingo++;
	}

	int diagonalR = 0, diagonalL = 0;
	for (int i = 0; i < BOARD_SIZE; i++) {
		if (hitBoard[i][i])
			diagonalL++;
		if (hitBoard[i][BOARD_SIZE - 1 - i])
			diagonalR++;
	}
	if (diagonalR == BOARD_SIZE)
		bingo++;

	if (diagonalL == BOARD_SIZE)
		bingo++;

	return bingo;
}


void Homework::Init()
{
	srand((uint)time(NULL));
	const uint SET_RANGE = MAX_NUM - MIN_NUM + 1;
	int settingBoard[SET_RANGE];
	for (int i = MIN_NUM; i <= MAX_NUM; i++)
		settingBoard[i - MIN_NUM] = i;

	GetRandomsNoOverlap(settingBoard, SET_RANGE, BOARD_SIZE * BOARD_SIZE);
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			board[i][j] = settingBoard[BOARD_SIZE * i + j];
			hitBoard[i][j] = false;
		}
	}
	CallRender();

	bool requestInput = false;
	int input = 0;
}

void Homework::Input()
{
	input = 0;
	printf("(%d~%d)�Է� -> ", MIN_NUM, MAX_NUM);
	scanf_s("%d", &input);

	if (input < MIN_NUM || MAX_NUM < input) {
		CallRender();
		renderMessage += "�߸��� �Է��Դϴ�.\n";
	}
	else {
		logArr[cnt_attempt++] = input;
		gameState = GameState::CHECK;
	}
}

void Homework::Check()
{
	renderMessage += std::to_string(input) + (CheckHit(input) ?" Hit\n" : " ����...\n");

	sleepTime = 1000;
	//�Է�Ƚ�� ����

	int bingo = GetCountBingo();
	renderMessage += "���� "+std::to_string(bingo)+"����\n";
	CallRender();

	if (bingo == WINNING_SCORE)
		gameState = GameState::WIN;
	else
		gameState = GameState::CALL_INPUT;
	
}

bool Homework::CheckHit(int input)
{
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j] == input) {
				return hitBoard[i][j] = true;
			}
		}
	}
	return false;
}

void Homework::Update()
{
	switch (gameState)
	{
	case Homework::GameState::INIT:
		gameState = GameState::CALL_INPUT;
		break;
	case Homework::GameState::CALL_INPUT:
		Input();
		break;
	case Homework::GameState::CHECK:
		Check();
		break;
	case Homework::GameState::WIN:
		renderMessage += std::to_string(WINNING_SCORE) + "���� �ϼ����� �¸��ϼ̽��ϴ�. ("+ std::to_string(cnt_attempt+1) + " �õ�)\n";
		CallRender();
		gameState = GameState::EXIT;
		break;
	case Homework::GameState::GAME_OVER:
		gameState = GameState::EXIT;
		break;
	case Homework::GameState::EXIT:
		renderMessage += "������ �����մϴ�\n";
		break;
	default:
		break;
	}

}

void Homework::Render()
{
	if (!renderOrder)
		return;

	system("cls");
	printf("�������\n");
	PrintBoard();
	PrintAttempt();
	PrintLog();
	printf("%s", renderMessage.c_str());
	if (sleepTime > 0) {
		Sleep(sleepTime);
		sleepTime = 0;
	}
	if(gameState != GameState::EXIT)
		renderMessage = "";
	renderOrder = false;
}

void Homework::Run()
{
	Init();
	while(gameState != GameState::EXIT) {
		Update();
		Render();
	}
	//���� ����
}
