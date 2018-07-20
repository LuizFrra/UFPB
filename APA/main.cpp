#include <iostream>
#include "array.h"
#define TAM 10

using std::cout;
using std::endl;

int main(int argc, char const *argv[])
{
    int array[TAM]; //{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << "Selection Sort :" << endl;
    array::fill(TAM, array); // preeencho o array com numeros aleatorios
    array::print(TAM, "My Array : " , array);    // printo o array desordenado
    array::selectSort(TAM, array); // ordeno o array com o metodo select sort
    array::print(TAM, "My Ordered Array : " ,array); // printo o array ordenado

    cout << endl << "Insert Sort" << endl;
    array::fill(TAM, array); // --
    array::print(TAM, "My Array : ", array); // --
    array::insertSort(TAM, array); // ordeno o array com o metodo insert sort
    array::print(TAM, "My Ordered Array : ", array); // --

    return 0;
}
