#pragma once

enum class Skills {
	NONE,
	HOME_SUB,
	HOME_ULT
};

extern int HOME_SUB_DURATION;

class Sub {
public:
	static void home(int &remainingDuration);

private:
	static void homeStart();
	static void homeEnd();
};

// ---------------------
extern int HOME_ULT_DURATION;

struct lastSavedState {
	int savedVelocityX;
	int savedVelocityY;
	int savedHomeSpeed;
	int savedVisitorSpeed;
	int savedHomeMana;
	int savedVisitorMana;
};

class Ult {
public:
	static void home(int &remainingDuration);

private:

	static void homeStart();
	static void homeEnd();
	static void saveCurrentRoundState(lastSavedState& state);
	static void loadCurrentRoundState(lastSavedState state);
};