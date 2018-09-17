/*
 * Carro.cpp
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#include "Carro.h"
#include "Parque.h"
#include <stdlib.h>
#include <unistd.h>

const int Carro::CAPACIDADE = 5;
std::atomic<int> Carro::numPassageiros;



Carro::Carro() {
	this->cont = 0;
	this->voltas = 0;
}

Carro::~Carro() {
}

void Carro::esperaEncher() {
	while (Carro::numPassageiros != Carro::CAPACIDADE) { 
		sleep(1); 
	}
}
void Carro::daUmaVolta(){
	sleep(2);
}


void Carro::esperaEsvaziar() {
	if(cont == 10){
		voltas++;
		cont = 0;
	}
	while (Carro::numPassageiros != 0) 
		sleep(1); 
}

int Carro::getNVoltas() {
	cont++;
	return voltas;
}

void Carro::run() {
	while (Parque::numPessoas > 0) {
		esperaEncher();

		daUmaVolta();

		esperaEsvaziar();

	}
}
