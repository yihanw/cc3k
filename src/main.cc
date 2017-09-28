#include "game.h"
using namespace std;

#include "myrand.h"

int main(int argc, char *argv[]) {

	string filename = "defaultmap.txt";

	if (argc == 2) {
		filename = argv[1];
	}

	cout << "Welcome to C33k, the best game in the universe!" << endl;
	cout << "\tPacked with stunning graphics, navigate your way through the depths of the evil dungeon and default all enemies in the way" << endl;

	Game game;
	game.PlayTheGame(filename); // The game is being played!
}

