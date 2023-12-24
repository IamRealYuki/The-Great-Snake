.PHONY: all

all: compile link
	
compile:	
	g++ -ISFMLlib/include -c main.cpp 

link: 
	g++ main.o -o SFMLlib/bin/snake -LSFMLlib/lib -lsfml-graphics -lsfml-window -lsfml-system

run:
	./SFMLlib/bin/snake.exe
	