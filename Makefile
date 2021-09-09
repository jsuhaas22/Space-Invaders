SI : main.o Ship.o Game.o constants.o
	g++ -lsfml-system -lsfml-graphics -lsfml-window main.o Ship.o Game.o constants.o -o SI

main.o : main.cpp Game.hpp
	g++ -c main.cpp

Ship.o : Ship.cpp Ship.hpp constants.hpp
	g++ -c Ship.cpp

Game.o : Game.cpp Game.hpp
	g++ -c Game.cpp

constants.o : constants.cpp constants.hpp
	g++ -c constants.cpp

clean:
	rm main.o Ship.o Game.o constants.o
