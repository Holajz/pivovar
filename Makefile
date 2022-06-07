#Makefile
#Zdrojovy soubor
PROJ=main.cpp Filtration.cpp Fermentation.cpp MainLine.cpp MaltProduction.cpp MaterialHolder.cpp MaterialGenerator.cpp WortProduction.cpp CarProcess.cpp

#Hlavickove soubory
HEADS=main.h Filtration.h Fermentation.h MainLine.h MaltProduction.h MaterialHolder.h MaterialGenerator.h WortProduction.h CarProcess.h

args=in

SIMLIB_DIR=../simlib/src/
SIMLIB_DEPEND=$(SIMLIB_DIR)/simlib.so $(SIMLIB_DIR)/simlib.h

#Nazev souboru
EXECT=pivovar

OBJ=$(PROJ:.cpp=.o)

#Nazev zazipovaneho souboru
ZIP_JMENO=02_xholik13.zip

#Nazev zatarovan0ho souboru
TAR_JMENO=02_xholik13.tar

#Dalsi soubory k zazipovani (zbytek .c souboru + dokumentace)
ZIP_SOUBORY=Makefile dokumentace.pdf main.cpp Filtration.cpp Fermentation.cpp MainLine.cpp MaltProduction.cpp MaterialHolder.cpp MaterialGenerator.cpp WortProduction.cpp main.h Filtration.h Fermentation.h MainLine.h MaltProduction.h MaterialHolder.h MaterialGenerator.h WortProduction.h CarProcess.cpp Carprocess.h

#Argumenty valgrind
ARGS=-v --leak-check=full --track-origins=yes --show-reachable=yes --tool=memcheck

#######################################################

#Kompilator
CC=g++

#Nastaveni kompilatoru
CFLAGS=-c -ggdb -std=c++11 -pedantic -W -Wextra -Wfloat-equal -Wall

LFLAGS= -lsimlib -lm

#######################################################

# .c -> .o
#%.o: %.c $(HEADS)
#	$(CC) $(CFLAGS) -c -o $@ $< 

all: clean $(EXECT)

$(EXECT): $(OBJ)
	$(CC) $(OBJ) -o $(EXECT) $(LFLAGS)

$(OBJ): $(PROJ) $(HEADS)
	$(CC) $(CFLAGS) $(PROJ)

run: all
	./$(EXECT)
	
#check: all
#	valgrind $(ARGS) ./$(EXECT)

zip: all
	rm -rf $(ZIP_JMENO)
	zip $(ZIP_JMENO) $(ZIP_SOUBORY)

tar: all
	rm -rf $(TAR_JMENO)
	tar -czvf $(TAR_JMENO) $(ZIP_SOUBORY)

clean:
	rm -rf $(EXECT)
	rm -rf *.o
