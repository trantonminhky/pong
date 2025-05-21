#include <raylib.h>
#include <random>
#include <string>
#include "helper.h"
#include "skills.h"

bool isWithinX(int curX, int windowSizeX) {
	return (curX >= 0 && curX <= windowSizeX - 20); // accounts for rectangle size
}

void resetState() {
	winnerState = 0;
	countdown = 300;

	velocityX = 0; // initial ball velocity
	velocityY = 8;

	homeScore = 0;
	visitorScore = 0;

	homeSpeed = 10;
	visitorSpeed = 10;

	homeSkillDurationLeft = 0;

	homeMana = 0;

	ball = { 590, 490, 20, 20 };
	home = { 525, 900, 150, 10 };
	visitor = { 525, 100, 150, 10 };

	LastSavedState = { 0 };
	delete GameInstance;

	CurrentSkillInUse = Skills::NONE;
	stageElapsedTime = 0;
	CurrentStageState = StageState::STAGE_OPENING;
}

void drawVolumeIcon() {
	switch (CurrentVolumeState) {
	case VolumeState::MUTE:
		DrawTextureEx(volume_mute, { 10, 900 }, 0, 3, WHITE);
		break;

	case VolumeState::QUIET:
		DrawTextureEx(volume_quiet, { 10, 900 }, 0, 3, WHITE);
		break;

	case VolumeState::MEDIUM:
		DrawTextureEx(volume_medium, { 10, 900 }, 0, 3, WHITE);
		break;

	case VolumeState::LOUD:
		DrawTextureEx(volume_loud, { 10, 900 }, 0, 3, WHITE);
		break;

	default:
		return;
	}
}

void updateVolumeAndVolumeIcon() {
	if (CheckCollisionPointRec(GetMousePosition(), volumeHitbox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		switch (CurrentVolumeState) {
		case VolumeState::MUTE:
			SetMasterVolume(0.2);
			CurrentVolumeState = VolumeState::QUIET;
			break;

		case VolumeState::QUIET:
			SetMasterVolume(0.5);
			CurrentVolumeState = VolumeState::MEDIUM;
			break;

		case VolumeState::MEDIUM:
			SetMasterVolume(0.8);
			CurrentVolumeState = VolumeState::LOUD;
			break;

		case VolumeState::LOUD:
			SetMasterVolume(0);
			CurrentVolumeState = VolumeState::MUTE;
			break;
		}
	}
}

void init() {
	backgroundMusic = LoadMusicStream("./assets/music/lolk_x.mp3");
	stage1Music = LoadMusicStream("./assets/music/wbawc_5.mp3");
	hitsoundWeak = LoadSound("./assets/sfx/hit_weak.wav");
	hitsoundStrong = LoadSound("./assets/sfx/hit_strong.wav");
	hitsoundMenuWeak = LoadSound("./assets/sfx/menu_hit_weak.wav");
	hitsoundMenuStrong = LoadSound("./assets/sfx/menu_hit_strong.wav");
	explosion = LoadSound("./assets/sfx/explosion.wav");
	failsound = LoadSound("./assets/sfx/skill_use_fail.wav");
	subsound = LoadSound("./assets/sfx/sub.wav");
	ultsound = LoadSound("./assets/sfx/ult.wav");

	icon = LoadImage("./assets/sprites/window_icon.png");

	volume_mute = LoadTexture("./assets/sprites/volume_mute.png");
	volume_quiet = LoadTexture("./assets/sprites/volume_quiet.png");
	volume_medium = LoadTexture("./assets/sprites/volume_medium.png");
	volume_loud = LoadTexture("./assets/sprites/volume_loud.png");

	backgroundMusic.looping = true;
	stage1Music.looping = true;
	SetWindowIcon(icon);
}


// 11 - instruction singleplayer
// 22 - instruction multiplayer
// 1 - P1 wins
// 2 - P2 wins
// else do not draw anything

void drawWinnerOrInstruction(int status) {
	switch (status) {
	case 11:
		DrawText("A - D to move\nESC to exit\nGood luck!", 400, 700, 60, WHITE);
		break;

	case 22:
		DrawText("A - D to move Player 1\nArrow keys to move Player 2\nESC to exit\nGood luck!", 200, 650, 60, WHITE);
		break;

	case 1:
		DrawText("Player 1 wins!", 400, 700, 60, WHITE);
		break;

	case 2:
		DrawText("Player 2 wins!", 400, 300, 60, WHITE);
		break;
	}
}

// this function is invoked everytime a paddle hits the ball, increasing randomly from 5 to 15 (max mana possible is 100)
void increaseMana(int &mana) {
	mana += std::min((rand() % 11) + 5, 100 - mana);
}

bool depleteMana(int& mana, int depleteAmount) {
	if (mana < depleteAmount) return false;
	mana -= depleteAmount;
	return true;
}

Rectangle singleplayerButton = { 350, 500, 500, 100 };
Rectangle multiplayerButton = { 350, 700, 500, 100 };
Rectangle loremIpsumButton = { 950, 500, 100, 100 };

Rectangle easyButton = { 350, 400, 500, 100 };
Rectangle normalButton = { 350, 600, 500, 100 };
Rectangle hardButton = { 350, 800, 500, 100 };

Rectangle volumeHitbox = { 10, 900, 96, 96 };

int countdown = 300;

int homeSpeed = 10;
int visitorSpeed = 10;

int velocityX = 0; // initial ball velocity
int velocityY = 8;

int homeScore = 0;
int visitorScore = 0;

int homeMana = 0;

int homeSkillDurationLeft = 0;
float stageElapsedTime = 0;

Rectangle ball = { 590, 490, 20, 20 };
Rectangle home = { 525, 900, 150, 10 };
Rectangle visitor = { 525, 100, 150, 10 };

Sound hitsoundWeak = { 0 };
Sound hitsoundStrong = { 0 };
Sound hitsoundMenuWeak = { 0 };
Sound hitsoundMenuStrong = { 0 };
Sound explosion = { 0 };
Sound failsound = { 0 };
Sound subsound = { 0 };
Sound ultsound = { 0 };

Music backgroundMusic = { 0 };
Music stage1Music = { 0 };
Image icon = { 0 };

Texture2D volume_mute = { 0 };
Texture2D volume_quiet = { 0 };
Texture2D volume_medium = { 0 };
Texture2D volume_loud = { 0 };

int winnerState = 0;

GameState CurrentGameState = GameState::LOADING;
VolumeState CurrentVolumeState = VolumeState::MEDIUM;
StageState CurrentStageState = StageState::STAGE_OPENING;
Instance* GameInstance = nullptr;

lastSavedState LastSavedState = { 0 };
Skills CurrentSkillInUse = Skills::NONE;