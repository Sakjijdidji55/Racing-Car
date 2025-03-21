#include"Sources.hpp"

int carsSpeed[TypeofCars] = { 0, 4, 4, 4, 4, 4 };
int speed = DefaultSpeed;
int NitrogenState = 0;
int Test[4][ROW * IMG_SIZE];
int PlayerBlood = 5;
int PlayerScore = 0;
int CanDown = 1;
int Enemy_x[4] = { 0 };

Queue* ExplodeTime = initQueue();
IMAGE bk[2];
IMAGE explode;
IMAGE money;
RoadLine lines[CountOfLines];
Car player;
Car enemy[CountofCars];
COLORREF transparentColor;
Coin coins[CountofCoins];

void StartMusic() {
	mciSendString(L"open music/bk.mp3 alias bgm", NULL, 0, NULL);
	mciSendString(L"play bgm repeat from 0", NULL, 0, NULL);
}

void CloseMusic() {
	mciSendString(L"close repeat", NULL, 0, NULL);
}

void WriteScore() {
	wchar_t score_text[20];
	_stprintf_s(score_text, sizeof(score_text) / sizeof(wchar_t), L"当前分数: %d", PlayerScore * 10);
	settextcolor(WHITE);
	settextstyle(15, 0, _T("幼圆"));
	setbkmode(TRANSPARENT);
	outtextxy(3 * IMG_SIZE + 5, 15, score_text);
}

void WriteBlood() {
	wchar_t score_text[20];
	_stprintf_s(score_text, sizeof(score_text) / sizeof(wchar_t), L"当前血量: %d", PlayerBlood * 10);
	settextcolor(WHITE);
	settextstyle(15, 0, _T("幼圆"));
	setbkmode(TRANSPARENT);
	outtextxy(3 * IMG_SIZE + 5, 40, score_text);
}

void LoadBackGround() {
	loadimage(&bk[0], _T("./image/grass.png"),IMG_SIZE,IMG_SIZE);
	loadimage(&bk[0], _T("./image/road.png"), IMG_SIZE, IMG_SIZE);
}

void LoadSource() {
	memset(Test, 0, sizeof(Test));
	LoadBackGround();
	LoadCars();
	loadimage(&explode, _T("./image/explore.png"), Car_WEIGHT + 20, Car_WEIGHT + 20);
	loadimage(&money, _T("./image/OIP-C.png"), Car_WEIGHT, Car_WEIGHT);
}

void DrawBackGround() {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (j == 0 || j == 3) {
				putimage(j * IMG_SIZE, i * IMG_SIZE, bk);
			}
			else {
				putimage(j * IMG_SIZE, i * IMG_SIZE, bk + 1);
			}
		}
	}
	//美化背景
	setlinestyle(PS_SOLID, 5);
	setlinecolor(BLACK);;
	line(IMG_SIZE, 0, IMG_SIZE, getheight());
	line(IMG_SIZE * 3, 0, IMG_SIZE * 3, getheight());
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID, 3);
	line(IMG_SIZE * 2, 0, IMG_SIZE * 2, getheight());
}

void initLines() {
	for (int i = 0; i < CountOfLines; i++) {
		lines[i].len = 48;
		if (i % 2 == 0) {
			lines[i].x = IMG_SIZE + IMG_SIZE / 2;
		}
		else {
			lines[i].x = IMG_SIZE * 2 + IMG_SIZE / 2;
		}
		lines[i].y = i * lines[i].len;
	}
}

void DrawLines() {
	for (int i = 0; i < CountOfLines; i++) {
		line(lines[i].x, lines[i].y, lines[i].x, lines[i].y + lines[i].len);
	}
}

void ChangeLines() {
	for (int i = CountOfLines - 1; i >= 0; i--) {
		lines[i].y += speed;
		if (lines[i].y >= getheight()) {
			int index = (i + 1) % CountOfLines;
			lines[i].y = lines[index].y - lines[i].len;
		}
	}
}

