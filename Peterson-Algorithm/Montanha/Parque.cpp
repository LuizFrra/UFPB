/*
 * Parque.cpp
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#include "Parque.h"
#include "Passageiro.h"

std::atomic<int> Parque::numPessoas;

Parque::Parque() {
}

Parque::~Parque() {
}

void Parque::addPassageiro(Passageiro *p) {
	passageiros.push_back(p);
}

vector<Passageiro*>& Parque::getPassageiros() {
	return passageiros;
}
