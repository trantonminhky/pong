#include <raylib.h>
#include <string>
#include "helper.h"
#include "skills.h"
#include "singleplayer.h"

void updateSingleplayerScreen(int failureRate) {
	int random = rand() % 100 + 1;
	if (IsKeyPressed(KEY_ESCAPE)) {
		CurrentGameState = GameState::MENU;
		return;
	}

	if (countdown < 0) {
		enactCurrentSkill();

		if (IsKeyDown(KEY_A)) home.x -= home.x >= 0 ? homeSpeed : 0; // A - move left, D - move right
		if (IsKeyDown(KEY_D)) home.x += home.x + home.width <= 1200 ? homeSpeed : 0;
		if (IsKeyPressed(KEY_S)) { // use sub
			if (homeSkillDurationLeft <= 0 && depleteMana(homeMana, 50)) {
				homeSkillDurationLeft = HOME_SUB_DURATION;
				CurrentSkillInUse = Skills::HOME_SUB;
				PlaySound(subsound);
			}
			else {
				PlaySound(failsound);
			}
		}
		if (IsKeyPressed(KEY_W)) { // use ult
			if (homeSkillDurationLeft <= 0 && depleteMana(homeMana, 100)) {
				homeSkillDurationLeft = HOME_ULT_DURATION;
				CurrentSkillInUse = Skills::HOME_ULT;
				PlaySound(ultsound);
			}
			else {
				PlaySound(failsound);
			}
		}

		if (ball.x < visitor.x + visitor.width / 4) {
			visitor.x -= (visitor.x >= 0 && (random >= failureRate)) ? visitorSpeed : 0;
		}
		if (ball.x > visitor.x + visitor.width / 4 + visitor.width / 2) {
			visitor.x += (visitor.x + visitor.width <= 1200 && (random >= failureRate)) ? visitorSpeed : 0;
		}

		if (!isWithinX(ball.x, 1200)) {
			velocityX *= -1;
			PlaySound(hitsoundWeak);
		}
		if (CheckCollisionRecs(ball, home)) {
			redirectBall();
			increaseMana(homeMana);

			if (isStuck(home)) snapBallOutOfHome();
		}
		else if (CheckCollisionRecs(ball, visitor)) {
			redirectBall();

			if (isStuck(visitor)) snapBallOutOfVisitor();
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
			winnerState = 1;
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
			winnerState = 2;
			PlaySound(explosion);
		}

		ball.x += velocityX;
		ball.y += velocityY;
	}
	else {
		countdown--;
	}
}

void drawSingleplayerScreen() {
	// paddles
	DrawRectangleRec(home, WHITE);
	DrawRectangleRec(visitor, WHITE);

	// mana
	drawManaBoard();

	// scores
	DrawText(std::to_string(homeScore).c_str(), 600, 950, 50, WHITE);
	DrawText(std::to_string(visitorScore).c_str(), 600, 50, 50, WHITE);

	// debugging
	// DrawText(std::to_string(abs(sin(4 * GetTime()))).c_str(), 100, 500, 50, WHITE);

	// countdown and announcements
	if (countdown >= 0) {
		DrawText(std::to_string((countdown - 1) / 60 + 1).c_str(), 540, 460, 120, WHITE);
		drawWinnerOrInstruction(winnerState);
	}
	else DrawRectangleRec(ball, WHITE); // draw projectile
}

void drawManaBoard() {
	float alpha;
	if (homeMana < 50) {
		alpha = 1;
	}
	else if (homeMana >= 50 && homeMana != 100) {
		alpha = abs(sin(4 * GetTime()));
	}
	else {
		alpha = abs(sin(8 * GetTime()));
	}
	DrawRectangleLinesEx({ 900, 950, 200, 30 }, 3, WHITE);
	DrawRectangle(900, 950, homeMana * 2, 30, ColorAlpha(WHITE, alpha));
}

void redirectBall() {
	velocityY *= -1;
	velocityX = (rand() % 21) - 10;

	if (abs(velocityX) >= 15) PlaySound(hitsoundStrong);
	else PlaySound(hitsoundWeak);
}

void snapBallOutOfHome() {
	ball.y = 872;
}

void snapBallOutOfVisitor() {
	ball.y = 128;
}

bool isStuck(Rectangle paddle) {
	return ((paddle.y < ball.y + 5 && ball.y + 15 < paddle.y + paddle.height) && (paddle.x < ball.x + 10 && ball.x + 10 < paddle.x + paddle.width));
}

void enactCurrentSkill() {
	switch (CurrentSkillInUse) {
	case Skills::HOME_SUB:
		Sub::home(homeSkillDurationLeft);
		break;

	case Skills::HOME_ULT:
		Ult::home(homeSkillDurationLeft);
		break;
	}
}