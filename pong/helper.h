#pragma once
#include "skills.h"
#include <string>

enum class GameState {
	LOADING,
	MENU,
	DIFFICULTY_MENU,
	SINGLEPLAYER_EASY,
	SINGLEPLAYER_MEDIUM,
	SINGLEPLAYER_HARD,
	MULTIPLAYER,
	STAGE_1
};

enum class StageState {
	STAGE_OPENING,
	STAGE_SUMMON,
	STAGE_BOSS
};

enum class VolumeState {
	MUTE,
	QUIET,
	MEDIUM,
	LOUD
};

class Instance {
public:
	virtual void updateSingleplayerScreen(int failureRate, float &elapsed) = 0;
	virtual void drawSingleplayerScreen() = 0;
};

// assets
extern Sound hitsoundWeak;
extern Sound hitsoundStrong;
extern Sound hitsoundMenuWeak;
extern Sound hitsoundMenuStrong;
extern Sound explosion;
extern Sound failsound;
extern Sound subsound;
extern Sound ultsound;

extern Music backgroundMusic;
extern Music stage1Music;

extern Image icon;

extern Texture2D volume_mute;
extern Texture2D volume_quiet;
extern Texture2D volume_medium;
extern Texture2D volume_loud;

// objects
extern Rectangle ball;
extern Rectangle home;
extern Rectangle visitor;

// interface
extern Rectangle singleplayerButton;
extern Rectangle multiplayerButton;
extern Rectangle loremIpsumButton;

extern Rectangle easyButton;
extern Rectangle normalButton;
extern Rectangle hardButton;

extern Rectangle volumeHitbox;

// gameplay data
// 11 - singleplayer instruction
// 22 - multiplayer instruction
// 1 - P1 wins
// 2 - P2 wins
// 3 - in progress
extern int winnerState;

extern int countdown;

extern int velocityX;
extern int velocityY;

extern int homeSpeed;
extern int visitorSpeed;

extern int homeScore;
extern int visitorScore;

extern int homeMana;
// extern int visitorMana;

extern int homeSkillDurationLeft;
// extern int visitorSkillDurationLeft;

extern Skills CurrentSkillInUse;
extern float stageElapsedTime;

// meta states
extern GameState CurrentGameState;
extern VolumeState CurrentVolumeState;
extern lastSavedState LastSavedState;
extern StageState CurrentStageState;
extern Instance* GameInstance;

bool isWithinX(int curX, int windowSizeX);
void resetState();
void init();
void drawVolumeIcon();
void updateVolumeAndVolumeIcon();
void drawWinnerOrInstruction(int status);
void increaseMana(int& mana);
bool depleteMana(int& mana, int depleteAmount);