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

enum class VolumeState {
	MUTE,
	QUIET,
	MEDIUM,
	LOUD
};

// 11 - singleplayer instruction
// 22 - multiplayer instruction
// 1 - P1 wins
// 2 - P2 wins
extern int winnerState;

extern Sound hitsoundWeak;
extern Sound hitsoundStrong;
extern Sound hitsoundMenuWeak;
extern Sound hitsoundMenuStrong;
extern Sound explosion;
extern Music backgroundMusic;

extern Image icon;

extern Texture2D volume_mute;
extern Texture2D volume_quiet;
extern Texture2D volume_medium;
extern Texture2D volume_loud;

extern Rectangle singleplayerButton;
extern Rectangle multiplayerButton;

extern Rectangle easyButton;
extern Rectangle normalButton;
extern Rectangle hardButton;

extern Rectangle volumeHitbox;

extern int countdown;

extern int velocityX;
extern int velocityY;

extern int homeScore;
extern int visitorScore;

extern Rectangle ball;
extern Rectangle home;
extern Rectangle visitor;

extern GameState CurrentGameState;
extern VolumeState CurrentVolumeState;

bool isWithinX(int curX, int windowSizeX);
void resetState();
void init();
void drawVolumeIcon();
void updateVolumeAndVolumeIcon();
void drawWinnerOrInstruction(int status);