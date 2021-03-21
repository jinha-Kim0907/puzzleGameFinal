#include <bangtal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

SceneID picture, background;
ObjectID start, reset, img1, img2, img3, img4, img5, img6, img7, img8, img9;
TimerID timer1;

int x[9] = { 300, 434, 568, 300, 434, 568, 300, 434, 568 };
int y[9] = { 400, 400, 400, 250, 250, 250, 100, 100, 100 };
int objectId[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
bool gameCheck = false;
char name[20];
int mixing{ 0 };
clock_t timeStart;
clock_t timeEnd;

const int mixNum = 100;

struct puzzle {
	int coord[9][2] = {
	{ 300, 400 }, { 434, 400 }, { 568, 400 },
	{ 300, 250 }, { 434, 250 }, { 568, 250 },
	{ 300, 100 }, { 434, 100 }, { 568, 100 }
	};
	int x, y;
	int currentPos[9][2] = { 0 };
	ObjectID obj[9] = { img1, img2, img3, img4, img5, img6, img7, img8, img9 };
};
puzzle myPuzzle;

//puzzle printPos() {
//	
//}
int objIndex(puzzle* puzzle, ObjectID object) {
	for (int i = 0; i < 16; i++) {
		if (puzzle->obj[i] == object) return i;
	}

	return -1;
}

void saveTocur(puzzle* puzzle) {
	for (int i{ 0 }; i < 9; i++) {
		for (int j{ 0 }; j < 2; j++) {
			puzzle->currentPos[i][j] = puzzle->coord[i][j];
		}
	}
}

void move(puzzle* puzzle, ObjectID object) {
	if (object == img1) {

	}
}

void mix(puzzle* puzzle) {
	srand(static_cast<unsigned int>(time(NULL)));
	int temp{ 0 };
	int buf1{ 0 };
	int buf2{ 0 };
	int mixCheck{ 0 };
	while (mixCheck < mixNum) {

		int firstNum{ 0 };
		firstNum = rand() % 9 + 1;

		temp = objectId[firstNum - 1];
		objectId[firstNum - 1] = objectId[objectId[8] - 1];
		objectId[objectId[8] - 1] = temp;

		buf1 = puzzle->coord[objectId[8] - 1][0];
		buf2 = puzzle->coord[objectId[8] - 1][1];
		puzzle->coord[objectId[8] - 1][0] = puzzle->coord[firstNum - 1][0];
		puzzle->coord[objectId[8] - 1][1] = puzzle->coord[firstNum - 1][1];
		puzzle->coord[firstNum - 1][0] = buf1;
		puzzle->coord[firstNum - 1][1] = buf2;

		for (int i{ 0 }; i < 9; i++) {
			printf("%d ", objectId[i]);
		}

		printf("\n%d %d \n", objectId[firstNum - 1], objectId[objectId[8] - 1]);

		for (int i{ 0 }; i < 9; i++) {
			for (int j{ 0 }; j < 2; j++) {
				puzzle->currentPos[i][j] = puzzle->coord[i][j];
			}
		}
		for (int i{ 0 }; i < 9; i++) {
			for (int j{ 0 }; j < 2; j++) {
				printf("%d ", puzzle->currentPos[i][j]);
			}
			printf("\n");
		}
		mixCheck++;
	}
}

bool check(puzzle* puzzle) {
	int check{ 0 };
	for (int i{ 0 }; i < 9; i++) {
		for (int j{ 0 }; j < 2; j++) {
			if (puzzle->coord[i][j] == puzzle->coord[i][j]) {
				check++;
			}
		}
	}
	if (check >= 18) return true;
	else return false;
}

void create() {
	background = createScene("back", "gyuri.png");
	picture = createScene("pic", "black.jpg");
	start = createObject("start1.jpg");
	reset = createObject("reset1.jpg");
	img1 = createObject("div1 (1).png");
	img2 = createObject("div1 (2).png");
	img3 = createObject("div1 (3).png");
	img4 = createObject("div1 (4).png");
	img5 = createObject("div1 (5).png");
	img6 = createObject("div1 (6).png");
	img7 = createObject("div1 (7).png");
	img8 = createObject("div1 (8).png");
	img9 = createObject("white.jpg");
}

void locateAndSave(puzzle* puzzle) {
	locateObject(img1, picture, puzzle->coord[0][0], puzzle->coord[0][1]);
	locateObject(img2, picture, puzzle->coord[1][0], puzzle->coord[1][1]);
	locateObject(img3, picture, puzzle->coord[2][0], puzzle->coord[2][1]);
	locateObject(img4, picture, puzzle->coord[3][0], puzzle->coord[3][1]);
	locateObject(img5, picture, puzzle->coord[4][0], puzzle->coord[4][1]);
	locateObject(img6, picture, puzzle->coord[5][0], puzzle->coord[5][1]);
	locateObject(img7, picture, puzzle->coord[6][0], puzzle->coord[6][1]);
	locateObject(img8, picture, puzzle->coord[7][0], puzzle->coord[7][1]);
	locateObject(img9, picture, puzzle->coord[8][0], puzzle->coord[8][1]);

	for (int i{ 0 }; i < 9; i++) {
		for (int j{ 0 }; j < 2; j++) {
			puzzle->currentPos[i][j] = puzzle->coord[i][j];
		}
	}

}

void scale() {
	scaleObject(img1, 0.5f);
	scaleObject(img2, 0.5f);
	scaleObject(img3, 0.5f);
	scaleObject(img4, 0.5f);
	scaleObject(img5, 0.5f);
	scaleObject(img6, 0.5f);
	scaleObject(img7, 0.5f);
	scaleObject(img8, 0.5f);
	scaleObject(img9, 0.5f);
}

void show() {
	showObject(img1);
	showObject(img2);
	showObject(img3);
	showObject(img4);
	showObject(img5);
	showObject(img6);
	showObject(img7);
	showObject(img8);
	showObject(img9);
}

void mouseCallback(ObjectID object, int x_, int y_, MouseAction action) {
	if (gameCheck) {
		if (check) {
			timeEnd = clock();
			printf("Time: %lf\n", (double)(timeEnd - timeStart) / CLOCKS_PER_SEC);
			sprintf_s(name, "%lf", (double)(timeEnd - timeStart) / CLOCKS_PER_SEC);
			showMessage(name);
			endGame();
		}
	}
	if (object == start) {
		timeStart = clock();
		hideObject(start);
		showObject(reset);
		mix(&myPuzzle);
		locateAndSave(&myPuzzle);
		scale();
		show();
		enterScene(picture);
	}

	if (object == reset) {
		timeEnd = clock();
		printf("Time: %.5lf\n", (double)(timeEnd - timeStart) / CLOCKS_PER_SEC);
		sprintf_s(name, "%.5lfÃÊ Áö³²", (double)(timeEnd - timeStart) / CLOCKS_PER_SEC);
		showMessage(name);
		mix(&myPuzzle);
		locateAndSave(&myPuzzle);
	}
	if (object == img1) {

		myPuzzle.coord[0][0] = x[8];
		myPuzzle.coord[0][1] = y[8];
		myPuzzle.coord[8][0] = x[0];
		myPuzzle.coord[8][1] = y[0];
		locateAndSave(&myPuzzle);

		//endGame();
	}
	/*
	if (object == img9) {
		showObject(start);
		setObjectImage(start, "reset1.jpg");
		locateObject(start, picture, 380, 50);

	}*/
}
void timerCallback(TimerID timer)
{
	mix(&myPuzzle);

	if (timer1 > 0) {
		--mixing;

		setTimer(timer1, 0.05f);
		startTimer(timer1);
	}
	else {
		hideObject(start);
		gameCheck = true;
	}
}


int main() {

	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	setMouseCallback(mouseCallback);
	setTimerCallback(timerCallback);
	timer1 = createTimer();
	create();
	locateObject(start, background, 380, 50);
	locateObject(reset, picture, 800, 300);
	showObject(start);
	hideObject(reset);

	startGame(background);
}