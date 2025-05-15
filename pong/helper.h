#pragma once

enum class GameState {
	LOADING,
	MENU,
	DIFFICULTY_MENU,
	SINGLEPLAYER_EASY,
	SINGLEPLAYER_MEDIUM,
	SINGLEPLAYER_HARD,
	MULTIPLAYER
};
extern Sound hitsoundWeak;
extern Sound hitsoundStrong;
extern Sound hitsoundMenuWeak;
extern Sound hitsoundMenuStrong;
extern Sound explosion;
extern Music backgroundMusic;
extern Image icon;

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
void resetState();
void init();