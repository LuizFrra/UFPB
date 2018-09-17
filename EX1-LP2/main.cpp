#include "matriz.h"
#include <thread>
#include <vector>

#define Nthreads 2

void multi(Matriz &a, Matriz &b, Matriz &c, int LineP){
	c.MultiplicaMatriz(a, b, LineP);
	//c.ImprimeMatriz();
}

int main(void)
{	
	int i = 0, e = 0, f = 0;
	Matriz a,b,c;
	std::vector < std::thread > threads;
	c.fill(a);
	c.fill(b);
	a.ImprimeMatriz();
	b.ImprimeMatriz();
	c.Tam(e);
	i = (e/Nthreads) - 1;

	for(f = 0; f < Nthreads; f++ ){
			threads.push_back(std::thread(multi, std::ref(a), std::ref(b), std::ref(c),i));
			i = e;
	}
	//c.ImprimeMatriz();

	for(f = 0; i < Nthreads; f++){
		if(threads[f].joinable())threads[f].join();
	}
	c.ImprimeMatriz();
	
	return 0 ;
}