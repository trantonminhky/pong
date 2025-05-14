#include <raylib.h>
#include <string>
#include <time.h>
#include "helper.h"
#include "singleplayer.h"
#include "difficultyMenu.h"
#include "multiplayer.h"
#include "menu.h"

Sound hitsoundWeak = { 0 };
Sound hitsoundStrong = { 0 };
Sound explosion = { 0 };

int main() {
	InitWindow(1200, 1000, "pong");
	InitAudioDevice();
	
	srand(time(NULL));

	Music backgroundMusic = LoadMusicStream("./assets/vivaldi.mp3");
	hitsoundWeak = LoadSound("./assets/hit_weak.wav");
	hitsoundStrong = LoadSound("./assets/hit_strong.wav");
	explosion = LoadSound("./assets/explosion.wav");
	Image icon = LoadImage("./assets/pixil-frame-0.png");
	backgroundMusic.looping = true;

	SetTargetFPS(144);
	SetWindowIcon(icon);

	PlayMusicStream(backgroundMusic);
		
	GameState CurrentState = GameState::MENU;

	while (!WindowShouldClose()) {
		BeginDrawing();
		UpdateMusicStream(backgroundMusic);
		ClearBackground(BLACK);
		switch (CurrentState) {
		case GameState::MENU:
			updateMenuScreen(CurrentState);
			drawMenuScreen();
			break;

		case GameState::DIFFICULTY_MENU:
			updateDifficultyMenuScreen(CurrentState);
			drawDifficultyMenuScreen();
			break;

		case GameState::SINGLEPLAYER_EASY: // singleplayer easy
			updateSingleplayerScreen(50);
			drawSingleplayerScreen();
			break;

		case GameState::SINGLEPLAYER_MEDIUM: // singleplayer medium
			updateSingleplayerScreen(30);
			drawSingleplayerScreen();
			break;

		case GameState::SINGLEPLAYER_HARD: // singleplayer hard
			updateSingleplayerScreen(10);
			drawSingleplayerScreen();
			break;

		case GameState::MULTIPLAYER: // multiplayer
			updateMultiplayerScreen();
			drawMultiplayerScreen();
			break;

		default:
			UnloadMusicStream(backgroundMusic);
			CloseAudioDevice();
			CloseWindow();
			return 0;
		}
		EndDrawing();
	}

	UnloadMusicStream(backgroundMusic);
	CloseAudioDevice();
	CloseWindow();
	return 0;
}