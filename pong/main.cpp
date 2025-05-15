#include <raylib.h>
#include <string>
#include <time.h>
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

	GameState CurrentState = GameState::LOADING;

	BeginDrawing();
	ClearBackground(BLACK);
	DrawText("LOADING...", 600 - MeasureText("LOADING...", 180) / 2, 500, 180, WHITE);
	EndDrawing();

	init();

	PlayMusicStream(backgroundMusic);
		
	CurrentState = GameState::MENU;

	while (!WindowShouldClose()) {
		BeginDrawing();
		UpdateMusicStream(backgroundMusic);
		ClearBackground(BLACK);
		switch (CurrentState) {
		case GameState::MENU:
			resetState();
			updateMenuScreen(CurrentState);
			drawMenuScreen();
			break;

		case GameState::DIFFICULTY_MENU:
			updateDifficultyMenuScreen(CurrentState);
			drawDifficultyMenuScreen();
			break;

		case GameState::SINGLEPLAYER_EASY: // singleplayer easy
			updateSingleplayerScreen(50, CurrentState);
			drawSingleplayerScreen();
			break;

		case GameState::SINGLEPLAYER_MEDIUM: // singleplayer medium
			updateSingleplayerScreen(30, CurrentState);
			drawSingleplayerScreen();
			break;

		case GameState::SINGLEPLAYER_HARD: // singleplayer hard
			updateSingleplayerScreen(10, CurrentState);
			drawSingleplayerScreen();
			break;

		case GameState::MULTIPLAYER: // multiplayer
			updateMultiplayerScreen(CurrentState);
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