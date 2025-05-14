#pragma once

enum class GameState {
	MENU,
	DIFFICULTY_MENU,
	SINGLEPLAYER_EASY,
	SINGLEPLAYER_MEDIUM,
	SINGLEPLAYER_HARD,
	MULTIPLAYER
};
extern Sound hitsoundWeak;
extern Sound hitsoundStrong;
extern Sound explosion;

extern Rectangle singleplayerButton;
extern Rectangle multiplayerButton;

extern Rectangle easyButton;
extern Rectangle normalButton;
extern Rectangle hardButton;

extern int countdown;

extern int velocityX;
extern int velocityY;

extern int homeScore;
extern int visitorScore;

extern Rectangle ball;
extern Rectangle home;
extern Rectangle visitor;

extern GameState CurrentState;

bool isWithinX(int curX, int windowSizeX);
