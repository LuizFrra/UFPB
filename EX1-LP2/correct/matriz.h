#ifndef _MATRIZ_H_
#define _MATRIZ_H_

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

#define SIZE 16 //linha e coluna


class Matriz{
	private:
		int matriz[SIZE][SIZE];
	
	public:
	
		Matriz ();
		void fill();	
		void const ImprimeMatriz ();
		void MultiplicaMatriz(const Matriz &a, const Matriz &b, int LStart, int LEnd); //LStart = linha de inicio do processo
		int Tam(int &a);
		//void MultiplicaMatrizThreads(const Matriz &a,const Matriz &b,int LINHA, int COLUNA);
			

};

#endif
