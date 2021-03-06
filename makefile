all: server client

server: server_stream.o Helper.o Interface.o Transactional_Commands.o Fact.o Base.o Threading.o Rule.o
	g++ -std=gnu++14 Helper.o Threading.o Interface.o Transactional_Commands.o Fact.o Base.o Rule.o server_stream.o -pthread -o server

client: client_stream.o Helper.o Interface.o Transactional_Commands.o Fact.o Base.o Threading.o Rule.o
	g++ -std=gnu++14 Helper.o Interface.o Threading.o Transactional_Commands.o Fact.o Base.o Rule.o client_stream.o -pthread -o client

client_stream.o: client_stream.cpp
	g++ -std=gnu++14 -c client_stream.cpp

server_stream.o: server_stream.cpp
	g++ -std=gnu++14 -c server_stream.cpp

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

Rule.o: Rule.cpp
	g++ -std=gnu++14 -c Rule.cpp

Threading.o: Threading.cpp
	g++ -std=gnu++14 -c Threading.cpp

clean:
	rm Main.o Helper.o Interface.o Transactional_Commands.o Fact.o Base.o Rule.o server_stream.o client_stream.o Threading.o

wipe:
	rm Main.o Helper.o Interface.o Transactional_Commands.o Main.cpp Helper.cpp Helper.hpp Threading.cpp Threading.hpp Threading.o Interface.cpp Interface.hpp Transactional_Commands.cpp Transactional_Commands.hpp Common.hpp Fact.o Fact.cpp Fact.hpp Rule.o Rule.cpp Rule.hpp Base.o Base.cpp Base.hpp
