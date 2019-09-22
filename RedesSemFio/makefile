all:redes
all: clean
all: exec

redes: main.o Coordenador.o Hospedeiro.o CamadaRede.o CamadaFisica.o CamadaEnlance.o
	g++ main.o Hospedeiro.o Coordenador.o -o redes

main.o: main.cpp # Primeiro define o retorno e o segundo os argumentos
	g++ -c main.cpp

Coordenador.o: Coordenador/Coordenador.cpp # Argumentos para ser utilizado do g++
	g++ -c Coordenador/Coordenador.cpp

Hospedeiro.o: Hospedeiro/Hospedeiro.cpp
	g++ -c Hospedeiro/Hospedeiro.cpp

CamadaRede.o: CamadaRede/CamadaRede.cpp
	g++ -c CamadaRede/CamadaRede.cpp

CamadaFisica.o: CamadaFisica/CamadaFisica.cpp
	g++ -c CamadaFisica/CamadaFisica.cpp

CamadaEnlance.o: CamadaEnlace/CamadaEnlace.cpp
	g++ -c CamadaEnlace/CamadaEnlace.cpp

clean:
	rm -f *.o

exec:
	clear
	./redes