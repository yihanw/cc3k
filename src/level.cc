#include "level.h"
#include "player.h"
#include "enemy.h"
#include "chamber.h"
#include "display.h"
#include "potion.h"
#include "treasure.h"
#include "position.h"
#include "name.h"
#include "stats.h"

#include <string>
#include <fstream>
#include <iostream>
#include "item.h"

#include "myrand.h"

using namespace std;

#include "dragonhoard.h"
#include "dragon.h"

#include "human.h"
#include "dwarf.h"
#include "elf.h"
#include "orc.h"
#include "merchant.h"
#include "halfling.h"

Level::Level() {

	auto display = make_shared<Display>();
	this->theDisplay = display;
	this->stopMovingEnemies = false;
	this->hasWon = false;
	this->curFloor = 1;
}
Level::~Level() {}


void Level::CreateLevels(string filename = "defaultmap.txt") {
	this->createDefaultMap(this->ogMap);
	this->theDisplay->setNumRows(this->assumedMapRows);
	this->theDisplay->setNumCols(this->assumedMapCols);
	this->createDefaultMap(this->theDisplay->getDisplayArray());


	this->createChambers();

	if (filename == "defaultmap.txt") {
		this->initializeEmptyMaps();
		this->randomlyGenerateMap();
	}

	else {
		this->readInMap(filename);
	}

	this->LoadMap(this->curFloor);

	this->pickUpGold();


}

void Level::randomlyGenerateMap() {
	for (int i = 0; i < this->amountOfLevels; i++) {
		int playerChamber;
		this->mapPlayer(i, playerChamber);
		this->mapStairs(i, playerChamber);
		for (int j = 0; j < this->numberOfPotions; j++) {
			this->mapPotions(i);
		}
		for (int j = 0; j < this->numberOfGold; j++) {
			this->mapGold(i);
		}
		for (int j = 0; j < numberOfEnemies; j++) {
			this->mapEnemies(i);
		}
	}
}

void Level::readInMap(std::string filename) {
    ifstream myfile{ filename };
    string line;
    for (int i = 0; i < this->amountOfLevels; i++) {
        vector < vector<char>> singleMap;
        for (int j = 0; j < this->assumedMapRows; j++) {
            vector<char> singleRow;
            int len = this->assumedMapCols;
            getline(myfile,line);
            for (int k = 0; k < len; k++) {
                //cout << "line[" << k << "] is " << line[k] << endl;
                singleRow.emplace_back(line[k]);
            }
            singleMap.emplace_back(singleRow);
        }
        maps.emplace_back(singleMap);
    }

}

void Level::LoadMap(int level) {
	int index = level - 1;

	for (int i = 0; i < this->assumedMapRows; i++) {
		for (int j = 0; j < this->assumedMapCols; j++) {
			char c = maps[index][i][j];
			Position pos{ i,j };

			if (c == '@') {
				this->spawnPlayer(pos);
			}

			else if (c == '\\') {
				this->spawnStairs(pos);
			}

			else if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5') {
				this->spawnPotions(pos, c);
			}

			else if (c == '6' || c == '7' || c == '8' || c == '9') {
				this->spawnGold(pos, c, index);
			}

			else if (c == 'H' || c == 'W' || c == 'E' || c == 'O' || c == 'M' || c == 'L') {
				//Note: Dragons are spawned in spawnGold
				this->spawnEnemies(pos, c);
			}

			else {
				this->theDisplay->setDisplayAtPos(pos, c);
			}
		}
	}

	//generate stuff
	sortEnemyArrayByPosition();

}

void Level::createDefaultMap(vector<vector<char>> & arr) {
	arr.clear();
	ifstream myfile{ "defaultmap.txt" };
	string s;

	while (getline(myfile, s)) {
		vector<char> singleRow;
		int len = s.size();

		for (int i = 0; i < len; i++) {
			singleRow.emplace_back(s[i]);
		}
		arr.emplace_back(singleRow);
	}

}
void Level::initializeEmptyMaps() {

	for (int i = 0; i < this->amountOfLevels; i++) {
		vector<vector<char>> singleMap;
		this->createDefaultMap(singleMap);
		this->maps.emplace_back(singleMap);
	}
}

//Spawns player in a random chamber
void Level::mapPlayer(int mapindex, int & playerChamber) {
	Random r;

	int ranChamber = r.Range(0, 4);
	Position playerPos = chambers[ranChamber]->randomGenerate(mapindex);

	this->maps[mapindex][playerPos.x][playerPos.y] = '@';
	playerChamber = ranChamber;
}

