#include "Homework.h"
#include "UsefulFunc.h"
#include <time.h>
#include <Windows.h>

void Homework::PrintAttempt()
{
	renderMessage += std::to_string(cnt_attempt+1)+"번째 시도\n";
}

void Homework::PrintLog()
{
	if (cnt_attempt == 0)
		return;
	renderMessage += "지난 입력 : ";

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
				printf(" □ ");
		}
		printf("\n");
	}
}

void Homework::Win()
{
	renderMessage += std::to_string(WINNING_SCORE) + "빙고 완성으로 승리하셨습니다. (" + std::to_string(cnt_attempt + 1) + " 시도)\n";
	CallRender();
	gameState = GameState::EXIT;
}

void Homework::GameOver()
{
	renderMessage += "넣을 수 있는 숫자가 " + std::to_string(MAX_NUM - MIN_NUM + 1) + "개 밖에 없는데 왜 " + std::to_string(MAX_ATTEMPT) + "번 시도하고도 못하셨습니까...\n";
	renderMessage += "이제 그만 해요.\n";
	CallRender();
	gameState = GameState::EXIT;
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
	printf("(%d~%d)입력 -> ", MIN_NUM, MAX_NUM);
	scanf_s("%d", &input);

	if (input < MIN_NUM || MAX_NUM < input) {
		CallRender();
		renderMessage += "잘못된 입력입니다.\n";
	}
	else {
		logArr[cnt_attempt++] = input;
		gameState = GameState::CHECK;
	}
}

void Homework::Check()
{
	bool check = CheckHit(input);
	renderMessage += std::to_string(input) + (check ?" Hit\n" : " 실패...\n");

	int bingo = GetCountBingo();
	renderMessage += "현재 "+std::to_string(bingo)+"빙고\n";
	CallRender();

	if (bingo >= WINNING_SCORE)
		gameState = GameState::WIN;
	else if(cnt_attempt == MAX_ATTEMPT)
		gameState = GameState::GAME_OVER;
	else
		gameState = GameState::CALL_INPUT;
	
}

bool Homework::CheckHit(int input)
{
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++)
			if (!hitBoard[i][j] && board[i][j] == input)
				return hitBoard[i][j] = true;
	}
	return false;
}

void Homework::Render()
{
	if (!renderOrder)
		return;

	system("cls");
	printf("[빙고게임]\n");
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
	//게임 종료
}
