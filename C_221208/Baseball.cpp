#include "Baseball.h"
#include "UsefulFunc.h"
#include <time.h>

#define LENGTH 3
#define MAX_ATTEMP_NUM 10
#define MAX_OUT_NUM 3
#define MIN_NUMBER 1
#define MAX_NUMBER 9


void Baseball::SetComputerNumbers(uint* arr, const uint& length = LENGTH, const uint& min_num = MIN_NUMBER, const uint& max_num = MAX_NUMBER)
{
	int numbers[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	GetRandomsNoOverlap(numbers, (uint)(sizeof(numbers)/sizeof(uint)), length);
	for (uint i = 0; i < length; i++) {
		arr[i] = numbers[i];
	}
}

void Baseball::SetPlayerNumbers(uint* arr, const uint& length = LENGTH, const uint& min_num = MIN_NUMBER, const uint& max_num = MAX_NUMBER)
{
	for(uint i = 0; i < length; i++)
		arr[i] = InputNumberInRange(MIN_NUMBER, MAX_NUMBER);

	printf("PlayerNumber : ");
	for (uint i = 0; i < length; i++)
		printf(" %d", arr[i]);
	printf("\n");
}

uint Baseball::InputNumberInRange(const uint& min_num = MIN_NUMBER, const uint& max_num = MAX_NUMBER)
{
	uint inputNum = 0;
	while (true) {
		printf("숫자를 입력하시오(%d~%d) -> ", min_num, max_num);
		
		scanf_s("%d", &inputNum);

		if (min_num <= inputNum && inputNum <= max_num)
			break;
		else
			printf("입력 범위 외!\n");
	}

	return inputNum;
}

GameState Baseball::CheckState(uint* computerNumbers, uint* playerNumbers, uint& outCount, uint& attemptCount, const uint& length = LENGTH)
{
	uint strike = 0, ball = 0;

	for (uint i = 0; i < length; i++) {
		for (uint j = 0; j < length; j++) {
			if (computerNumbers[i] == playerNumbers[j])
				i == j ? strike++ : ball++;
		}
	}

	if (strike == 0 && ball == 0) {
		printf("%d아웃\n", ++outCount);
		if (outCount == 3)
			return GameState::GAME_OVER;
	}
	else
		printf("%dS %dB\n", strike, ball);
	
	if (strike == 3)
		return GameState::CLEAR;


	printf("%d번 시도했습니다. 남은 시도 횟수 : %d\n", attemptCount, MAX_ATTEMP_NUM-(++attemptCount));
	if (attemptCount == MAX_ATTEMP_NUM)
		return GameState::GAME_OVER;

	return GameState::INPUT;
}

void Baseball::Run()
{
	uint computerNumbers[LENGTH];
	uint playerNumbers[LENGTH];
	GameState gameState = GameState::SETTING;
	uint outCnt = 0, attempCnt = 0;

	srand((uint)time(NULL));

	while (1) {
		switch (gameState)
		{
		case GameState::SETTING:
			SetComputerNumbers(computerNumbers);
			gameState = GameState::INPUT;
			break;
		case GameState::INPUT:
			SetPlayerNumbers(playerNumbers);
			gameState = GameState::CHECK;
			break;
		case GameState::CHECK:
			gameState = CheckState(computerNumbers, playerNumbers, outCnt, attempCnt);
			break;
		case GameState::CLEAR:
			break;
		case GameState::GAME_OVER:
			return;
		default:
			break;
		}
	}
}
