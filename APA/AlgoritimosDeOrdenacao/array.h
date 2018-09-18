#ifndef ARRAY_H
#define ARRAY_H

#include <cstdlib>
#include <iostream>

using std::cout;
using std::endl;

namespace array{

    void fill(const int tam, int *p)
    {
        srand(time(NULL));
        for(int i = 0; i < tam; i++)
            p[i] = (rand() % 100) + 1;

    }
    //-------------------------
    void print(const int tam, const char *text, const int *p)
    {
        std::ios::sync_with_stdio(false);
        std::cin.tie(0);
        cout << text;
        for(int i = 0; i < tam; i++)
            i == (tam - 1) ? cout << p[i] << endl : cout << p[i] << ",";
    }
    //----------------------
    void selectSort(const int tam, int *p)
    {
        for(int i = 0; i < tam - 1; i++) 
        {
            int min = i;
            for(int j = i + 1; j < tam; j++)
                if( p[min] > p[j] )
                    min = j;

            int vTemp = p[i];
            p[i] = p[min];
            p[min] = vTemp;            
            
        }
    }
    // ------------------------
    void insertSort (const int tam, int *p)
    {
        int vTemp;

        for(int i = 1; i <  tam ; i++){
            
            while(p[i -1] > p[i] && i > 0  ){
                vTemp = p[i];
                p[i] = p[i - 1];
                p[i - 1] = vTemp;

                i--;
            }
            
        }

    }
    //--------------------------

    //2º Conquistar
    static int Merge(int *p, const int start, const int middle, const int end)
    {
        int *arrayT, tam, indexArrayOne = start, indexArrayTwo = middle + 1;
        tam = end - start + 1; // + 1 == array[10] -> 9 elementos -> 9 + 1 posições 
        arrayT = new int[tam * sizeof(int)];// Alocando quantidade de bytes necessaria para copiar o array

        for(int i = 0; i < tam; i++)
        {
            if((indexArrayOne <= middle) && (indexArrayTwo < end + 1)){ // um subvetor vetor nao acessar a area do outro
                if(p[indexArrayOne] < p[indexArrayTwo])
                    arrayT[i] = p[indexArrayOne++];
                else
                    arrayT[i] = p[indexArrayTwo++]; 
            }

            else
            {
                if(indexArrayOne > middle)
                    arrayT[i] = p[indexArrayTwo++];
                else
                    arrayT[i] = p[indexArrayOne++];
            }

            
        }
        
        for(int i = 0, k = start;  i < tam; i++, k++)
            p[k] = arrayT[i];
        
        delete [] arrayT;
        return 1;
    }

    //1º Dividir Para Conquitar
    // ((end + start) / 2 ) == meio do array, array 0 <-> 10 = 0 + 9 /2 = 4,5 = 4  => 0 1 2 3 4 =  5 elementos
    void MergeSort(int *p, const int start, const int end)
    {   
        
        if(start < end)
        {
            MergeSort(p, start, int((end + start) / 2 ));
            MergeSort(p, int((end + start) / 2 ) + 1, end);
            Merge(p, start, int((end + start) / 2 ), end);
            
        }

        
    }
    //-------------------------------------------
    static int partition(int *p, const int start, const int end)
    {
        int pivo = p[end];
        int i = start - 1;

        for(int j = start; j < end; j++)
        {
            if(p[j] <= pivo)
            {
                i++;
                int hold = p[i];
                p[i] = p[j];
                p[j] = hold;

            }

        }
        ++i;
        int hold = p[end];
        p[end] = p[i];
        p[i] = hold;

        return i;
    }

    int quicksort(int *p, const int start, const int end)
    {
        if(start < end)
        {
            int pivo = partition(p, start, end);
            quicksort(p, start, pivo - 1);
            quicksort(p, pivo + 1, end);
        }
        
        return 1;
    }

    static const int GetMaxEl(const int tam, const int *array)
    {
        int max = array[0];
        
        for(int i = 1; i < tam; i++)
            if(array[i] > max)
                max = array[i];
    
        return max;
    }

    void countinSort(const int tam, const int *array, int *orderedArray)
    {
        int max = GetMaxEl(tam, array);
        
        int *freqEl = new int[max + 1]; // Ja começa com todos os valores == 0
        //Contabilizando frequencia
        for(int i = 0; i < tam; i++)
            freqEl[array[i]]++;
        //Propagando a frequencia
        for(int i = 1; i < max + 1; i++)
            freqEl[i] += freqEl[i - 1];
        
        for(int j = tam - 1 ; j >= 0; j--)
        {
            orderedArray[freqEl[array[j]] - 1] = array[j];
            freqEl[array[j]]--;
        }
        
        delete [] freqEl ;

    }

    void MaxHeapify(const int tam, int *array, const int index)
    {
        /*Dado elemento i :
          Pai de i: (i - 1)/2
          filho esquerdo : 2i + 1
          filho direito : 2i + 2
          comprimento : tam
          tamanho_heap : numero de elemtos no heap : tam - indicepai
        */
        int father = ((index - 1)/2) ;
        //(index -1)/2 < 0 ? father = (((index - 1)/2)* 1) : father = (index - 1)/2 ;
        int leftChild = (2 * index) + 1;
        int rightChild = (2 * index) + 2;
        int tam_heap = tam - father - 1;
        int max = index;

        if( leftChild <= tam_heap && array[leftChild] > array[max])
            max = leftChild;
        if( rightChild <= tam_heap && array[rightChild] > array[max])
            max = rightChild;
        if( max != index)
        {
            int aux = array[max];
            array[max] = array[index];
            array[index] = aux;
            MaxHeapify(tam_heap ,array, max);
        }
    }

    void buildMaxHeap(const int tam, int *array)
    {
        int tam_heap = tam - 1;

        for(int i = (tam / 2) - 1 ; i >= 0; i--)
            MaxHeapify(tam, array, i);

    }

    void HeapSort(const int tam, int *array)
    {
        buildMaxHeap(tam, array);

        for(int i = tam - 1; i >= 0; i--)
        {
            int aux = array[0];
            array[0] = array[i];
            array[i] = aux;
            MaxHeapify(i, array, 0);
        }
    }

}

#endif