void Level::spawnPlayer(Position pos) {
	this->player->setPosition(pos);
	cout << pos.x << " " << pos.y << endl;
	this->theDisplay->setDisplayAtPos(pos, '@');
}

void Level::mapGold( int mapindex) {
	     Random r;
		int ranChamber = r.Range(0, 4);

		Position goldPos = chambers[ranChamber]->randomGenerate(mapindex);

		int goldTypeNumber = r.Range(1, 8);

		//Normal hoard = 6 on map
		if (goldTypeNumber >= 1 && goldTypeNumber <= 5) {
			this->maps[mapindex][goldPos.x][goldPos.y] = '6';
		}
		//Dragon hoard = 9 on map; D for dragon
		else if (goldTypeNumber == 6) {

			Position dragonPos = goldPos;
			int tries = 0;
			int max = 1000;
			bool successfullyFoundPosition = true;
			while (dragonPos == goldPos) {
			  dragonPos	= getRandomPositionAroundMap(goldPos, vector<char>{'.'}, mapindex);
			  tries++;
			  if (tries >= max) {
				  successfullyFoundPosition = false;
				  break;
			  }
			}
			if (successfullyFoundPosition) {
				this->maps[mapindex][goldPos.x][goldPos.y] = '9';
				this->maps[mapindex][dragonPos.x][dragonPos.y] = 'D';
			}
			else {
				cout << "Something went wrong with mapping DragonHoard!" << endl;
			}

		}
		//Small hoard = 7 on map
		else if (goldTypeNumber >= 7 && goldTypeNumber <= 8) {
			shared_ptr<Treasure> myGold = make_shared<Treasure>(goldPos, HoardType::Small);
			this->gold.emplace_back(myGold);
			this->maps[mapindex][goldPos.x][goldPos.y] = '7';
		}
}

void Level::spawnGold(Position pos, char thisType, int mapIndex) {


	if (thisType == '6') {
	shared_ptr<Treasure> myGold = make_shared<Treasure>(pos, HoardType::Normal);
	this->gold.emplace_back(myGold);
	}
	else if (thisType == '7') {
		shared_ptr<Treasure> myGold = make_shared<Treasure>(pos, HoardType::Small);
		this->gold.emplace_back(myGold);
	}
	else if (thisType == '8') {
	shared_ptr<Treasure> myGold = make_shared<Treasure>(pos, HoardType::Merchant);
	this->gold.emplace_back(myGold);
	}
	else if (thisType == '9' ){

		vector<Position> potentialPos{
			Position{ pos.x - 1, pos.y - 1 },
			Position{ pos.x, pos.y - 1 },
			Position{ pos.x + 1, pos.y - 1 },
			Position{ pos.x - 1 , pos.y },
			Position{ pos.x + 1, pos.y },
			Position{ pos.x - 1, pos.y + 1 },
			Position{ pos.x , pos.y + 1 },
			Position{ pos.x + 1, pos.y + 1 },
		};
		int len = potentialPos.size();
		bool hasSpawnedDragon = false;

		for (int i = 0; i < len; i++) {
			Position isDragonPos = potentialPos[i];

			if (potentialPos[i].x < 0 || potentialPos[i].x >= this->assumedMapRows || potentialPos[i].y < 0 || potentialPos[i].y >= this->assumedMapCols) {
				continue;
			}

			if (maps[mapIndex][isDragonPos.x][isDragonPos.y] == 'D') {


				int enemyCheck = this->enemies.size();

				bool dragonIsAlreadyThere = false;

				//Assumption: Is enemy is already there, then we cannot spawn the dragon
				for (int j = 0; j < enemyCheck; j++) {
					if (enemies[j]->getPosition() == isDragonPos) {
						dragonIsAlreadyThere = true;
						break;
					}
				}

				if (dragonIsAlreadyThere) {
					continue;
				}

				shared_ptr<Dragon> dragon = make_shared<Dragon>(isDragonPos, this);
				shared_ptr<DragonHoard> myGold = make_shared<DragonHoard>(pos, HoardType::Dragon, dragon);

				this->gold.emplace_back(myGold);
				cout << "Dragon : " << dragon->getPosition().x << " " << dragon->getPosition().y << endl;
				this->enemies.emplace_back(dragon);
				hasSpawnedDragon = true;

				this->theDisplay->setDisplayAtPos(isDragonPos, 'D');
				break;

			}

		}
		if (!hasSpawnedDragon) {
			cout << "Something went wrong with Dragon spawning!" << endl;
		}

	}
	else {
		cout << "Something went wrong " << endl;
	}
	this->theDisplay->setDisplayAtPos(pos, 'G');

}

