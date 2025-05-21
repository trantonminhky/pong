#include <raylib.h>
#include <string>
#include <time.h>
#include <iostream>
#include "helper.h"
#include "singleplayer.h"
#include "difficultyMenu.h"
#include "multiplayer.h"
#include "menu.h"

#ifdef NDEBUG

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#endif


int main() {
	InitWindow(1200, 1000, "pong");
	InitAudioDevice();
	
	srand(time(NULL));
	SetExitKey(KEY_NULL);

	SetTargetFPS(144);
	SetWindowIcon(icon);

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
		if (IsKeyPressed(KEY_ESCAPE)) {
			CurrentGameState = GameState::MENU;
			resetState();
		}

		BeginDrawing();
		ClearBackground(BLACK);
		drawVolumeIcon();
		updateVolumeAndVolumeIcon();

		switch (CurrentGameState) {
		case GameState::MENU:
			UpdateMusicStream(backgroundMusic);
			updateMenuScreen();
			drawMenuScreen();
			break;

		case GameState::DIFFICULTY_MENU:
			UpdateMusicStream(backgroundMusic);
			updateDifficultyMenuScreen();
			drawDifficultyMenuScreen();
			break;

		case GameState::SINGLEPLAYER_EASY: // singleplayer easy
			UpdateMusicStream(backgroundMusic);
			GameInstance->updateSingleplayerScreen(50, stageElapsedTime);
			GameInstance->drawSingleplayerScreen();
			break;

		case GameState::SINGLEPLAYER_MEDIUM: // singleplayer medium
			UpdateMusicStream(backgroundMusic);
			GameInstance->updateSingleplayerScreen(30, stageElapsedTime);
			GameInstance->drawSingleplayerScreen();
			break;

		case GameState::SINGLEPLAYER_HARD: // singleplayer hard
			UpdateMusicStream(backgroundMusic);
			GameInstance->updateSingleplayerScreen(10, stageElapsedTime);
			GameInstance->drawSingleplayerScreen();
			break;

		case GameState::STAGE_1:
			GameInstance->updateSingleplayerScreen(30, stageElapsedTime);
			GameInstance->drawSingleplayerScreen();
			break;

		case GameState::MULTIPLAYER: // multiplayer
			UpdateMusicStream(backgroundMusic);
			updateMultiplayerScreen();
			drawMultiplayerScreen();
			break;

		default:
			EndDrawing();
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