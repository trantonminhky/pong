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

// -----------------------------

int HOME_ULT_DURATION = 144; // 1s

void Ult::homeStart() {
	homeSpeed -= 5;
	Ult::saveCurrentRoundState(LastSavedState);

	velocityX = 0;
	velocityY = 0;
	visitorSpeed = 0;
}

void Ult::saveCurrentRoundState(lastSavedState& state) {
	state.savedVelocityX = velocityX;
	state.savedVelocityY = velocityY;
	state.savedVisitorSpeed = visitorSpeed;
	state.savedHomeMana = homeMana;
	// state.savedVisitorMana = visitorMana;
}

void Ult::loadCurrentRoundState(lastSavedState state) {
	velocityX = state.savedVelocityX;
	velocityY = state.savedVelocityY;
	visitorSpeed = state.savedVisitorSpeed;
	homeMana = state.savedHomeMana;
	// state.savedVisitorMana = visitorMana;
}

void Ult::homeEnd() {
	homeSpeed += 5;
	Ult::loadCurrentRoundState(LastSavedState);
}

void Ult::home(int& remainingDuration) {
	if (remainingDuration == HOME_ULT_DURATION) {
		Ult::homeStart();
	}
	if (remainingDuration > 0) {
		remainingDuration--;
	}
	else {
		Ult::homeEnd();
		CurrentSkillInUse = Skills::NONE;
	}
}