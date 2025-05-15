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

void drawVolumeIcon(VolumeState CurrentVolumeState) {
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

void updateVolumeAndVolumeIcon(VolumeState &CurrentVolumeState) {
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
	backgroundMusic = LoadMusicStream("./assets/vivaldi.mp3");
	hitsoundWeak = LoadSound("./assets/hit_weak.wav");
	hitsoundStrong = LoadSound("./assets/hit_strong.wav");
	hitsoundMenuWeak = LoadSound("./assets/menu_hit_weak.wav");
	hitsoundMenuStrong = LoadSound("./assets/menu_hit_strong.wav");
	explosion = LoadSound("./assets/explosion.wav");

	icon = LoadImage("./assets/window_icon.png");

	volume_mute = LoadTexture("./assets/volume_mute.png");
	volume_quiet = LoadTexture("./assets/volume_quiet.png");
	volume_medium = LoadTexture("./assets/volume_medium.png");
	volume_loud = LoadTexture("./assets/volume_loud.png");

	backgroundMusic.looping = true;
	SetWindowIcon(icon);
}

Rectangle singleplayerButton = { 350, 500, 500, 100 };
Rectangle multiplayerButton = { 350, 700, 500, 100 };

Rectangle easyButton = { 350, 400, 500, 100 };
Rectangle normalButton = { 350, 600, 500, 100 };
Rectangle hardButton = { 350, 800, 500, 100 };

Rectangle volumeHitbox = { 10, 900, 96, 96 };

int countdown = 180;

int velocityX = 0; // initial ball velocity
int velocityY = 8;

int homeScore = 0;
int visitorScore = 0;

Rectangle ball = { 590, 490, 20, 20 };
Rectangle home = { 525, 900, 150, 10 };
Rectangle visitor = { 525, 100, 150, 10 };

Sound hitsoundWeak = { 0 };
Sound hitsoundStrong = { 0 };
Sound hitsoundMenuWeak = { 0 };
Sound hitsoundMenuStrong = { 0 };
Sound explosion = { 0 };
Music backgroundMusic = { 0 };
Image icon = { 0 };

Texture2D volume_mute = { 0 };
Texture2D volume_quiet = { 0 };
Texture2D volume_medium = { 0 };
Texture2D volume_loud = { 0 };