void Level::mapPotions(int mapindex) {

	//Note it is just 1 to 5 to be consistent with the document
	//But the enum starts at 0, which is why it is -1
		Random r;

		int potionNumber = r.Range(0, 5);
		int ranChamber = r.Range(0, 4);

		Position potionPos = chambers[ranChamber]->randomGenerate(mapindex);

		if (potionNumber == 0) {
			this->maps[mapindex][potionPos.x][potionPos.y] = '0';
		}
		else if (potionNumber == 1) {
			this->maps[mapindex][potionPos.x][potionPos.y] = '1';
		}
		else if (potionNumber == 2) {
			this->maps[mapindex][potionPos.x][potionPos.y] = '2';
		}
        else if (potionNumber == 3) {
            this->maps[mapindex][potionPos.x][potionPos.y] = '3';
        }
		else if (potionNumber == 4) {
			this->maps[mapindex][potionPos.x][potionPos.y] = '4';
		}
		else if (potionNumber == 5) {
			this->maps[mapindex][potionPos.x][potionPos.y] = '5';
		}

	//Spawns potions in a random chamber
}
void Level::spawnPotions(Position pos, char thisType) {

	if (thisType == '0') {
		shared_ptr<Potion> potion = make_shared<Potion>(pos, PotionType::RestoreHealth);
		potions.emplace_back(potion);
	}
	else if (thisType == '1') {
		shared_ptr<Potion> potion = make_shared<Potion>(pos, PotionType::BoostAtk);
		potions.emplace_back(potion);
	}
	else if (thisType == '2') {
		shared_ptr<Potion> potion = make_shared<Potion>(pos, PotionType::BoostDef);
		potions.emplace_back(potion);
	}
    else if (thisType == '3') {
        shared_ptr<Potion> potion = make_shared<Potion>(pos, PotionType::PoisonHealth);
        potions.emplace_back(potion);
    }
	else if (thisType == '4') {
		shared_ptr<Potion> potion = make_shared<Potion>(pos, PotionType::WoundAtk);
		potions.emplace_back(potion);
	}
	else if (thisType == '5') {
		shared_ptr<Potion> potion = make_shared<Potion>(pos, PotionType::WoundDef);
		potions.emplace_back(potion);
	}
	else {
		cout << "Something went wrong with spawning potions!" << endl;
	}
	this->theDisplay->setDisplayAtPos(pos, 'P');

}

//Spawns stairs in a random chamber
void Level::mapStairs( int mapindex, int & playerChamber) {

	//TODO: PUT IN CHAMBER--------------------------------------
	Random r;
	int ranChamber = playerChamber;

	while (ranChamber == playerChamber) {
		ranChamber = r.Range(0, 4);
	}

	Position stairsPos = chambers[ranChamber]->randomGenerate(mapindex);
	this->maps[mapindex][stairsPos.x][stairsPos.y] = '\\';
}

void Level::spawnStairs(Position pos) {
	this->theDisplay->setDisplayAtPos(pos, '\\');
}

void Level::mapEnemies( int mapindex) {

	Random r;

		int ranChamber = r.Range(0, 4);
		Position enemyPos = chambers[ranChamber]->randomGenerate(mapindex);

		int enemyNumber = r.Range(1, this->numberOfTypesOfEnemies);

		//Hoomans
		if (enemyNumber == 1) {
			this->maps[mapindex][enemyPos.x][enemyPos.y] = 'H';
		}
		//Dwarfs
		else if (enemyNumber == 2) {
			this->maps[mapindex][enemyPos.x][enemyPos.y] = 'W';
		}
		//Elves
		else if (enemyNumber == 3) {
			this->maps[mapindex][enemyPos.x][enemyPos.y] = 'E';
		}
		//Orcs
		else if (enemyNumber == 4) {
			this->maps[mapindex][enemyPos.x][enemyPos.y] = 'O';
		}
		//Travelling merchants
		else if (enemyNumber == 5) {
			this->maps[mapindex][enemyPos.x][enemyPos.y] = 'M';
		}
		//Halflings
		else if (enemyNumber == 6) {
			this->maps[mapindex][enemyPos.x][enemyPos.y] = 'L';
		}
		else {
			cout << "WRONG THING : " << enemyNumber << endl;
		}


	//Spawns enemies in a random chamber
}

