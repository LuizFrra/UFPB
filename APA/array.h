#ifndef ARRAY_H
#define ARRAY_H

#include <cstdlib>

using std::cout;
using std::endl;

namespace array{

    void fill(int tam, int *p)
    {
        srand(time(NULL));
        for(int i = 0; i < tam; i++)
            p[i] = (rand() % 10) + 1;

    }
    //-------------------------
    void print(int tam, const char *text, int *p)
    {
        cout << text;
        for(int i = 0; i < tam; i++)
            i == (tam - 1) ? cout << p[i] << endl : cout << p[i] << ",";
    }
    //----------------------
    void selectSort(int tam, int *p)
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
    void insertSort (int tam, int *p)
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


}

#endif
