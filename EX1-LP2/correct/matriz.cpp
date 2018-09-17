#include "matriz.h"

Matriz::Matriz(){
	memset(matriz, 0, sizeof(matriz));
	srand(unsigned(time(NULL)));

}

void Matriz::fill (){
	int i = 0, j = 0;	
	for(i = 0; i <= SIZE - 1; i++)
		for(j = 0; j <= SIZE -1; j++)
			matriz[i][j] = (rand() % 10) + 1;	
}

void const Matriz::ImprimeMatriz(){

	int i = 0, j = 0;
	for(i = 0; i <= SIZE - 1; i++){
		std::cout << std::endl;
		for(j = 0; j<= SIZE -1; j++)
			std::cout << matriz[i][j] << " ";
	}
	std::cout << std::endl;
}

void Matriz::MultiplicaMatriz(const Matriz &a, const  Matriz &b, int LStart, int LEnd){
	int i,j ,k;
		
		for(i = LStart ; i <= LEnd; i++)
			for(j = 0; j <= SIZE - 1; j++)
				for(k = 0; k <= SIZE -1; k++)
					matriz[i][j] += a.matriz[i][k] * b.matriz[k][j];
				



}

int Matriz::Tam(int &a){
	a = SIZE;
}

