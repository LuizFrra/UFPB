/*
 * Carro.h
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#ifndef CARRO_H_
#define CARRO_H_

#include <atomic>

class Parque;

class Carro {
public:
	static const int CAPACIDADE;
	static std::atomic<int> numPassageiros;

	Carro();
	virtual ~Carro();
	void esperaEncher();
	void daUmaVolta();
	void esperaEsvaziar();
	int getNVoltas();
	void run();

private:
	int cont;
	int voltas;

};

#endif /* CARRO_H_ */
