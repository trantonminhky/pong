#include <raylib.h>
#include <string>
#include <queue>
#include "../helper.h"
#include "../skills.h"
#include "./stages.h"

// PROJECTILE DEFINITIONS -------------------------------------
Projectile proj_1_1 = {
	1,
	{ 590, 290, 20, 20 },
	{ 0, 5 },
	4, 10
};

Projectile proj_2_1 = {
	1,
	{ 100, 290, 20, 20 },
	{ 3, 5 },
	8, 10
};
Projectile proj_2_2 = {
	1,
	{ 150, 290, 20, 20 },
	{ 2, 5 },
	9, 10
};
Projectile proj_2_3 = {
	1,
	{ 200, 290, 20, 20 },
	{ 1, 5 },
	10, 10
};

Projectile proj_2_4 = {
	1,
	{ 1100, 290, 20, 20 },
	{ -3, 5 },
	12, 10
};
Projectile proj_2_5 = {
	1,
	{ 1050, 290, 20, 20 },
	{ -2, 5 },
	13, 10
};
Projectile proj_2_6 = {
	1,
	{ 1000, 290, 20, 20 },
	{ -1, 5 },
	14, 10
};

Projectile proj_3_1 = {
	1,
	{ 200, 190, 20, 20 },
	{ (rand() % 11) - 5, 5 },
	16, 10
};
Projectile proj_3_2 = {
	1,
	{ 300, 190, 20, 20 },
	{ (rand() % 11) - 5, 5 },
	16.5, 10
};
Projectile proj_3_3 = {
	1,
	{ 400, 190, 20, 20 },
	{ (rand() % 11) - 5, 5 },
	17, 10
};
Projectile proj_3_4 = {
	1,
	{ 500, 190, 20, 20 },
	{ (rand() % 11) - 5, 5 },
	17.5, 10
};
Projectile proj_3_5 = {
	1,
	{ 600, 190, 20, 20 },
	{ (rand() % 11) - 5, 5 },
	18, 10
};
Projectile proj_3_6 = {
	1,
	{ 700, 190, 20, 20 },
	{ (rand() % 11) - 5, 5 },
	18.5, 10
};
Projectile proj_3_7 = {
	1,
	{ 800, 190, 20, 20 },
	{ (rand() % 11) - 5, 5 },
	19, 10
};
Projectile proj_3_8 = {
	1,
	{ 900, 190, 20, 20 },
	{ (rand() % 11) - 5, 5 },
	19.5, 10
};

Projectile proj_4_1 = {
	1,
	{ 400, 190, 20, 20 },
	{ (rand() % 7) - 3, 8 },
	22, 10
};
Projectile proj_4_2 = {
	1,
	{ 600, 190, 20, 20 },
	{ (rand() % 7) - 3, 8 },
	23, 10
};
Projectile proj_4_3 = {
	1,
	{ 800, 190, 20, 20 },
	{ (rand() % 7) - 3, 8 },
	24, 10
};

std::vector<Projectile> projectiles = { proj_1_1,
							proj_2_1, proj_2_2, proj_2_3,
							proj_2_4, proj_2_5, proj_2_6,
							proj_3_1, proj_3_2, proj_3_3, proj_3_4, proj_3_5, proj_3_6, proj_3_7, proj_3_8,
							proj_4_1, proj_4_2, proj_4_3
};
// --------------------------------

void LoremInstance::updateSingleplayerScreenOpening(float &elapsed) {
	if (elapsed >= 3) {
		transitionFromOpeningToSummon();
		return;
	}

	elapsed += GetFrameTime();
	listenInput();
	// TODO: display some text for stage opening
}

void LoremInstance::updateSingleplayerScreenSummon(float& elapsed) {
	UpdateMusicStream(stage1Music);
	if (elapsed >= 29) {
		transitionFromSummonToBoss();
		return;
	}

	elapsed += GetFrameTime();
	listenInput();

	for (auto& proj : projectiles) {
		// plays a hitsound when ball hits paddle or wall, then redirect ball to the opposite side
		playSoundAndRedirectProjectile(proj);
		if (proj.isAlive(stageElapsedTime)) {
			moveProjectiles(proj);
		}
	}
}

void LoremInstance::updateSingleplayerScreenBoss(int failureRate, float& elapsed) {
	UpdateMusicStream(stage1Music);
	elapsed += GetFrameTime();
	// reads the current skills in usage and executes the relevant function
	enactCurrentSkill();

	// listens to keyboard input
	// A - move left
	// D - move right
	// S - use sub
	// W - use ult
	listenInput();

	// if ball is on visitor left, move left and vice versa, with a failureRate chance that the paddle fails to move
	controlVisitorPaddle(failureRate);

	// plays a hitsound when ball hits paddle or wall, then redirect ball to the opposite side
	playSoundAndRedirectBall();

	// gives point to winner and resets the stage to original position
	determineWinnerAndResetState();

	moveBall();
}

void LoremInstance::updateSingleplayerScreen(int failureRate, float &elapsed) {
	switch (CurrentStageState) {
	case StageState::STAGE_OPENING:
		updateSingleplayerScreenOpening(stageElapsedTime);
		break;

	case StageState::STAGE_SUMMON:
		updateSingleplayerScreenSummon(stageElapsedTime);
		break;

	case StageState::STAGE_BOSS:
		updateSingleplayerScreenBoss(failureRate, stageElapsedTime);
		break;
	}
}

