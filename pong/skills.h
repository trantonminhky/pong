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

class Ult {

};