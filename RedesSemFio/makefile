#Primeiro MakeFile

all:redes

redes: main.o Coordenador.o 
	g++ -o redes main.o Coordenador.o

main.o: main.cpp ./Coordenador/Coordenador.hpp
	g++ -o main.o main.cpp

Coordenador.o: Coordenador/Coordenador.cpp Coordenador/Coordenador.hpp
	g++ -o Coordenador/Coordenador.cpp Coordenador/Coordenador.hpp