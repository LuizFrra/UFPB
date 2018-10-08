#include "prim.h"

int main(int argc, char const *argv[])
{
    Prim *Object = new Prim();

    std::cout << "1 - dij10 \n2 - dij20\n3 - dij40\n4 - dij50\n";

    switch(atoi(argv[1]))
    {
        case 1:
            Prim::OpenFile(Object, "/home/luiz/Desktop/Git/UFPB/APA/Trabalho_implementacao_2.1/Prim/instancias de teste/dij10.txt");
            break;
        case 2:
            Prim::OpenFile(Object, "/home/luiz/Desktop/Git/UFPB/APA/Trabalho_implementacao_2.1/Prim/instancias de teste/dij20.txt");
            break;
        case 3:
            Prim::OpenFile(Object, "/home/luiz/Desktop/Git/UFPB/APA/Trabalho_implementacao_2.1/Prim/instancias de teste/dij40.txt");
            break;
        case 4:
            Prim::OpenFile(Object, "/home/luiz/Desktop/Git/UFPB/APA/Trabalho_implementacao_2.1/Prim/instancias de teste/dij40.txt");
            break;
        default:
            std::cout << "Wrong Option\n";
    }   

    Prim::PrintMatrix(Object);
    Prim::primMST(Object);
    Prim::PrintSolution(Object);
    
    return 0;
}
