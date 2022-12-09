#pragma once
/*
과제 2 : 슬라이드 퍼즐 게임
4*4 슬라이드
w a s d 키로 0을 상하좌우로 이동

//고급 : 제한 시간 추가

00 01 02 03

04 05 06 07

08 09 10 11

12 13 14 15

순서대로 정렬하는 데에 성공하면 승리
*/
#include "Base.h"
#include <time.h>
#include <string>

class Homework2 : public Base
{
	static const int BOARD_SIZE = 4;
	static const int INIT_SHUFFLE = 500;
	static const int SEC = 1000;
	static const time_t TIME_LIMIT = 2000*SEC; //초

	enum class Movement : int
	{
		NONE = 0, UP = 1, LEFT = 2, DOWN = 3, RIGHT = 4
	};
	static const int dr[5];
	static const int dc[5];

	enum class GameState {
		INIT,
		INPUT,
		CHECK,
		WIN,
		GAME_OVER,
		EXIT
	};
	GameState gameState = GameState::INIT;
private:
	Movement WaitInput();

private:
	int board[BOARD_SIZE][BOARD_SIZE] = {};
	
	int curZeroR = 0, curZeroC = 0;
	bool IsVaildPoint(int r, int c);
	bool Move(Movement);

	GameState Check();
	bool CheckBoard();

	time_t startTime = 0;
	time_t lastCheckTime = 0;
	void CheckTime();

private:
	bool renderOrder = false;
	void RequestRender() { renderOrder = true; }
	void SetRenderMessage(const char* Message);

	void RenderBoard();
	void RenderTime();

	std::string renderMessage = "";
private:
	void Init();
	void Update();
	void Render();
public:
	// Base을(를) 통해 상속됨
	virtual void Run() override;
};

