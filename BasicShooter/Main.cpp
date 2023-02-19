#include "Game.h"

int main(int argc, char** argv) {
	Game game;
	bool success = game.Init();
	if (success) {
		game.Loop();
	}
	game.Quit();
	return 0;
}