void Level::spawnEnemies(Position pos, char thisType) {

	if (thisType == 'H') {
		shared_ptr<Human> enemy = make_shared<Human>(pos, this);
		this->enemies.emplace_back(enemy);
	}
	else if (thisType == 'W') {
		shared_ptr<Dwarf> enemy = make_shared<Dwarf>(pos, this);
		this->enemies.emplace_back(enemy);
	}
	else if (thisType == 'E') {
		shared_ptr<Elf> enemy = make_shared<Elf>(pos, this);
		this->enemies.emplace_back(enemy);
	}
	else if (thisType == 'O') {
		shared_ptr<Orc> enemy = make_shared<Orc>(pos, this);
		this->enemies.emplace_back(enemy);
	}
	else if (thisType == 'M') {
		shared_ptr<Merchant> enemy = make_shared<Merchant>(pos, this);
		this->enemies.emplace_back(enemy);
	}
	else if (thisType == 'L') {
		shared_ptr<Halfling> enemy = make_shared<Halfling>(pos, this);
		this->enemies.emplace_back(enemy);
	}
	else {
		cout << "Mistake in spawnEnemies" << endl;
	}
	this->theDisplay->setDisplayAtPos(pos, thisType);


}


bool Level::getWon() {
	return this->hasWon;
}

void Level::setWon(bool won) {
	this->hasWon = won;
}
static int doSpawnPlayer = 0;

void Level::reset() {
     //Clears lists so they can respawn again
    this->enemies.clear();
	this->potions.clear();
	this->gold.clear();

	//Clears maps, and sets it to default
	this->getDisplay()->getDisplayArray().clear();
	this->createDefaultMap(this->theDisplay->getDisplayArray());
}

void Level::nextFloor() {
	this->hasWon = true;
	this->reset();
	this->curFloor++;
	//Clear map
	if (this->curFloor <= this->amountOfLevels) {
		this->LoadMap(this->curFloor);
		this->player->revertToBaseStats();
	}

}

void Level::notifyMerchants() {
	merchantsHostile = true;
}

bool Level::areMerchantsHostile() {
	return this->merchantsHostile;
}

void Level::playerTurn() {
	this->player->TurnStart();
}

void Level::enemyTurn() {

	//Move/Attack....

	int len = this->enemies.size();
	for (int i = 0; i < len; i++) {
		this->enemies[i]->TurnStart();
		bool isDragon = !(dynamic_pointer_cast<Dragon> (enemies[i]) == nullptr);

		bool isInRange = this->enemies[i]->getPosition().isInRadiusOf(this->player->getPosition());

		if (isInRange || isDragon) {
			if (this->enemies[i]->getIsHostile()  || (isDragon && isInRange) ) {
				this->EnemyAttack(i);
			}
		}
		else {
			if (this->stopMovingEnemies == false) {
				this->EnemyMove(i);
			}
		}
	}
	sortEnemyArrayByPosition();


}

void Level::EnemyAttack(int i) {

		this->enemies[i]->Attack(*this->player);
		if (player->getStats().HP == 0) {
			//Lose the game
			theDisplay->setDisplayAtPos(this->player->getPosition(), 'X');
		}

}

void Level::EnemyMove(int i) {
	Position enemyPos = this->enemies[i]->getPosition();
	Position movePos = this->getRandomPositionAround(enemyPos, vector<char>{'.'});

	bool success = this->enemies[i]->Move(movePos);

	if (success) {
		this->theDisplay->setDisplayAtPos(enemyPos, '.');
		this->theDisplay->setDisplayAtPos(movePos, this->enemies[i]->getName().symbol);
	}
}

bool Level::getStopMovingEnemies() {
	return this->stopMovingEnemies;
}

void Level::setStopMovingEnemies(bool set) {
	this->stopMovingEnemies = set;
}

