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
		BeginDrawing();
		if (CurrentSkillInUse != Skills::HOME_ULT) UpdateMusicStream(backgroundMusic);
		ClearBackground(BLACK);
		drawVolumeIcon();
		updateVolumeAndVolumeIcon();

		switch (CurrentGameState) {
		case GameState::MENU:
			resetState();
			updateMenuScreen();
			drawMenuScreen();
			break;

		case GameState::DIFFICULTY_MENU:
			updateDifficultyMenuScreen();
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