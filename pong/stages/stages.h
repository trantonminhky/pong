#pragma once
#include "../helper.h"

struct Projectile {
	int typeId; // projectile types
	Rectangle projectile; // projectile sprites and initial position
	Vector2 velocity; // velocity
	float timer; // the time that projectile appears
	float lifetime; // how long the projectile is drawn/updated

	bool isAlive(const float &elapsed) const {
		return (elapsed > timer && elapsed < lifetime + timer && (projectile.y < 1000 && projectile.y > -20));
	}
};


// STAGE 1 --------------

class LoremInstance : public Instance {
public:
	virtual void updateSingleplayerScreen(int failureRate, float& elapsed);
	virtual void drawSingleplayerScreen();

private:
	void updateSingleplayerScreenOpening(float& elapsed);
	void updateSingleplayerScreenSummon(float& elapsed);
	void updateSingleplayerScreenBoss(int failureRate, float& elapsed);

	void drawSingleplayerScreenOpening();
	void drawSingleplayerScreenSummon();
	void drawSingleplayerScreenBoss();


	void spawnBall(int x, int y);
	void listenInput();
	void controlVisitorPaddle(int failureRate);
	void playSoundAndRedirectProjectile(Projectile &projectile);
	void playSoundAndRedirectBall();
	void transitionFromOpeningToSummon();
	void transitionFromSummonToBoss();
	void determineWinnerAndResetState();
	void moveBall();
	void moveProjectiles(Projectile& projectile);
	void drawManaBoard();
	void redirectBall();
	void redirectProjectiles(Projectile &projectile);
	void snapProjectileOutOfHome(Projectile &projectile);
	void snapBallOutOfHome();
	void snapBallOutOfVisitor();
	bool isBallStuck(Rectangle paddle);
	bool isProjectileStuck(Rectangle paddle, Projectile projectile);
	void enactCurrentSkill();
	void drawCurrentSkill();
};

extern Projectile proj_1_1;

extern Projectile proj_2_1;
extern Projectile proj_2_2;
extern Projectile proj_2_3;

extern Projectile proj_2_4;
extern Projectile proj_2_5;
extern Projectile proj_2_6;

extern Projectile proj_3_1;
extern Projectile proj_3_2;
extern Projectile proj_3_3;
extern Projectile proj_3_4;
extern Projectile proj_3_5;
extern Projectile proj_3_6;
extern Projectile proj_3_7;
extern Projectile proj_3_8;

extern Projectile proj_4_1;
extern Projectile proj_4_2;
extern Projectile proj_4_3;
// -------------------------------------