void initPlayer(int id) {
	int x = rand() % 2 + 1;
	initCar(&player, x * IMG_SIZE + 12, getheight() - 64 - 25, id);
}

void DrawPlayer() {
	DrawCar(player);
}

void MovePlayer() {
	if (GetAsyncKeyState(VK_UP)) {
		if (player.y > 0) {
			player.y -= DefaultSpeed;
		}
		else {
			player.y = 0;
		}
	}
	if (GetAsyncKeyState(VK_DOWN) && CanDown) {
		if (player.y < getheight() - Car_LENGTH - 16) {
			player.y += DefaultSpeed + speed;
		}
		else {
			player.y = getheight() - Car_LENGTH - 16;
		}
	}
	if (GetAsyncKeyState(VK_LEFT)) {
		if (player.x > IMG_SIZE) {
			player.x -= DefaultSpeed;
		}
		else {
			player.x = IMG_SIZE;
		}
	}
	if (GetAsyncKeyState(VK_RIGHT)) {
		if (player.x < 3 * IMG_SIZE - Car_WEIGHT) {
			player.x += DefaultSpeed;
		}
		else {
			player.x = 3 * IMG_SIZE - Car_WEIGHT;
		}
	}
	if (GetAsyncKeyState(VK_SPACE)) {
		if (speed < MaxSpeed) {
			speed += a;
		}
		CanDown = 0;
	}
	else {
		if (speed > DefaultSpeed && !NitrogenState) {
			speed = DefaultSpeed;
		}
		CanDown = 1;
	}


}

int NotVaild(int x, int y) {
	for (int i = y - Car_LENGTH - 10; i < y + Car_LENGTH + 10; i++) {
		if (Test[x][i]) {
			return 1;
		}
	}
	return 0;
}

int EnemynotVaild(int x) {
	return Enemy_x[x] == 1;
}

void initEnemy() {
	for (int i = 0; i < CountofCars; i++) {
		int id = rand() % 5 + 1;
		int x = rand() % 4;
		int y = (rand() % getheight()) / 2;
		while (EnemynotVaild(x)) {
			x = rand() % 4;
		}
		Enemy_x[x] = 1;
		initCar(enemy + i, IMG_SIZE + (IMG_SIZE / 2) * x + 12, y, id);
	}
}

void DrawEnemy() {
	for (int i = 0; i < CountofCars; i++) {
		DrawCar(enemy[i]);
	}
}

void MoveEnemy() {
	for (int i = 0; i < CountofCars; i++) {
		enemy[i].y += carsSpeed[enemy[i].id] + speed;
		if (enemy[i].y > getheight() - Car_LENGTH) {
			enemy[i].y = -Car_LENGTH;
			int origin_x = (enemy[i].x - 12 - IMG_SIZE) / (IMG_SIZE / 2);
			origin_x %= 4;
			Enemy_x[origin_x] = 0;
			int x = rand() % 4;
			while (EnemynotVaild(x)) {
				x = rand() % 4;
			}
			Enemy_x[x] = 1;
			enemy[i].x = IMG_SIZE + (IMG_SIZE / 2) * x + 12;
			enemy[i].id = rand() % 5 + 1;
		}
	}
}

int isInThisPlace(int x, int y, int checkx1, int checky1, int checkx2, int checky2) {
	return x >= checkx1 && x <= checkx2 && y >= checky1 && y <= checky2;
}

