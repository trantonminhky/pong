#include <raylib.h>
#include "difficultyMenu.h"

int launchMenu() {
	const int PONG_TEXT_SIZE = MeasureText("PONG", 180);
	const int SINGLEPLAYER_TEXT_SIZE = MeasureText("SINGLEPLAYER", 50);
	const int MULTIPLAYER_TEXT_SIZE = MeasureText("MULTIPLAYER", 50);

	Rectangle singleplayerButton = { 350, 500, 500, 100 };
	Rectangle multiplayerButton = { 350, 700, 500, 100 };

	while (!WindowShouldClose()) {
		if (CheckCollisionPointRec(GetMousePosition(), singleplayerButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return launchDifficultyMenu();
		if (CheckCollisionPointRec(GetMousePosition(), multiplayerButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return 4;

		BeginDrawing();
		ClearBackground(BLACK);

		DrawText("PONG", 600 - PONG_TEXT_SIZE / 2, 100, 180, WHITE);

		if (CheckCollisionPointRec(GetMousePosition(), singleplayerButton)) DrawRectangleRec(singleplayerButton, WHITE);
		else DrawRectangleRec(singleplayerButton, GRAY);
		DrawText("SINGLEPLAYER", 600 - SINGLEPLAYER_TEXT_SIZE / 2, 525, 50, BLACK);

		if (CheckCollisionPointRec(GetMousePosition(), multiplayerButton)) DrawRectangleRec(multiplayerButton, WHITE);
		else DrawRectangleRec(multiplayerButton, GRAY);
		DrawText("MULTIPLAYER", 600 - MULTIPLAYER_TEXT_SIZE / 2, 725, 50, BLACK);

		EndDrawing();
	}

	return -1;
}