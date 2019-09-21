all:redes
all: clean

redes: main.o Coordenador.o
	g++ main.o Coordenador.o -o redes

main.o: main.cpp # Primeiro define o retorno e o segundo os argumentos
	g++ -c main.cpp

Coordenador.o: Coordenador/Coordenador.cpp # Argumentos para ser utilizado do g++
	g++ -c Coordenador/Coordenador.cpp

clean:
	rm -f *.o