//Collision detection
bool Level::isTileAvailable(Position pos, vector<char> travelableTiles) {

	if (pos.x < 0 || pos.x >= theDisplay->getNumRows() || pos.y < 0 || pos.y >= theDisplay->getNumCols()) return false;

	bool isTravelable = false;
	int len = travelableTiles.size();
	char tile = this->theDisplay->getDisplayAtPos(pos);

	for (int i = 0; i < len; i++) {
		if (tile == travelableTiles[i]) {
			isTravelable = true;
			break;
		}
	}
	return isTravelable;
}

char Level::getCharAt(Position pos){
    return theDisplay->getDisplayAtPos(pos);
}


void Level::createChambers() {
//Creates a random chamber
    for(int i=0; i<5; i++){
        chambers.emplace_back(make_shared<Chamber>(i, this));
    }
}

void Level::setPlayer(std::shared_ptr<Player> character) {
	this->player = character;
}

shared_ptr<Player> Level::getPlayer() {
	return this->player;
}

Position Level::translatePos(std::string direction, Position pos) {
	Position to = pos;
	if (direction == "nw") {
		to.x--;
		to.y--;
	}
	else if (direction == "n") {
		to.x--;
	}
	else if (direction == "ne") {
		to.x--;
		to.y++;
	}
	else if (direction == "w") {
		to.y--;
	}
	else if (direction == "e") {
		to.y++;
	}
	else if (direction == "sw") {
		to.x++;
		to.y--;
	}
	else if (direction == "s") {
		to.x++;
	}
	else if (direction == "se") {
		to.x++;
		to.y++;
	}
	return to;
}

bool Level::movePlayer(string direction) {
	this->player->TurnStart();

	Position playerpos = getPlayerPos();
	Position to = translatePos(direction, playerpos);

	cout << "Player Position: " << playerpos.x << " " << playerpos.y << endl;
	cout << "Char at: " << this->theDisplay->getDisplayAtPos(to) << endl;

	//this->theDisplay->setDisplayAtPos(to, '\\');

   // char toSymbol = getCharAt(to);


	if (this->isTileAvailable(to, vector<char> {'.', '+', '#', '\\', 'G'} )) {
		//char prevPosChar = theDisplay->getDisplayAtPos(playerpos);
		Position prevPos = this->player->getPosition();
		this->player->Move(to);
		if (this->theDisplay->getDisplayAtPos(to) == '\\') {
			nextFloor();
			return true;
		}

        if(this->theDisplay->getDisplayAtPos(to) == 'G'){
            pickUpGold();
        }

        char ogSymbol = ogMap[prevPos.x][prevPos.y];
		theDisplay->setDisplayAtPos(prevPos, ogSymbol);
		theDisplay->setDisplayAtPos(to, '@');

		pickUpGold();

		return true;
	}
	else {
		return false;
	}
}


int Level::getCurFloor() {
	return this->curFloor;
}

bool Level::PlayerAttack(string direction) {
	this->player->TurnStart();

	Position playerPos = player->getPosition();
	Position targetPos = translatePos(direction, playerPos);

	int len = this->enemies.size();
	bool hasAttacked = false;
	for (int i = 0; i < len; i++) {
		Position enemyPos = this->enemies[i]->getPosition();
		if (enemyPos == targetPos) {
			this->player->Attack(*this->enemies[i]);
			hasAttacked = true;

			if (this->enemies[i]->getStats().HP == 0) {
				this->theDisplay->setDisplayAtPos(enemyPos, '.');
				this->enemies.erase(enemies.begin() + i);
			}
			break;
		}
	}
	return hasAttacked;

}

Position Level::getPlayerPos() {
	return this->player->getPosition();
}

shared_ptr<Display>  Level::getDisplay(){
	return this->theDisplay;
}

bool Level::usePotion(string direction) {
	this->player->TurnStart();

	Position playerpos = player->getPosition();
	Position target = translatePos(direction, playerpos);

	int len = this->potions.size();
	bool usedPotion = false;

	for (int i = 0; i < len; i++) {
		Position potionpos = this->potions[i]->getPos();
		//cout << "Potion : " << this->potions[i]->getPos().x << " " << this->potions[i]->getPos().y << endl;

		if (target == potionpos) {
			this->player->usePotion(*this->potions[i]);
			this->theDisplay->setDisplayAtPos(potionpos, '.');
			this->potions.erase(potions.begin() + i);
			usedPotion = true;
			break;
		}
	}
	return usedPotion;
}


