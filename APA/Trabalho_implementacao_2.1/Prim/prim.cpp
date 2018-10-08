#include "prim.h"


Prim::Prim()
{

}


int Prim::OpenFile(Prim *PrimInstance, const char *argv)
{

    PrimInstance->file.open(argv, std::fstream::in);
    
    if(PrimInstance->file.is_open())
    {
        int num = 0, counter  = 0;
        std::string line; 
        getline(PrimInstance->file, line);
        std::stringstream input(line);
        input >> PrimInstance->nVertices;

        PrimInstance->vertices =  new int*[PrimInstance->nVertices];

        for(size_t i = 0; i <= PrimInstance->nVertices; i++)
            PrimInstance->vertices[i] = new int[PrimInstance->nVertices];

        for(; getline(PrimInstance->file, line);)
        {
            input = std::stringstream(line);
            
            for(size_t i = counter; i < PrimInstance->nVertices; i++)
                input >> PrimInstance->vertices[counter][i + 1];         
            
            counter++;
        }

        for(size_t i  = 0; i < PrimInstance->nVertices; i++)
            for(size_t j = 0; j < PrimInstance->nVertices && PrimInstance->vertices[i][j] == 0; j++)
                PrimInstance->vertices[i][j] = PrimInstance->vertices[j][i];

        return 1;
    }

    return 0;
}


void Prim::PrintMatrix(Prim *PrimInstance)
{
    for(size_t i  = 0; i < PrimInstance->nVertices; i++)
    {
        std::cout << "\n";
        for(size_t j  = 0; j < PrimInstance->nVertices; j++)
            std::cout << PrimInstance->vertices[i][j] << " ";
    }
}