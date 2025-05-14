#include <raylib.h>
#include "helper.h"

bool isWithinX(int curX, int windowSizeX) {
	return (curX >= 0 && curX <= windowSizeX - 20); // accounts for rectangle size
}

void resetState() {
	countdown = 180;

	velocityX = 0; // initial ball velocity
	velocityY = 8;

	homeScore = 0;
	visitorScore = 0;

	ball = { 590, 490, 20, 20 };
	home = { 525, 900, 150, 10 };
	visitor = { 525, 100, 150, 10 };
}

Rectangle singleplayerButton = { 350, 500, 500, 100 };
Rectangle multiplayerButton = { 350, 700, 500, 100 };

Rectangle easyButton = { 350, 400, 500, 100 };
Rectangle normalButton = { 350, 600, 500, 100 };
Rectangle hardButton = { 350, 800, 500, 100 };

int countdown = 180;

int velocityX = 0; // initial ball velocity
int velocityY = 8;

int homeScore = 0;
int visitorScore = 0;

Rectangle ball = { 590, 490, 20, 20 };
Rectangle home = { 525, 900, 150, 10 };
Rectangle visitor = { 525, 100, 150, 10 };