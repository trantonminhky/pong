#pragma once
#include "helper.h"

class SingleplayerInstance : public Instance {
public:
	virtual void updateSingleplayerScreen(int failureRate, float &elapsed);
	virtual void drawSingleplayerScreen();

private:
	void listenInput();
	void controlVisitorPaddle(int failureRate);
	void playSoundAndRedirect();
	void determineWinnerAndResetState();
	void moveBall();
	void drawManaBoard();
	void redirectBall();
	void snapBallOutOfHome();
	void snapBallOutOfVisitor();
	bool isStuck(Rectangle paddle);
	void enactCurrentSkill();
	void drawCurrentSkill();
};