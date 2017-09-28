#include "item.h"
#include "position.h"
#include "name.h"


Item::Item(Position pos) {
	this->pos = pos;
}

Item::~Item() {}

Position Item::getPos() {
	return this->pos;
}

Name Item::getName() {
	return this->name;
}

void Item::setPos(Position pos) {
    this->pos = pos;
}

