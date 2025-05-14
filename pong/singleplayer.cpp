#include <raylib.h>
#include <string>
#include "helper.h"

void launchSingleplayer(int failureRate) { // failureRate varies from 0-100
	int countdown = 180;

	int velocityX = 0; // initial ball velocity
	int velocityY = 5;

	int homeScore = 0;
	int visitorScore = 0;

	Rectangle ball = { 590, 490, 20, 20 };
	Rectangle home = { 525, 900, 150, 10 };
	Rectangle visitor = { 525, 100, 150, 10 };

	while (!WindowShouldClose()) {
		int random = rand() % 100 + 1;
		if (countdown < 0) {
			if (IsKeyDown(KEY_A)) home.x -= home.x >= 0 ? 10 : 0; // A - move left, D - move right
			if (IsKeyDown(KEY_D)) home.x += home.x + home.width <= 1200 ? 10 : 0;

			if (ball.x < visitor.x + visitor.width / 4) {
				visitor.x -= (visitor.x >= 0 && (random >= failureRate)) ? 10 : 0;
			}
			if (ball.x > visitor.x + visitor.width / 4 + visitor.width / 2) {
				visitor.x += (visitor.x + visitor.width <= 1200 && (random >= failureRate)) ? 10 : 0;
			}

			if (!isWithinX(ball.x, 1200)) velocityX *= -1;
			if (CheckCollisionRecs(ball, home) || CheckCollisionRecs(ball, visitor)) {
				if (CheckCollisionRecs(ball, home)) velocityY += 1;
				else velocityY -= 1;
				velocityY *= -1;
				velocityX = (rand() % 21) - 5;
			}

			if (ball.y < 0) { // home wins
				ball.x = 590;
				ball.y = 490;
				home.x = 525;
				home.y = 900;
				visitor.x = 525;
				visitor.y = 100;
				velocityX = 0;
				velocityY = -5;

				homeScore++;
				countdown = 180;
			}
			else if (ball.y + ball.height > 1000) {
				ball.x = 590;
				ball.y = 490;
				home.x = 525;
				home.y = 900;
				visitor.x = 525;
				visitor.y = 100;
				velocityX = 0;
				velocityY = 5;

				visitorScore++;
				countdown = 180;
			}

			ball.x += velocityX;
			ball.y += velocityY;
		}
		else {
			countdown--;
		}

		BeginDrawing();
		ClearBackground(BLACK);

		DrawRectangleRec(home, WHITE); // draw home paddle
		DrawRectangleRec(visitor, WHITE); // draw visitor paddle
		DrawText(std::to_string(homeScore).c_str(), 600, 950, 50, WHITE);
		DrawText(std::to_string(visitorScore).c_str(), 600, 50, 50, WHITE);

		if (countdown >= 0) DrawText(std::to_string((countdown - 1) / 60 + 1).c_str(), 540, 460, 120, WHITE);
		else DrawRectangleRec(ball, WHITE); // draw projectile

		EndDrawing();
	}
}