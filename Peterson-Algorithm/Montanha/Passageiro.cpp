/*
 * Passageiro.cpp
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#include "Passageiro.h"
#include "Carro.h"
#include "Parque.h"
#include <stdio.h>
#include <stdlib.h>
#include <atomic>
#include <unistd.h>
#include <time.h>
#include <iostream>
#include <chrono>
#include <thread>

#define MAX_NUM_VOLTAS 3
int Passageiro::g = 0;
int Passageiro::estagios[8];
int Passageiro::ultimo[8];
std::atomic_flag lock = ATOMIC_FLAG_INIT;
std::atomic_flag lock2 = ATOMIC_FLAG_INIT;
std::atomic_flag lock3 = ATOMIC_FLAG_INIT;
//std::atomic_flag lock4 = ATOMIC_FLAG_INIT;
//std::atomic_flag debug = ATOMIC_FLAG_INIT;
//std::atomic_flag debug2 = ATOMIC_FLAG_INIT;

Passageiro::Passageiro(int id, Carro *c) {
	this->id = id;
	this->carro = c;
	srand(unsigned(time(NULL)));
}

Passageiro::~Passageiro() {
}

void Passageiro::entraNoCarro() {
	int j = 0, k = 0;
	lock.clear();
	std::this_thread::sleep_for(std::chrono::milliseconds(500*id));
	for(j = 0; j < 8; j++){
		estagios[id] = j;
		ultimo[j] = id;
		for(k = 0; k < 8; k++){
			if(k != id)
				while(estagios[k] >= estagios[id] && ultimo[j] == id );					
		}
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
	//std::cout << "Prendi Aqui" << std::endl;
	while(lock.test_and_set());
	if(carro->numPassageiros == 5)
		while(carro->numPassageiros != 0);
	std::cout << "O Passageiro " << id << " Entrou no carro" << std::endl;
	carro->numPassageiros++;
	estagios[id] = 0;
	lock.clear();
}	


void Passageiro::esperaVoltaAcabar() {
	carro->daUmaVolta();
}	

void Passageiro::saiDoCarro() {
	while(lock2.test_and_set());	
	g++;	
	std::cout << " O Passageiro " << id << " Saiu do carro" << std::endl;
	if(g == 5 ){
		carro->numPassageiros = 0;
		g = 0;
	}
	lock2.clear();
	std::this_thread::sleep_for(std::chrono::milliseconds(100*id));
}

void Passageiro::passeiaPeloParque() {
	std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 20));
	//sleep((rand() % 20) + 1);
	sleep(1);
}

bool Passageiro::parqueFechado() {
	if (carro->getNVoltas() < MAX_NUM_VOLTAS){
		//while(lock3.test_and_set());
		//std::cout << "O Passageiro  " << id << " Entrou no parque." << std::endl;
		//lock3.clear();
		return false;
	}
	std::cout << " O Parque Fechou" << std::endl;
	return true;
}

void Passageiro::run() {
	while (!parqueFechado()) {
		//std::cout << " Os Passageiro Estao entrando no carro" << std::endl;
		entraNoCarro(); // a
		carro->esperaEncher();
		//std::cout << " O Carro esta dando a volta, Espere acabar" << std::endl;
		esperaVoltaAcabar();
		//std::cout << " A volta acabou, os passageiros vao sair do carro" << std::endl;
		saiDoCarro(); // 
		carro->esperaEsvaziar();
		//std::cout << " Os Passageiros Sairam do Parque, agora vao passear" << std::endl;
		passeiaPeloParque(); 
	}

	while(Parque::numPessoas > 0){ 
		Parque::numPessoas.fetch_add(-1, std::memory_order_seq_cst);	// NÃO ESTAMOS UTILIZANDO ISSO EM LUGAR NENHUM - DISCUTIR OQ DEVERA SER FEITO
	 	//decrementa o numero de pessoas no parque
	}
}

