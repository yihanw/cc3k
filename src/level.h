#ifndef _LEVEL_
#define _LEVEL_

#include <vector>
#include <memory>

class Player;
class Display;
class Enemy;


class Potion;
class Treasure;
class Chamber;
struct Position;
class Item;

#include <iostream>



//Level.h
class Level {
private:

	//Constants:
	const int amountOfLevels = 5;
	const int assumedMapRows = 25;
	const int assumedMapCols = 79;

	int numberOfPotions = 10; // 10
	int numberOfGold = 10;  // 10
	int numberOfEnemies = 20; // 20

	const int numberOfTypesOfEnemies = 6;

	//Flags:

	bool hasWon;
	int curFloor;
	bool stopMovingEnemies;
	bool merchantsHostile = false;

	//Lists
	std::shared_ptr<Player> player;
	std::shared_ptr<Display> theDisplay;
	std::vector < std::shared_ptr<Enemy>> enemies;
	std::vector < std::shared_ptr<Potion>> potions;
	std::vector < std::shared_ptr<Treasure >> gold;
	std::vector < std::shared_ptr<Chamber >> chambers;

	void pickUpGold(); //Checks whether to pick up gold


	//Maps
	void mapPlayer(int mapindex, int & playerChamber); // map player
	void mapGold(int mapindex); // map gold
	void mapPotions( int mapindex); // map potions
	void mapStairs( int mapindex, int & playerChamber); // map stairs
	void mapEnemies( int mapindex); // map enemies
	void createChambers(); // create a empty chamber

	void spawnPlayer(Position pos); // randomly generete the player in a chamber
	void spawnGold(Position pos, char thisType, int mapIndex); // randomly generete the golds in a chamber
	void spawnPotions(Position pos, char thisType); // randomly generete the potions in a chamber
	void spawnStairs(Position pos); // randomly generete the stairs in a chamber
	void spawnEnemies(Position pos, char thisType); // randomly generete the enemies in a chamber

	std::vector<std::vector<char>> ogMap;
	std::vector <std::vector<std::vector<char>>> maps;

	//Helpers
	void EnemyAttack(int i);
	void EnemyMove(int i);

	Position translatePos(std::string direction, Position pos); // updates the pos based on given direction
	void sortEnemyArrayByPosition(); // sorts the enemy based on its position

	void randomlyGenerateMap();
	void readInMap(std::string filename);
	void createDefaultMap(std::vector<std::vector<char>> & arr);
	void initializeEmptyMaps();



public:
	Level();
	~Level();

	void LoadMap(int level); // generate the completed map with player, enemies, potions, and golds

	void CreateLevels(std::string filename); // get the default floor
	void reset(); // reset the map
	void nextFloor(); // goes to next floor
	void notifyMerchants(); // set merchants to hostile
	void playerTurn();  //Signify its players turn
	void enemyTurn(); //Signify that its the enemy's turn. Activates its AI
	bool isTileAvailable(Position pos, std::vector<char>); // Check if a tile is valid to moveCollision detection
    char getCharAt(Position pos); // get the character at position, pos

	std::shared_ptr<Player> getPlayer();
	void setPlayer(std::shared_ptr<Player> player); // set the player to selected character
	bool PlayerAttack(std::string direction); // player attacks at a given direction
	bool movePlayer(std::string direction); // moves player at a givin direction
	bool usePotion(std::string direction); // player uses the potion that is at its direction

	Position getPlayerPos(); // get the player's position
	std::shared_ptr<Display> getDisplay(); // get the display

	void DropItemAt(std::shared_ptr<Item>  item, Position pos, bool isRand); //Drops an item onto the map

	void generateItemByChar(int row, int col, char symbol); // generate item at given row and col based on the symbol

	Position getRandomPositionAround(Position pos, std::vector<char> tilableCharacters); //helper
	Position getRandomPositionAroundMap(Position pos, std::vector<char> tilableCharacters, int mapIndex); //helper

	//getters/setters
	std::vector <std::vector<std::vector<char>>> getMaps();
	void setMaps(int mapIndex, int x, int y, char value);

	bool getWon();
	void setWon(bool won);

	int getCurFloor(); //
	bool areMerchantsHostile(); // check if merchant is hostile

	bool getStopMovingEnemies();
	void setStopMovingEnemies(bool set);

};

std::ostream & operator<< (std::ostream & ss, const std::shared_ptr<Level>  level);

#endif
