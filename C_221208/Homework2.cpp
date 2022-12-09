#include "Homework2.h"
#include "UsefulFunc.h"
#include <conio.h>
#include <stdio.h>

const int Homework2::dr[5] = { 0, -1, 0, 1, 0 };
const int Homework2::dc[5] = { 0, 0, -1, 0, 1 };

Homework2::Movement Homework2::WaitInput()
{
	if (_kbhit()) {					//키보드 누르면 인식
		int inputNum = _getch();	//키보드 입력을 아스키코드로 받음
		switch (inputNum)
		{
		case 'w': case 'W':
			return Movement::UP;
		case 'a': case 'A':
			return Movement::LEFT;
		case 's': case 'S':
			return Movement::DOWN;
		case 'd': case 'D':
			return Movement::RIGHT;
		default:
			return Movement::NONE;
		}
	}
	return Movement::NONE;
}

inline bool Homework2::IsVaildPoint(int r, int c)
{
	return r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE;
}

bool Homework2::Move(Movement movement)
{
	if (movement == Movement::NONE)
		return false;

	int nr = curZeroR + dr[(int)movement];
	int nc = curZeroC + dc[(int)movement];

	if (!IsVaildPoint(nr, nc))
		return false;

	int tmp = board[curZeroR][curZeroC];
	board[curZeroR][curZeroC] = board[nr][nc];
	board[nr][nc] = tmp;

	curZeroR = nr;
	curZeroC = nc;
	return true;
}

Homework2::GameState Homework2::Check()
{
	if (CheckBoard())
		return GameState::WIN;

	if (lastCheckTime - startTime >= TIME_LIMIT)
		return GameState::GAME_OVER;

	return GameState::INPUT;
}

bool Homework2::CheckBoard() {
	for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
		if (i != board[i / BOARD_SIZE][i % BOARD_SIZE])
			return false;
	}
	return true;
}

void Homework2::CheckTime() {
	time_t now = clock();
	if (now - lastCheckTime >= SEC) {
		lastCheckTime = now;
		RequestRender();
	}
}

void Homework2::RenderBoard()
{
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++)
			printf("%.2d ", board[i][j]);
		printf("\n");
	}
}

void Homework2::Init()
{
	//게임판 초기화
	for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
		board[i/BOARD_SIZE][i%BOARD_SIZE] = i;
	curZeroR = 0;
	curZeroC = 0;
	
	do {
		for (int i = 0; i < INIT_SHUFFLE; i++)
			if (!Move(Movement(MakeRandByRange(1, 4))))
				i--;
	} while (CheckBoard());
	
	RequestRender();
	renderMessage = "";
	gameState = GameState::CHECK;
	lastCheckTime = startTime = clock();
}

void Homework2::Update()
{
	CheckTime();
	switch (gameState)
	{
	case Homework2::GameState::INIT:
		break;
	case Homework2::GameState::INPUT:
	{
		//올바른 입력(w,a,s,d)가 들어오면 0을 이동
		Movement movement = WaitInput();
		if (movement != Movement::NONE) {
			Move(movement);
			RequestRender();
		}
		gameState = GameState::CHECK;
	}
		break;
	case GameState::CHECK:
		//
		gameState = Check();
		break;
	case GameState::WIN:
		//승리
		SetRenderMessage("You Win!\n");
		gameState =  GameState::EXIT;
		break;
	case GameState::GAME_OVER:
		//패배
		SetRenderMessage("Game Over...\n");
		gameState = GameState::EXIT;
		break;
	case GameState::EXIT:
		//종료
		break;
	default:
		break;
	}
}

void Homework2::Render()
{
	if (!renderOrder)
		return;
	renderOrder = false;

	system("cls");

	RenderBoard();
	RenderTime();

	if(renderMessage.length() > 0)
		printf("%s\n", renderMessage.c_str());
}

void Homework2::Run()
{
	srand((unsigned int)time(NULL));
	Init();
	while (1) {
		Update();
		Render();
		if (gameState == GameState::EXIT)
			break;
	}

	printf("게임을 종료합니다\n");
}

void Homework2::RenderTime()
{
	time_t remining = (TIME_LIMIT - (lastCheckTime - startTime))/SEC;
	printf("남은 시간 : %lld\n", remining);
}

void Homework2::SetRenderMessage(const char* message)
{
	renderMessage = message;
	renderOrder = true;
}
