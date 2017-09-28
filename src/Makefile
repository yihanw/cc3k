CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla
EXEC = cc3k
OBJECTS = main.o	level.o	game.o	orc.o	chamber.o	drow.o	enemy.o	goblin.o	potion.o	treasure.o	troll.o	vampire.o	merchant.o	human.o	dragonhoard.o	item.o	display.o	dragon.o	dwarf.o	elf.o	halfling.o	character.o	player.o	shade.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
