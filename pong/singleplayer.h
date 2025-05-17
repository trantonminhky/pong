#pragma once

void updateSingleplayerScreen(int failureRate);
void drawSingleplayerScreen();
void drawManaBoard();
void snapBallOutOfHome();
void snapBallOutOfVisitor();
bool isStuck(Rectangle paddle);
void redirectBall();
void enactCurrentSkill();