void EnemysisCrash() {
	for (int i = 0; i < CountofCars; i++) {
		if (isInThisPlace(player.x, player.y, enemy[i].x + 3, enemy[i].y + 4, enemy[i].x + Car_WEIGHT - 3, enemy[i].y + Car_LENGTH - 4) || isInThisPlace(player.x + Car_WEIGHT, player.y, enemy[i].x + 3, enemy[i].y + 4, enemy[i].x + Car_WEIGHT - 3, enemy[i].y + Car_LENGTH - 4) || isInThisPlace(player.x, player.y + Car_LENGTH, enemy[i].x + 3, enemy[i].y + 4, enemy[i].x + Car_WEIGHT - 3, enemy[i].y + Car_LENGTH - 4) || isInThisPlace(player.x + Car_WEIGHT, player.y + Car_LENGTH, enemy[i].x + 3, enemy[i].y + 4, enemy[i].x + Car_WEIGHT - 3, enemy[i].y + Car_LENGTH - 4)) {
			int origin_x = (enemy[i].x - 12 - IMG_SIZE) / (IMG_SIZE / 2);
			origin_x %= 4;
			Enemy_x[origin_x] = 0;
			enemy[i].y = -Car_LENGTH;
			int x = rand() % 4;
			while (EnemynotVaild(x)) {
				x = rand() % 4;
			}
			Enemy_x[x] = 1;
			enemy[i].x = IMG_SIZE + (IMG_SIZE / 2) * x + 12;
			enemy[i].id = rand() % 5 + 1;
			push(ExplodeTime, time(0), player.x - 10, player.y - 10);
			PlayerBlood--;
		}
	}
}

void EXPlODE(int x, int y) {
	PutAlphaImg(x, y, &explode);
}

void IsShouldExplore() {
	if (isEmpty(ExplodeTime)) {
		return;
	}
	for (int i = ExplodeTime->front; i != ExplodeTime->end; i = (i + 1) % MAX_SIZE) {
		if (time(0) - ExplodeTime->data[i] >= EXPLORESTATETIME) {
			pop_front(ExplodeTime);
		}
		EXPlODE(ExplodeTime->x[i], ExplodeTime->y[i]);
	}
}

void initCoins() {
	for (int i = 0; i < CountofCoins; i++) {
		int x = rand() % 4;
		int y = (rand() % getheight()) / 2;
		while (NotVaild(x, y)) {
			x = rand() % 4;
			y = (rand() % getheight()) / 2;
		}
		coins[i].x = IMG_SIZE + (IMG_SIZE / 2) * x + 12;
		coins[i].y = y;
		Test[x][y] = 1;
	}
}

void MoveCoins() {
	for (int i = CountofCoins - 1; i >= 0; i--) {
		coins[i].y += speed;
		if (coins[i].y >= getheight() - Car_WEIGHT) {
			coins[i].x = IMG_SIZE + (IMG_SIZE / 2) * (rand() % 4) + 12;
			coins[i].y = -rand() % Car_WEIGHT - Car_WEIGHT;
		}
	}
}

void DrawCoins() {
	for (int i = 0; i < CountofCoins; i++) {
		PutAlphaImg(coins[i].x, coins[i].y, &money);
	}
}

void EatCoins() {
	PlayerScore++;
}

void CoinsisCrash() {
	for (int i = 0; i < CountofCoins; i++) {
		if (isInThisPlace(player.x, player.y, coins[i].x, coins[i].y, coins[i].x + Car_WEIGHT, coins[i].y + Car_WEIGHT) || isInThisPlace(player.x + Car_WEIGHT, player.y, coins[i].x, coins[i].y, coins[i].x + Car_WEIGHT, coins[i].y + Car_WEIGHT) || isInThisPlace(player.x, player.y + Car_LENGTH, coins[i].x, coins[i].y, coins[i].x + Car_WEIGHT, coins[i].y + Car_WEIGHT) || isInThisPlace(player.x + Car_WEIGHT, player.y + Car_LENGTH, coins[i].x, coins[i].y, coins[i].x + Car_WEIGHT, coins[i].y + Car_WEIGHT)) {
			EatCoins();
			coins[i].x = IMG_SIZE + (IMG_SIZE / 2) * (rand() % 4) + 12;
			coins[i].y = -rand() % Car_WEIGHT - Car_WEIGHT;
		}
	}
}