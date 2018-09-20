#include "krustal.h"
#include <iostream>
#include <sstream>
#include <string>

using std::cout;

Krustal::Krustal()
{
    NVertices = 0;
}

int Krustal::OpenFile(Krustal *krustalInstance, const char *argv)
{ 
    krustalInstance->file.open(argv, std::fstream::in);
    
    return krustalInstance->file.is_open() == 1 ? 1 : 0;
}

int Krustal::GetInfoContent(Krustal *krustalInstance)
{
    std::vector<int> row;
    int num = 0;
    int j = 1;
    
    std::string Nv;
    getline(krustalInstance->file, Nv);

    for(std::string line; getline(krustalInstance->file, line);)
    {
        std::vector<int> row;
        int num = 0;
        std::stringstream number(line);
        ++krustalInstance->NVertices;

        for(size_t i = 0; i < j; i++)
            row.push_back(0);

        while(number >> num)
        {  
            //krustalInstance->uniqueNum.push_back(num);
            row.push_back(num);
        }

        ++j;
        krustalInstance->numbers.push_back(row);

    }

    for(size_t i = 0; i < krustalInstance->NVertices; i++)
        for(size_t j = 0; krustalInstance->numbers[i][j] == 0; j++)
                krustalInstance->numbers[i][j] = krustalInstance->numbers[j][i];

    return 0;
}

void Krustal::PrintNumbers(Krustal *krustalInstance)
{
    for(auto k : krustalInstance->numbers){
        cout << "\n";
        for(auto c : k)        
            cout << c << " ";
    }
}