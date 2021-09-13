SI : main.o Ship.o Game.o Alien.o Bullet.o constants.o
	g++ -lsfml-system -lsfml-graphics -lsfml-window main.o Ship.o Game.o Alien.o Bullet.o constants.o -o SI

main.o : main.cpp Game.hpp
	g++ -c main.cpp

Ship.o : Ship.cpp Ship.hpp constants.hpp
	g++ -c Ship.cpp

Game.o : Game.cpp Game.hpp Bullet.hpp
	g++ -c Game.cpp

Alien.o : Alien.cpp constants.hpp Alien.hpp
	g++ -c Alien.cpp

Bullet.o : Bullet.cpp Bullet.hpp
	g++ -c Bullet.cpp

constants.o : constants.cpp constants.hpp
	g++ -c constants.cpp

clean:
	rm main.o Ship.o Game.o Alien.o Bullet.o constants.o
