all: Main.o Helper.o Interface.o Transactional_Commands.o 
	g++ -std=gnu++14 Main.o Helper.o Interface.o Transactional_Commands.o -pthread

Main.o: Main.cpp
	g++ -std=gnu++14 -c Main.cpp

Helper.o: Helper.cpp
	g++ -std=gnu++14 -c Helper.cpp

Interface.o: Interface.cpp
	g++ -std=gnu++14 -c Interface.cpp

Transactional_Commands.o: Transactional_Commands.cpp
	g++ -std=gnu++14 -c Transactional_Commands.cpp

clean:
	rm Main.o Helper.o Interface.o Transactional_Commands.o

wipe:
	rm Main.o Helper.o Interface.o Transactional_Commands.o Main.cpp Helper.cpp Helper.hpp Interface.cpp Interface.hpp Transactional_Commands.cpp Transactional_Commands.hpp Common.hpp
