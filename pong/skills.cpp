#include <raylib.h>
#include "skills.h"
#include "helper.h"

int HOME_SUB_DURATION = 72; // 0.5s

void Sub::homeStart() {
	homeSpeed += 5;
}

void Sub::homeEnd() {
	homeSpeed -= 5;
}

void Sub::home(int &remainingDuration) {
	if (remainingDuration == HOME_SUB_DURATION) {
		Sub::homeStart();
	}
	if (remainingDuration > 0) {
		remainingDuration--;
	}
	else {
		Sub::homeEnd();
		CurrentSkillInUse = Skills::NONE;
	}
}