#include <raylib.h>
#include <string>
#include "helper.h"
#include "singleplayer.h"
#include "multiplayer.h"

void updateMultiplayerScreen(GameState &CurrentGameState) {
	if (IsKeyPressed(KEY_ESCAPE)) {
		CurrentGameState = GameState::MENU;
		return;
	}

	if (countdown < 0) {
		if (IsKeyDown(KEY_A)) home.x -= home.x >= 0 ? 10 : 0; // A - move left, D - move right
		if (IsKeyDown(KEY_D)) home.x += home.x + home.width <= 1200 ? 10 : 0;
		if (IsKeyDown(KEY_LEFT)) visitor.x -= visitor.x >= 0 ? 10 : 0;
		if (IsKeyDown(KEY_RIGHT)) visitor.x += visitor.x + visitor.width <= 1200 ? 10 : 0;

		if (!isWithinX(ball.x, 1200)) {
			velocityX *= -1;
			PlaySound(hitsoundWeak);
		}
		if (CheckCollisionRecs(ball, home) || CheckCollisionRecs(ball, visitor)) {
			velocityY *= -1;
			velocityX = (rand() % 21) - 10;

			if (abs(velocityX) >= 15) PlaySound(hitsoundStrong);
			else PlaySound(hitsoundWeak);
		}

		if (ball.y < 0) { // home wins
			ball.x = 590;
			ball.y = 490;
			home.x = 525;
			home.y = 900;
			visitor.x = 525;
			visitor.y = 100;
			velocityX = 0;
			velocityY = -8;

			homeScore++;
			countdown = 180;
			PlaySound(explosion);
		}
		else if (ball.y + ball.height > 1000) {
			ball.x = 590;
			ball.y = 490;
			home.x = 525;
			home.y = 900;
			visitor.x = 525;
			visitor.y = 100;
			velocityX = 0;
			velocityY = 8;

			visitorScore++;
			countdown = 180;
			PlaySound(explosion);
		}

		ball.x += velocityX;
		ball.y += velocityY;
	}
	else {
		countdown--;
	}
}

void drawMultiplayerScreen() {
	DrawRectangleRec(home, WHITE); // draw home paddle
	DrawRectangleRec(visitor, WHITE); // draw visitor paddle
	DrawText(std::to_string(homeScore).c_str(), 600, 950, 50, WHITE);
	DrawText(std::to_string(visitorScore).c_str(), 600, 50, 50, WHITE);

	if (countdown >= 0) DrawText(std::to_string((countdown - 1) / 60 + 1).c_str(), 540, 460, 120, WHITE);
	else DrawRectangleRec(ball, WHITE); // draw projectile
}