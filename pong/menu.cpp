#include <raylib.h>
#include "difficultyMenu.h"
#include "menu.h"
#include "helper.h"
#include "stages/stages.h"

void updateMenuScreen() {
	if (CheckCollisionPointRec(GetMousePosition(), singleplayerButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		CurrentGameState = GameState::DIFFICULTY_MENU;
		PlaySound(hitsoundMenuWeak);
	}

	if (CheckCollisionPointRec(GetMousePosition(), multiplayerButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		CurrentGameState = GameState::MULTIPLAYER;
		winnerState = 22;
		PlaySound(hitsoundMenuStrong);
	}

	if (CheckCollisionPointRec(GetMousePosition(), loremIpsumButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		CurrentGameState = GameState::STAGE_1;
		winnerState = 3;
		PlaySound(hitsoundMenuStrong);
		visitor.x = 9000;
		PlayMusicStream(stage1Music);
		GameInstance = new LoremInstance;
	}
}

void drawMenuScreen() {
	int PONG_TEXT_SIZE = MeasureText("PONG", 180);
	int SINGLEPLAYER_TEXT_SIZE = MeasureText("SINGLEPLAYER", 50);
	int MULTIPLAYER_TEXT_SIZE = MeasureText("MULTIPLAYER", 50);
	int LOREM_TEXT_SIZE = MeasureText("LOREM", 50);

	DrawText("PONG", 600 - PONG_TEXT_SIZE / 2, 100, 180, WHITE);

	if (CheckCollisionPointRec(GetMousePosition(), singleplayerButton)) DrawRectangleRec(singleplayerButton, WHITE);
	else DrawRectangleRec(singleplayerButton, GRAY);
	DrawText("SINGLEPLAYER", 600 - SINGLEPLAYER_TEXT_SIZE / 2, 525, 50, BLACK);

	if (CheckCollisionPointRec(GetMousePosition(), multiplayerButton)) DrawRectangleRec(multiplayerButton, WHITE);
	else DrawRectangleRec(multiplayerButton, GRAY);
	DrawText("MULTIPLAYER", 600 - MULTIPLAYER_TEXT_SIZE / 2, 725, 50, BLACK);

	if (CheckCollisionPointRec(GetMousePosition(), loremIpsumButton)) DrawRectangleRec(loremIpsumButton, WHITE);
	else DrawRectangleRec(loremIpsumButton, GRAY);
	DrawText("LOREM", 950 - LOREM_TEXT_SIZE / 2, 525, 50, BLACK);
}