void LoremInstance::drawSingleplayerScreenOpening() {
	// paddles
	DrawRectangleRec(home, WHITE);

	// mana
	drawManaBoard();

	drawCurrentSkill();
}

void LoremInstance::drawSingleplayerScreenSummon() {
	// paddles
	DrawRectangleRec(home, WHITE);

	// mana
	drawManaBoard();

	for (const auto &proj : projectiles) {
		if (proj.isAlive(stageElapsedTime)) {
			DrawRectangleRec(proj.projectile, WHITE);
		}
	}

	drawCurrentSkill();
}

void LoremInstance::drawSingleplayerScreenBoss() {
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

	DrawRectangleRec(ball, WHITE); // draw projectile

	drawCurrentSkill();
}

void LoremInstance::drawSingleplayerScreen() {
	switch (CurrentStageState) {
	case StageState::STAGE_OPENING:
		drawSingleplayerScreenOpening();
		break;

	case StageState::STAGE_SUMMON:
		drawSingleplayerScreenSummon();
		break;

	case StageState::STAGE_BOSS:
		drawSingleplayerScreenBoss();
		break;
	}
}

void LoremInstance::spawnBall(int x, int y) {

}

void LoremInstance::listenInput() {
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
}

void LoremInstance::controlVisitorPaddle(int failureRate) {
	int random = rand() % 100 + 1;
	if (ball.x < visitor.x + visitor.width / 4) {
		visitor.x -= (visitor.x >= 0 && (random >= failureRate)) ? visitorSpeed : 0;
	}
	if (ball.x > visitor.x + visitor.width / 4 + visitor.width / 2) {
		visitor.x += (visitor.x + visitor.width <= 1200 && (random >= failureRate)) ? visitorSpeed : 0;
	}
}

void LoremInstance::playSoundAndRedirectProjectile(Projectile &projectile) {
	if (!isWithinX(projectile.projectile.x, 1200)) {
		projectile.velocity.x *= -1;
		PlaySound(hitsoundWeak);
	}
	if (CheckCollisionRecs(projectile.projectile, home)) {
		redirectProjectiles(projectile);
		increaseMana(homeMana);

		if (isProjectileStuck(home, projectile)) snapProjectileOutOfHome(projectile);
	}
}

void LoremInstance::playSoundAndRedirectBall() {
	if (!isWithinX(ball.x, 1200)) {
		velocityX *= -1;
		PlaySound(hitsoundWeak);
	}
	if (CheckCollisionRecs(ball, home)) {
		redirectBall();
		increaseMana(homeMana);

		if (isBallStuck(home)) snapBallOutOfHome();
	}
	else if (CheckCollisionRecs(ball, visitor)) {
		redirectBall();

		if (isBallStuck(visitor)) snapBallOutOfVisitor();
	}
}

void LoremInstance::transitionFromOpeningToSummon() {
	CurrentStageState = StageState::STAGE_SUMMON;
}

void LoremInstance::transitionFromSummonToBoss() {
	visitor.x = 525;
	CurrentStageState = StageState::STAGE_BOSS;
}

void LoremInstance::determineWinnerAndResetState() {
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
		winnerState = 2;
		PlaySound(explosion);
	}
}

void LoremInstance::moveProjectiles(Projectile &projectile) {
	projectile.projectile.x += projectile.velocity.x;
	projectile.projectile.y += projectile.velocity.y;
}

void LoremInstance::moveBall() {
	ball.x += velocityX;
	ball.y += velocityY;
}

void LoremInstance::drawManaBoard() {
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

void LoremInstance::redirectBall() {
	velocityY *= -1;
	velocityX = (rand() % 21) - 10;

	if (abs(velocityX) >= 15) PlaySound(hitsoundStrong);
	else PlaySound(hitsoundWeak);
}

void LoremInstance::redirectProjectiles(Projectile &projectile) {
	projectile.velocity.y *= -1;
	projectile.velocity.x = (rand() % 21) - 10;

	if (abs(projectile.velocity.x) >= 15) PlaySound(hitsoundStrong);
	else PlaySound(hitsoundWeak);
}

void LoremInstance::snapBallOutOfHome() {
	ball.y = 872;
}

void LoremInstance::snapProjectileOutOfHome(Projectile &projectile) {
	projectile.projectile.y = 872;
}

void LoremInstance::snapBallOutOfVisitor() {
	ball.y = 128;
}

bool LoremInstance::isBallStuck(Rectangle paddle) {
	return ((paddle.y < ball.y + 5 && ball.y + 15 < paddle.y + paddle.height) && (paddle.x < ball.x + 10 && ball.x + 10 < paddle.x + paddle.width));
}

bool LoremInstance::isProjectileStuck(Rectangle paddle, Projectile projectile) {
	return ((paddle.y < projectile.projectile.y + 5 && projectile.projectile.y + 15 < paddle.y + paddle.height) && (paddle.x < projectile.projectile.x + 10 && projectile.projectile.x + 10 < paddle.x + paddle.width));
}

void LoremInstance::enactCurrentSkill() {
	switch (CurrentSkillInUse) {
	case Skills::HOME_SUB:
		Sub::home(homeSkillDurationLeft);
		break;

	case Skills::HOME_ULT:
		Ult::home(homeSkillDurationLeft);
		break;
	}
}

void LoremInstance::drawCurrentSkill() {
	switch (CurrentSkillInUse) {
	case Skills::HOME_ULT:
		DrawRectangle(0, 0, 1200, 1000, ColorAlpha(WHITE, 0.2));
		break;
	}
}