all:redes
all: clean
all: exec

redes: main.o Coordenador.o Hospedeiro.o CamadaRede.o CamadaFisica.o CamadaEnlance.o TabelaRoteamento.o
	g++ -g main.o Hospedeiro.o -o redes

main.o: main.cpp # Primeiro define o retorno e o segundo os argumentos
	g++ -g -c main.cpp

Coordenador.o: Coordenador/Coordenador.cpp # Argumentos para ser utilizado do g++
	g++ -g -c Coordenador/Coordenador.cpp

Hospedeiro.o: Hospedeiro/Hospedeiro.cpp
	g++ -g -c Hospedeiro/Hospedeiro.cpp

CamadaRede.o: CamadaRede/CamadaRede.cpp
	g++ -g -c CamadaRede/CamadaRede.cpp

CamadaFisica.o: CamadaFisica/CamadaFisica.cpp
	g++ -g -c CamadaFisica/CamadaFisica.cpp

CamadaEnlance.o: CamadaEnlace/CamadaEnlace.cpp
	g++ -g -c CamadaEnlace/CamadaEnlace.cpp

TabelaRoteamento.o: TabelaRoteamento/TabelaRoteamento.cpp
	g++ -g -c TabelaRoteamento/TabelaRoteamento.cpp
	
clean:
	rm -f *.o

exec:
	clear
	./redes