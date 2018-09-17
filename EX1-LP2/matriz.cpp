#include "matriz.h"

Matriz::Matriz(){
	memset(matriz, 0, sizeof(matriz));
	srand(unsigned(time(NULL)));

}

void Matriz::fill (Matriz &a){
	int i = 0, j = 0;	
	for(i = 0; i <= SIZE - 1; i++)
		for(j = 0; j <= SIZE -1; j++)
			a.matriz[i][j] = (rand() % 10) + 1;	
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

void Matriz::MultiplicaMatriz(const Matriz &a, const  Matriz &b, int LineP){
	int i,j ,k;
		
		if(LineP == (SIZE)){
			i = (SIZE/2);
			LineP = SIZE -1;
		}else
			i = 0;

		for(i ; i <= LineP; i++)
			for(j = 0; j <= SIZE - 1; j++)
				for(k = 0; k <= SIZE -1; k++)
					matriz[i][j] += a.matriz[i][k] * b.matriz[k][j];
				



}

int Matriz::Tam(int &a){
	a = SIZE;
}