void Level::pickUpGold() {
	Position pos = player->getPosition();
	int len = this->gold.size();

	for (int i = 0; i < len; i++) {
		Position goldpos = this->gold[i]->getPos();
		bool isDragonGold = !(dynamic_pointer_cast<DragonHoard> (gold[i]) == nullptr);

		if (!isDragonGold) {
			if (goldpos == pos) {
				int goldAmount = gold[i]->getGold();
				this->player->addGold(goldAmount);
				gold.erase(gold.begin() + i);
				cout << this->player->getName().name << " has found " << goldAmount << " gold!" << endl;
				break;
			}
		}
		else {
			shared_ptr<DragonHoard> dragonHoard = dynamic_pointer_cast<DragonHoard> (gold[i]);
		   if (dragonHoard->isDragonAlive() && this->player->getPosition().isInRadiusOf(gold[i]->getPos())) {
				dragonHoard->notifyDragon();
				cout << "The dragon does not want you take its gold. Slay it to steal all of its money" << endl;
		   }
		   else if (dragonHoard->isDragonAlive()) {
			   dragonHoard->unNotifyDragon();
		   }
		   else {
				if (goldpos == pos) {
					int goldAmount = gold[i]->getGold();
					this->player->addGold(goldAmount);
					gold.erase(gold.begin() + i);
					cout << this->player->getName().name << " has found " << goldAmount << " gold!" << endl;
					break;
				}
			}

		   if (!(pos == goldpos)) {
               if(dragonHoard->isDragonAlive()){
                   this->theDisplay->setDisplayAtPos(goldpos, 'G');
               }
               else{
               }
		   }

		}

	}
}



Position Level::getRandomPositionAround(Position pos, std::vector<char> tilableCharacters) {

	vector<Position> potentialPos{
		Position{ pos.x - 1, pos.y - 1 },
		Position{ pos.x, pos.y - 1 },
		Position{ pos.x + 1, pos.y - 1 },
		Position{ pos.x - 1 , pos.y },
		//Position{ pos.x, pos.y },
		Position{ pos.x + 1, pos.y },
		Position{ pos.x - 1, pos.y + 1 },
		Position{ pos.x , pos.y + 1 },
		Position{ pos.x + 1, pos.y + 1 },
	};
	vector<Position> potentialCanidates;
	int posLen = potentialPos.size();

	int charactersLen = tilableCharacters.size();

	for (int i = 0; i < posLen; i++) {
		for (int j = 0; j < charactersLen; j++) {

			if (potentialPos[i].x < 0 || potentialPos[i].x >= theDisplay->getNumRows() || potentialPos[i].y < 0 || potentialPos[i].y >= theDisplay->getNumCols()) {
				continue;
			}

			if (this->theDisplay->getDisplayAtPos(potentialPos[i]) == tilableCharacters[j]) {
				potentialCanidates.emplace_back(potentialPos[i]);
				break;
			}
		}
	}

	int finalLen = potentialCanidates.size() -1;
	if (finalLen < 0) {
		return pos;  //If no position is available, return original
	}

	Random r;
	int randomIndex = r.Range(0, finalLen);
	return potentialCanidates[randomIndex];

}

Position Level::getRandomPositionAroundMap(Position pos, std::vector<char> tilableCharacters, int mapIndex) {

	vector<Position> potentialPos{
		Position{ pos.x - 1, pos.y - 1 },
		Position{ pos.x, pos.y - 1 },
		Position{ pos.x + 1, pos.y - 1 },
		Position{ pos.x - 1 , pos.y },
		//Position{ pos.x, pos.y },
		Position{ pos.x + 1, pos.y },
		Position{ pos.x - 1, pos.y + 1 },
		Position{ pos.x , pos.y + 1 },
		Position{ pos.x + 1, pos.y + 1 },
	};
	vector<Position> potentialCanidates;
	int posLen = potentialPos.size();

	int charactersLen = tilableCharacters.size();

	for (int i = 0; i < posLen; i++) {
		for (int j = 0; j < charactersLen; j++) {

			if (potentialPos[i].x < 0 || potentialPos[i].x >= this->assumedMapRows || potentialPos[i].y < 0 || potentialPos[i].y >= this->assumedMapCols) {
				continue;
			}

			if (this->maps[mapIndex][potentialPos[i].x][potentialPos[i].y] == tilableCharacters[j]) {
				potentialCanidates.emplace_back(potentialPos[i]);
				break;
			}
		}
	}

	int finalLen = potentialCanidates.size() - 1;
	if (finalLen < 0) {
		return pos;  //If no position is available, return original
	}

	Random r;
	int randomIndex = r.Range(0, finalLen);
	return potentialCanidates[randomIndex];

}

