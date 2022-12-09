#pragma once
/*
���� 2 : �����̵� ���� ����
4*4 �����̵�
w a s d Ű�� 0�� �����¿�� �̵�

//��� : ���� �ð� �߰�

00 01 02 03

04 05 06 07

08 09 10 11

12 13 14 15

������� �����ϴ� ���� �����ϸ� �¸�
*/
#include "Base.h"
#include <time.h>
#include <string>

class Homework2 : public Base
{
	static const int BOARD_SIZE = 4;
	static const int INIT_SHUFFLE = 500;
	static const int SEC = 1000;
	static const time_t TIME_LIMIT = 2000*SEC; //��

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
	// Base��(��) ���� ��ӵ�
	virtual void Run() override;
};

