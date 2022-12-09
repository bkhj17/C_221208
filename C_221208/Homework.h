#pragma once
#include "Base.h"
#include <string>

class Homework : public Base
{
	static const int BOARD_SIZE = 5;
	static const int WINNING_SCORE = 5;
	static const int MIN_NUM = 1;
	static const int MAX_NUM = 100;
	static const int MAX_ATTEMPT = 120;
private:
	//플레이 관련
	bool hitBoard[BOARD_SIZE][BOARD_SIZE];
	int board[BOARD_SIZE][BOARD_SIZE];

	int input = 0;			//입력된 문자
	void Input();

	int cnt_attempt = 0;	//현재까지의 시도 횟수
	void Check();
	bool CheckHit(int input);

	int logArr[MAX_ATTEMPT] = {0};
	int GetLastInput() { cnt_attempt <= 0 ? 0 : logArr[cnt_attempt - 1]; }
	int GetCountBingo();

	void Win();
	void GameOver();
private:
	//출력 관련
	void PrintAttempt();
	void PrintLog();
	void PrintBoard();

	bool renderOrder = false;
	int sleepTime = 0;
	inline void CallRender(int sleep = 0) {
		sleepTime = sleep;
		renderOrder = true;
	}
	std::string renderMessage;
private:
	enum class GameState {
		INIT,
		INPUT,
		CHECK,
		WIN,
		GAME_OVER,
		EXIT
	};
	GameState gameState = GameState::INIT;
	void Init();
	void Update();
	void Render();
public:
	// Base을(를) 통해 상속됨
	virtual void Run() override;
};

