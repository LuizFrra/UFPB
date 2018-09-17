#include "matriz.h"
#include <thread>
#include <vector>

#define Nthreads 4

void multi(Matriz &a, Matriz &b, Matriz &c, int LStart, int LEnd){ 
	c.MultiplicaMatriz(a, b, LStart, LEnd);
	//c.ImprimeMatriz();
}

int main(void)
{	
	int i = 0, e = 0, f = 0, k = 0, j = 0; //e = tamanho da matriz ; k = LStart ; j = LEnd
	Matriz a,b,c;
	std::vector < std::thread > threads; //vetor do tipo thread
	a.fill(); //preenchendo a matriz
	b.fill(); // =
	a.ImprimeMatriz();
	b.ImprimeMatriz();
	c.Tam(e); //salva o tamanho da matriz que estamos trabalhando
	i = (e/Nthreads);
	j = i - 1;

	for(f = 0; f < Nthreads; f++ ){
			threads.push_back(std::thread(multi, std::ref(a), std::ref(b), std::ref(c), k, j));
			k = k + i;
			j = j + i;


	}

	for(i = 0; i < Nthreads; i++){
		threads[i].join();
	}
	c.ImprimeMatriz();
	
	return 0 ;
}
/*


*/