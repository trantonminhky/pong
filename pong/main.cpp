#include <raylib.h>
#include <string>
#include <time.h>
#include "singleplayer.h"
#include "multiplayer.h"
#include "menu.h"

Image icon = LoadImage("./pixil-frame-0.png");

int main() {
	srand(time(NULL));

	InitWindow(1200, 1000, "pong");
	SetTargetFPS(60);
	SetWindowIcon(icon);

	while (!WindowShouldClose()) {
		int option = launchMenu();
		switch (option) {
		case 1: // singleplayer easy
			launchSingleplayer(50);
			break;

		case 2: // singleplayer normal
			launchSingleplayer(30);
			break;

		case 3: // singleplayer hard
			launchSingleplayer(10);
			break;

		case 4: // multiplayer
			launchMultiplayer();
			break;

		default:
			CloseWindow();
			return 1;
		}
	}
	CloseWindow();
	return 0;
}