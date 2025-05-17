#include <raylib.h>
#include "difficultyMenu.h"
#include "menu.h"
#include "helper.h"
#include "singleplayer.h"

void updateDifficultyMenuScreen() {
	if (CheckCollisionPointRec(GetMousePosition(), easyButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		CurrentGameState = GameState::SINGLEPLAYER_EASY;
		winnerState = 11;
		PlaySound(hitsoundMenuStrong);
		GameInstance = new SingleplayerInstance;
	}
	if (CheckCollisionPointRec(GetMousePosition(), normalButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		CurrentGameState = GameState::SINGLEPLAYER_MEDIUM;
		winnerState = 11;
		PlaySound(hitsoundMenuStrong);
		GameInstance = new SingleplayerInstance;
	}
	if (CheckCollisionPointRec(GetMousePosition(), hardButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		CurrentGameState = GameState::SINGLEPLAYER_HARD;
		winnerState = 11;
		PlaySound(hitsoundMenuStrong);
		GameInstance = new SingleplayerInstance;
	}
}

void drawDifficultyMenuScreen() {
	int PONG_TEXT_SIZE = MeasureText("PONG", 180);
	int EASY_TEXT_SIZE = MeasureText("EASY", 50);
	int NORMAL_TEXT_SIZE = MeasureText("NORMAL", 50);
	int HARD_TEXT_SIZE = MeasureText("HARD", 50);

	DrawText("PONG", 600 - PONG_TEXT_SIZE / 2, 100, 180, WHITE);

	if (CheckCollisionPointRec(GetMousePosition(), easyButton)) DrawRectangleRec(easyButton, WHITE);
	else DrawRectangleRec(easyButton, GRAY);
	DrawText("EASY", 600 - EASY_TEXT_SIZE / 2, 425, 50, BLACK);

	if (CheckCollisionPointRec(GetMousePosition(), normalButton)) DrawRectangleRec(normalButton, WHITE);
	else DrawRectangleRec(normalButton, GRAY);
	DrawText("NORMAL", 600 - NORMAL_TEXT_SIZE / 2, 625, 50, BLACK);

	if (CheckCollisionPointRec(GetMousePosition(), hardButton)) DrawRectangleRec(hardButton, WHITE);
	else DrawRectangleRec(hardButton, GRAY);
	DrawText("HARD", 600 - HARD_TEXT_SIZE / 2, 825, 50, BLACK);
}