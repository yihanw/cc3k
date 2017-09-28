#include "game.h"
#include <iostream>

using namespace std;



void Game::CharacterSelect(shared_ptr<Level> & level) {

	cout << "Select your race:" << endl;

	int len = descriptions.size();

	for (int i = 0; i < len; i++) {
		cout << "\t" << descriptions[i] << endl;
		i++;
		cout << "\t\t" << descriptions[i] << endl;
	}


		//, d = Drow, v = vampire, t = troll, g = goblin" << endl;
	while (true) {
		string race;
		cin >> race;
	//	race = "s";
		Position defaultPos{ 0,0 };
		if (race == "s" || race == "S") {
			auto player = make_shared<Shade>(defaultPos);
			level->setPlayer(player);
			cout << "You have selected: Shade!" << endl;
			break;
		}
		else if (race == "d" || race == "D") {
			auto player = make_shared<Drow>(defaultPos);
			level->setPlayer(player);
			cout << "You have selected: Drow!" << endl;
			break;
		}
		else if (race == "v" || race == "V") {
			auto player = make_shared<Vampire>(defaultPos);
			level->setPlayer(player);
			cout << "You have selected: Vampire!" << endl;
			this->displayMaxHP = false;
			break;
		}
		else if (race == "t" || race == "T") {
			auto player = make_shared<Troll>(defaultPos);
			level->setPlayer(player);
			cout << "You have selected: Troll!" << endl;
			break;
		}
		else if (race == "g" || race == "G") {
			auto player = make_shared<Goblin>(defaultPos);
			level->setPlayer(player);
			cout << "You have selected: Goblin!" << endl;
			break;
		}
		else {
			cout << "Not a valid race. Please choose again." << endl;
		}
	}
}

void Game::DisplayPlayerStatus(shared_ptr<Level> & level) {
	cout <<  "Floor: " << level->getCurFloor() << endl;
	cout << "Race: " << level->getPlayer()->getName().name << endl;
	cout << "Gold: " << level->getPlayer()->getGold() << endl;


	cout  << "HP : " << level->getPlayer()->getStats().HP;
	if (this->displayMaxHP) {
		cout << "/" << level->getPlayer()->getStats().MaxHP;
	}

	cout << endl;

	cout << "Atk: " << level->getPlayer()->getStats().Atk;
	cout << " | " << "Def: " << level->getPlayer()->getStats().Def;

	cout << endl;
}

void Game::PlayerCommands(shared_ptr<Level> & level) {

	string input;

	cout << "Please specify your command:" << endl;
	cout << "\t Direction = one of: nw, n, ne, w, e, sw, s, se" << endl;
	cout << "\t\t<Direction> - Moves the player in <Direction>" << endl;
	cout << "\t\ta <Direction> - Attacks enemy in <Direction>" << endl;
	cout << "\t\tu <Direction> - Use potion in <Direction>" << endl;
	cout << "\t\tf - Stop all enemies from moving" << endl;
	cout << "\t\tr - Reset game" << endl;
	cout << "\t\tq - Quit game" << endl;

	while (true) {
			cout << level;
			DisplayPlayerStatus(level);
		cin >> input;

		if (input == "nw" || input == "n" || input == "ne" || input == "w" || input == "e" || input == "sw" || input == "s" || input == "se") {
			bool success = level->movePlayer(input);
			if (!success) {
				cout << "Can't go there!" << endl;
				continue;
			}
		}
		else if (input == "a") {
			string direction;
			cin >> direction;
			if (direction == "nw" || direction == "n" || direction == "ne" || direction == "w" || direction == "e" || direction == "sw" || direction == "s" || direction == "se") {
				bool success = level->PlayerAttack(direction);
				if (!success) {
					//No target
					cout << "There's no enemy there!" << endl;
					continue;
				}
			}
			//Second input not a direction
			else {
				cout << "Not a valid direction!" << endl;
				continue;
			}

		}
		else if (input == "u") {
			string direction;
			cin >> direction;
			if (direction == "nw" || direction == "n" || direction == "ne" || direction == "w" || direction == "e" || direction == "sw" || direction == "s" || direction == "se") {
				bool success = level->usePotion(direction);
				if (!success) {
					//No target
					cout << "There's no item there!" << endl;
					continue;
				}
			}
			//Second input not a direction
			else {
				cout << "Not a valid direction" << endl;
				continue;
			}

		}
		else if (input == "f") {
			level->setStopMovingEnemies(!level->getStopMovingEnemies());
			if (level->getStopMovingEnemies()) {
				cout << "Enemies have stopped moving, commander!" << endl;
			}
			else {
				cout << "The game is fair and balanced yet again!" << endl;
			}
			continue;
		}
		else if (input == "r") {
			gameState = GameState::Reset;
			cout << "Reseting game..." << endl;

			break;
		}
		else if (input == "q") {
			gameState = GameState::Quit;
			cout << "Leaving already? :(" << endl;

			break;
		}

		else {
			cout << "I don't understand your input." << endl;
			continue;
		}

		if (level->getWon()) {
			if (level->getCurFloor() >= 6) {
				gameState = GameState::Winner;
				cout << "You have conquered the dungeon and saved the city!" << endl;
				cout << "The gold obtained from your adventure is: " << level->getPlayer()->getGold() << endl;

				cout << "Type r to reset" << endl;
				cout << "Type q to quit" << endl;

				while (true) {
					string input2;
					cin >> input2;

					if (input2 == "r") {
						gameState = GameState::Reset;
						break;
					}
					else if (input2 == "q") {
						gameState = GameState::Quit;
						break;
					}
					else {
						cout << "Not valid command" << endl;
					}
				}

				break;
			}
			else {
				cout << "Advancing to floor: " << level->getCurFloor() << endl;
				level->setWon(false);
				continue;
			}
		}

		//Enemy Turn

		level->enemyTurn();
		//cout << level;

		if (level->getPlayer()->getStats().HP == 0) {
			gameState = GameState::GameOver;
			int score = level->getPlayer()->getGold();
			cout << "You have died! Game over!" << endl;
			cout << "You have obtained: " << score << " gold!" << endl;
			cout << "Not that it matters anyway, you're dead!" << endl;
			cout << "Type r to reset" << endl;
			cout << "Type q to quit" << endl;

			while (true) {
				cin >> input;
				if (input == "r") {
					gameState = GameState::Reset;
					break;
				}
				else if (input == "q") {
					gameState = GameState::Quit;
					break;
				}

			}

			break;

		}
		//Enemy turn end

	}

}



void Game::PlayTheGame(string filename)  {



	while (true) {
		gameState = GameState::Play;

		auto level = make_shared<Level>();

		CharacterSelect(level);

		level->CreateLevels(filename);


		PlayerCommands(level);

		if (gameState == GameState::Reset) {
			level->setWon(true);
			continue;
		}
		else if (gameState == GameState::Quit) {
			level->setWon(true);
			break;
		}

	}
	cout << "Goodbye, friend" << endl;

}

