#include "krustal.h"
#include <iostream>
#include <sstream>
#include <string>

using std::cout;

Krustal::Krustal()
{

}

int Krustal::OpenBmp(Krustal *krustalInstance, const char *argv)
{ 
    krustalInstance->file.open(argv, std::fstream::in);
    
    return krustalInstance->file.is_open() == 1 ? 1 : 0;
}

int Krustal::ReadBmp(Krustal *krustalInstance)
{
    return 0;
}

int Krustal::GetInfoContent(Krustal *krustalInstance)
{
    std::vector<int> row;
    int num = 0;
    
    for(std::string line; std::getline(krustalInstance->file, line);)
    {
        std::vector<int> row;
        int num = 0;
        std::stringstream number(line);

        while(number >> num)
        {
            row.push_back(num);
        }

        krustalInstance->numbers.push_back(row);

    }

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