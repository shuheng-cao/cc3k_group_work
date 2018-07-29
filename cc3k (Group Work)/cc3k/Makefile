CXX = g++
CXXFLAGS = -std=c++14 -Wextra -Wpedantic -Wall -Werror=vla -MMD -g 
MAIN_OBJECTS = main.o character.o grid.o item.o observer.o subject.o textdisplay.o dlc_controller.o normal_controller.o
ENEMY_OBJECTS = enemy/dragon.o enemy/dwarf.o enemy/elf.o enemy/enemy.o enemy/halfing.o enemy/human.o enemy/merchant.o enemy/orc.o enemy/wolf.o
FACTORY_OBJECTS = factory/enemy_factory.o factory/factory.o factory/pc_factory.o factory/potion_factory.o factory/treasure_factory.o
PC_OBJECTS = pc/pc.o pc/drow.o pc/goblin.o pc/shade.o pc/troll.o pc/vampire.o pc/witch.o
POTION_OBJECTS = potion/potion.o potion/ba.o potion/bd.o potion/ph.o potion/rh.o potion/wa.o potion/wd.o
TREASURE_OBJECTS = treasure/dragon_hoard.o treasure/merchant_hoard.o treasure/normal_hoard.o treasure/small_hoard.o treasure/treasure.o
OBJECTS = ${MAIN_OBJECTS} ${FACTORY_OBJECTS} ${PC_OBJECTS} ${POTION_OBJECTS} ${ENEMY_OBJECTS} ${TREASURE_OBJECTS}
DEPENDS = ${OBJECTS:.o=.d}
EXEC = cc3k

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lcurses

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
