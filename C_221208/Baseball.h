#pragma once
#include "Base.h"
#include "UsefulType.h"

enum class GameState {
	SETTING,
	INPUT,
	CHECK,
	CLEAR,
	GAME_OVER
};

class Baseball : public Base
{
	void SetComputerNumbers(uint* arr, const uint& length, const uint& min_num, const uint& max_num);
	void SetPlayerNumbers(uint* arr, const uint& length, const uint& min_num, const uint& max_num);
	uint InputNumberInRange(const uint& min_num, const uint& max_num);
	GameState CheckState(uint* computerNumbers,	uint* playerNumbers, uint& outCount, uint& attemptCount, const uint& length);
public:
	// Base을(를) 통해 상속됨
	virtual void Run() override;
};

