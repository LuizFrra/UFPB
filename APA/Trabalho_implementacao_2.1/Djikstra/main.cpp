#include "dijkstra.h"

int main(int argc, char const *argv[])
{
    int op = 0;
    Dijkstra *Object = new Dijkstra();

    std::cout << "1 - dij10 \n2 - dij20\n3 - dij40\n4 - dij50\n";
    std::cin >> op;
    switch(op)
    {
        case 1:
            Dijkstra::OpenFile(Object, "/home/luiz/Desktop/Git/UFPB/APA/Trabalho_implementacao_2.1/Prim/instancias de teste/dij10.txt");
            break;
        case 2:
            Dijkstra::OpenFile(Object, "/home/luiz/Desktop/Git/UFPB/APA/Trabalho_implementacao_2.1/Prim/instancias de teste/dij20.txt");
            break;
        case 3:
            Dijkstra::OpenFile(Object, "/home/luiz/Desktop/Git/UFPB/APA/Trabalho_implementacao_2.1/Prim/instancias de teste/dij40.txt");
            break;
        case 4:
            Dijkstra::OpenFile(Object, "/home/luiz/Desktop/Git/UFPB/APA/Trabalho_implementacao_2.1/Prim/instancias de teste/dij40.txt");
            break;
        default:
            std::cout << "Wrong Option\n";
    }   

    Dijkstra::PrintMatrix(Object);
    Dijkstra::dijSPA(Object, 0);
    Dijkstra::PrintSolution(Object);
    
    return 0;
}