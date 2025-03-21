#include"Body.hpp"

int frameInterval = 1000 / FPS;
clock_t startTime, endTime;

void setFPSonTheGame(int diff) {
	if (diff < frameInterval) {
		Sleep( frameInterval - diff );
	}
}

int main() {

	initGame();

	UserStart();

	StartGame();

	while (true) {
		startTime = clock();

		update();

		isGameOver();

		endTime = clock();

		int DiffofTime = endTime - startTime;

		setFPSonTheGame(DiffofTime);
	}

	CloseGame();

	return 0;
}