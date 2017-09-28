#include <iostream>
#include <string>
#include <fstream>

#include "level.h"
#include <vector>
#include "display.h"
#include "position.h"
#include "name.h"
#include "stats.h"
#include "character.h"
#include "shade.h"
#include <memory>

#include "drow.h"
#include "vampire.h"
#include "troll.h"
#include "goblin.h"

class Game {
	std::vector<std::string> descriptions{
		"s = Shade: 125 HP, 25 Atk, 25 Def",
		"Nothing Special",
		"d = Drow: 150 HP, 25 Atk, 15 Def",
		"All potions x1.5",
		"v = Vampire: 50 HP, 25 Atk, 25 Def",
		"Gains 5 HP every Attack; No maximum health",
		"t = Troll: 120 HP, 25 Atk, 15 Def",
		"Regenerates 5 HP every turn",
		"g = Goblin: 110 HP, 15 Atk, 20 Def",
		"Steals 5 gold from every slain enemy"
	};

	enum class GameState {
		Play, Reset, GameOver, Quit, Winner
	};

	GameState gameState;
	void CharacterSelect(std::shared_ptr<Level> & level); // asks player to select the character
	void DisplayPlayerStatus(std::shared_ptr<Level> & level); // display the stats of the selected character
	void PlayerCommands(std::shared_ptr<Level> & level); // asks player to enter the command

	bool displayMaxHP = true;

public:
    void PlayTheGame(std::string filename);
};
