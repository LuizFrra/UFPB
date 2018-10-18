#include <iostream>
#include "knapsack.h"

using std::cout;

int main(int argc, char const *argv[])
{
    Knapsack *k = new Knapsack();
    int n = 0, op = 0;
    cout << "Digite uma opcao entre 1 - 5\n";
    std::cin >> op;

    switch(op)
    {
        case 1 :
            n = Knapsack::OpenFile(k, "/home/luiz/Desktop/Git/UFPB/APA/Problema da Mochila/instancias/mochila01.txt.txt");
            break;
        case 2 :
            n = Knapsack::OpenFile(k, "/home/luiz/Desktop/Git/UFPB/APA/Problema da Mochila/instancias/mochila02.txt.txt");
            break;
        case 3 :
            n = Knapsack::OpenFile(k, "/home/luiz/Desktop/Git/UFPB/APA/Problema da Mochila/instancias/mochila1000.txt.txt");
            break;
        case 4 :
            n = Knapsack::OpenFile(k, "/home/luiz/Desktop/Git/UFPB/APA/Problema da Mochila/instancias/mochila2500.txt.txt");
            break;
        case 5 :
            n = Knapsack::OpenFile(k, "/home/luiz/Desktop/Git/UFPB/APA/Problema da Mochila/instancias/mochila5000.txt.txt");
            break;
        default :
            cout << "Execute o programa novamente e digite uma opcao valida entre 1 - 5";
    }
    cout << n;
    return 0;
}
