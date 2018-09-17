/*
 * Passageiro.h
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#ifndef PASSAGEIRO_H_
#define PASSAGEIRO_H_

class Carro;
class Parque;

class Passageiro {
public:
	static int estagios[8];
	static int ultimo[8];
	
	Passageiro(int id, Carro *c);
	virtual ~Passageiro();
	void entraNoCarro();
	void esperaVoltaAcabar();
	void saiDoCarro();
	void passeiaPeloParque();
	bool parqueFechado();

	void run();
private:
	static int g;
	int id;
	Carro *carro;
};

#endif /* PASSAGEIRO_H_ */
