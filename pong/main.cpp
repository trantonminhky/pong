#include <raylib.h>
#include <string>
#include <time.h>
#include <iostream>
#include "helper.h"
#include "singleplayer.h"
#include "difficultyMenu.h"
#include "multiplayer.h"
#include "menu.h"

int main() {
	InitWindow(1200, 1000, "pong");
	InitAudioDevice();
	
	srand(time(NULL));
	SetExitKey(KEY_NULL);

	SetTargetFPS(144);
	SetWindowIcon(icon);

	GameState CurrentGameState = GameState::LOADING;
	VolumeState CurrentVolumeState = VolumeState::MEDIUM;

	SetMasterVolume(0.5);
	std::cout << GetMasterVolume() << std::endl;

	BeginDrawing();
	ClearBackground(BLACK);
	DrawText("LOADING...", 600 - MeasureText("LOADING...", 180) / 2, 500, 180, WHITE);
	EndDrawing();

	init();

	PlayMusicStream(backgroundMusic);
		
	CurrentGameState = GameState::MENU;

	while (!WindowShouldClose()) {
		BeginDrawing();
		UpdateMusicStream(backgroundMusic);
		ClearBackground(BLACK);
		drawVolumeIcon(CurrentVolumeState);
		updateVolumeAndVolumeIcon(CurrentVolumeState);

		switch (CurrentGameState) {
		case GameState::MENU:
			resetState();
			updateMenuScreen(CurrentGameState);
			drawMenuScreen();
			break;

		case GameState::DIFFICULTY_MENU:
			updateDifficultyMenuScreen(CurrentGameState);
			drawDifficultyMenuScreen();
			break;

		case GameState::SINGLEPLAYER_EASY: // singleplayer easy
			updateSingleplayerScreen(50, CurrentGameState);
			drawSingleplayerScreen();
			break;

		case GameState::SINGLEPLAYER_MEDIUM: // singleplayer medium
			updateSingleplayerScreen(30, CurrentGameState);
			drawSingleplayerScreen();
			break;

		case GameState::SINGLEPLAYER_HARD: // singleplayer hard
			updateSingleplayerScreen(10, CurrentGameState);
			drawSingleplayerScreen();
			break;

		case GameState::MULTIPLAYER: // multiplayer
			updateMultiplayerScreen(CurrentGameState);
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