#include "krustal.h"

using std::cout;
using std::cerr;

int main(int argc, char const **argv)
{
    cout << "\nTrying Open File ... ";
    Krustal *k = new Krustal();
    
    if(Krustal::OpenFile(k, argv[1]))
        cout << "\nFile Opened\n";
    else
    {
        throw std::runtime_error("\nFile Not Opened\n");
        return 1;
    }

    cout << "Trying Get Content Of File ... ";
    Krustal::GetInfoContent(k);
    cout << "\nContent Got, Numbers of Vertices :  " << Krustal::FNEdges(k) << "\n"; 
    Krustal::PrintNumbers(k);
    
    cout << "\n";

    Krustal::CreateEdges(k);
    //Krustal::PrintEdges(k);
    Krustal::SortKrustal(k);
    cout << "\nPrint Sorted Edges : \n";
    //Krustal::PrintEdges(k);
    Krustal::GetMinTree(k);
    //Krustal::PrintEdges(k);
    Krustal::PrintMinTree(k);
    cout << "\n";

    return 0;
}
