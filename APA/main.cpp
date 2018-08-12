#include <iostream>
#include "array.h"

#define TAM 10

using std::cout;
using std::endl;

int main(int argc, char const *argv[])
{
    int array[TAM];// {2, 4, 8, 9, 3, 15, 21, 29, 12, 10};
    std::cout << "Selection Sort :" << "\n";
    array::fill(TAM, array); // preeencho o array com numeros aleatorios
    array::print(TAM, "My Array : " , array);    // printo o array desordenado
    array::selectSort(TAM, array); // ordeno o array com o metodo select sort
    array::print(TAM, "My Ordered Array : " ,array); // printo o array ordenado

    std::cout << "\nInsertSort" << "\n";
    array::fill(TAM, array); // --
    array::print(TAM, "My Array : ", array); // --
    array::insertSort(TAM, array); // ordeno o array com o metodo insert sort
    array::print(TAM, "My Ordered Array : ", array); // --

    cout << "\nMergeSort" << "\n";
    array::fill(TAM, array);
    array::print(TAM, "My Array : ", array);
    array::MergeSort(array, 0, TAM - 1);
    array::print(TAM, "My Ordered Array : ", array);

    cout << "\nQuickSort" << "\n";
    array::fill(TAM, array);
    array::print(TAM, "My Array : ", array);
    array::quicksort(array, 0, TAM - 1);
    array::print(TAM, "My Ordered Array : ", array);

    return 0;
}
