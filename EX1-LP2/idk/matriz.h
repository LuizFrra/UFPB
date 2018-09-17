#ifndef _MATRIZ_H_
#define _MATRIZ_H_

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

#define SIZE 4


class Matriz{
	private:
		int matriz[SIZE][SIZE];
	
	public:
	
		Matriz ();
		void fill(Matriz &a);	
		void const ImprimeMatriz ();
		void MultiplicaMatriz(Matriz &a, Matriz &b, int LineP);
		int Tam(int &a);
		//void MultiplicaMatrizThreads(const Matriz &a,const Matriz &b,int LINHA, int COLUNA);
			

};

#endif