void Level::DropItemAt(shared_ptr<Item>  item, Position pos, bool isRand) {
	if (!isRand) {
		theDisplay->setDisplayAtPos(pos, item->getName().symbol);
		item->setPos(pos);
	}
	else {
		Position randPos = this->getRandomPositionAround(pos, vector<char> {'.'});
		theDisplay->setDisplayAtPos(randPos, item->getName().symbol);
		item->setPos(randPos);
	}
	auto isTreasure = dynamic_pointer_cast<Treasure>(item);
	if (isTreasure != nullptr) {
		this->gold.emplace_back(isTreasure);
	}
}

void Level::generateItemByChar(int row, int col, char symbol) {
	if (symbol == '0') {
		shared_ptr<Potion> potion = make_shared<Potion>(Position{ row, col }, PotionType::RestoreHealth);
		this->potions.emplace_back(potion);
	}
	else if (symbol == '1') {
		shared_ptr<Potion> potion = make_shared<Potion>(Position{ row, col }, PotionType::BoostAtk);
		this->potions.emplace_back(potion);
	}
	else if (symbol == '2') {
		shared_ptr<Potion> potion = make_shared<Potion>(Position{ row, col }, PotionType::BoostDef);
		this->potions.emplace_back(potion);
	}
    else if (symbol == '3') {
        shared_ptr<Potion> potion = make_shared<Potion>(Position{ row, col }, PotionType::PoisonHealth);
        this->potions.emplace_back(potion);
    }
	else if (symbol == '4') {
		shared_ptr<Potion> potion = make_shared<Potion>(Position{ row, col }, PotionType::WoundAtk);
		this->potions.emplace_back(potion);
	}
	else if (symbol == '5') {
		shared_ptr<Potion> potion = make_shared<Potion>(Position{ row, col }, PotionType::WoundDef);
		this->potions.emplace_back(potion);
	}
	else if (symbol == '6') {
		shared_ptr<Treasure> myGold = make_shared<Treasure>(Position{ row, col }, HoardType::Normal);
		this->gold.emplace_back(myGold);
	}
	else if (symbol == '7') {
		shared_ptr<Treasure> myGold = make_shared<Treasure>(Position{ row, col }, HoardType::Small);
		this->gold.emplace_back(myGold);
	}
	else if (symbol == '8') {

		shared_ptr<Treasure> myGold = make_shared<Treasure>(Position{ row, col }, HoardType::Merchant);
		this->gold.emplace_back(myGold);
	}
	else if (symbol == '9') {
		shared_ptr<Dragon> dragon = make_shared<Dragon>(getRandomPositionAround(Position{ row, col }, vector<char>{'.'}) , this );
		shared_ptr<DragonHoard> myGold = make_shared<DragonHoard>(Position{ row, col }, HoardType::Small, dragon);

		this->gold.emplace_back(myGold);
		this->enemies.emplace_back(dragon);
	}
	else {
		//A mistake you have made
	}


}


void Level::sortEnemyArrayByPosition() {
	int len = enemies.size();
	for (int i = 0; i < len - 1; i++) {
		Position pos = enemies[i]->getPosition();
		int index = i;
		for (int j = i + 1; j < len; j++) {
			Position indexedPos = enemies[j]->getPosition();
			if (indexedPos.x < pos.x || indexedPos.x == pos.x && indexedPos.y < pos.y) {
				index = j;
			}
		}
		//swap
		using std::swap;
		swap(enemies[i], enemies[index]);
	}

}
std::vector <std::vector<std::vector<char>>> Level::getMaps() {
	return this->maps;
}

void Level::setMaps(int mapIndex, int x, int y, char value) {
	this->maps[mapIndex][x][y] = value;
}

ostream & operator<< (ostream & ss, const shared_ptr<Level> level) {
	shared_ptr<Display> display = level->getDisplay();
	vector<vector<char>> displayArr = display->getDisplayArray();
	int len = displayArr.size();

	for (int i = 0; i < len; i++) {
		string row;
		int size = displayArr[i].size();
		for (int j = 0; j < size; j++) {
			row += displayArr[i][j];
		}
		ss << row;
	}
	return ss;

}
