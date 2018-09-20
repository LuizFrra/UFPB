#include "krustal.h"
#include <iostream>

using std::cout;
using std::cerr;

int main(int argc, char const **argv)
{
    cout << "\nTrying Open File ... ";
    Krustal k;
    
    if(Krustal::OpenFile(&k, argv[1]))
        cout << "\nFile Opened\n";
    else
    {
        throw std::runtime_error("\nFile Not Opened\n");
        return 1;
    }

    cout << "Trying Get Content Of File ... ";
    Krustal::GetInfoContent(&k);
    cout << "\nContent Got, Numbers of Vertices :  " << Krustal::NVertice(&k) << "\n"; 
    Krustal::PrintNumbers(&k);

    return 0;
}