all: Main.o Helper.o Interface.o Transactional_Commands.o Fact.o Base.o Parse.o Rule.o
	g++ -std=gnu++14 Main.o Helper.o Interface.o Transactional_Commands.o Fact.o Base.o Parse.o Rule.o -pthread

Main.o: Main.cpp
	g++ -std=gnu++14 -c Main.cpp

Helper.o: Helper.cpp
	g++ -std=gnu++14 -c Helper.cpp

Interface.o: Interface.cpp
	g++ -std=gnu++14 -c Interface.cpp

Transactional_Commands.o: Transactional_Commands.cpp
	g++ -std=gnu++14 -c Transactional_Commands.cpp

Fact.o: Fact.cpp
	g++ -std=gnu++14 -c Fact.cpp

Base.o: Base.cpp
	g++ -std=gnu++14 -c Base.cpp

Parse.o: Parse.cpp
	g++ -std=gnu++14 -c Parse.cpp

Rule.o: Rule.cpp
	g++ -std=gnu++14 -c Rule.cpp

clean:
	rm Main.o Helper.o Interface.o Transactional_Commands.o Fact.o Base.o Parse.o Rule.o

wipe:
	rm Main.o Helper.o Interface.o Transactional_Commands.o Main.cpp Helper.cpp Helper.hpp Interface.cpp Interface.hpp Transactional_Commands.cpp Transactional_Commands.hpp Common.hpp Fact.o Fact.cpp Fact.hpp Rule.o Rule.cpp Rule.hpp Parse.o Parse.cpp Parse.hpp Base.o Base.cpp Base.hpp
