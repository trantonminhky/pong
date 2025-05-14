#include <raylib.h>

int launchDifficultyMenu() {
	const int PONG_TEXT_SIZE = MeasureText("PONG", 180);
	const int EASY_TEXT_SIZE = MeasureText("EASY", 50);
	const int NORMAL_TEXT_SIZE = MeasureText("NORMAL", 50);
	const int HARD_TEXT_SIZE = MeasureText("HARD", 50);

	Rectangle easyButton = { 350, 400, 500, 100 };
	Rectangle normalButton = { 350, 600, 500, 100 };
	Rectangle hardButton = { 350, 800, 500, 100 };

	while (!WindowShouldClose()) {
		if (CheckCollisionPointRec(GetMousePosition(), easyButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return 1;
		if (CheckCollisionPointRec(GetMousePosition(), normalButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return 2;
		if (CheckCollisionPointRec(GetMousePosition(), hardButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return 3;

		BeginDrawing();
		ClearBackground(BLACK);

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

		EndDrawing();
	}

	return -1;
}