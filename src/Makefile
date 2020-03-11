#OBJS files to be compiled
OBJS = card.cpp deck.cpp combination.cpp book.cpp run.cpp partialBook.cpp partialRun.cpp combinationFinder.cpp player.cpp human.cpp computer.cpp round.cpp game.cpp gameFile.cpp main.cpp

#CC specify compiler
CC = g++

#CCC alternative compiler (usually clang)
CCC = 

#COMPILER_FLAGS passed to both compilers
COMPILER_FLAGS = -g -w -std=c++11 -Wall -pedantic -lm

#LINKER_FLAGS passed to both compilers
LINKER_FLAGS =

#OBJ_NAME name of executable
OBJ_NAME = project

#the target that compiles the executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

alt : $(OBJS)
	$(CCC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

debug : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) -g $(LINKER_FLAGS) -o $(OBJ_NAME)

altdebug : $(OBJS)
	$(CCC) $(OBJS) $(COMPILER_FLAGS) -g $(LINKER_FLAGS) -o $(OBJ_NAME)

opt : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) -O3 $(LINKER_FLAGS) -o $(OBJ_NAME)

altopt : $(OBJS)
	$(CCC) $(OBJS) $(COMPILER_FLAGS) -O4 $(LINKER_FLAGS) -o $(OBJ_NAME)

clean :
	rm project
