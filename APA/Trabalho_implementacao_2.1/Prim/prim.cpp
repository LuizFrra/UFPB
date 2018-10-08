#include "prim.h"


Prim::Prim()
{

}


int Prim::OpenFile(Prim *PrimInstance, const char *argv)
{

    PrimInstance->file.open(argv, std::fstream::in);
    
    if(PrimInstance->file.is_open())
    {
        int counter  = 0;
        std::string line; 
        getline(PrimInstance->file, line);
        std::stringstream input(line);
        input >> PrimInstance->nVertices;

        PrimInstance->vertices =  new int*[PrimInstance->nVertices];

        for(size_t i = 0; i <= PrimInstance->nVertices; i++)
            PrimInstance->vertices[i] = new int[PrimInstance->nVertices];

        for(;getline(PrimInstance->file, line);)
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

int Prim::MinVertexKey(Prim *PrimInstance,int *key, bool *VertexIN)
{
    int min = INT_MAX, min_index;
    for(size_t v = 0; v < PrimInstance->nVertices; v++)
        if(VertexIN[v] == false && key[v] < min)
            min = key[v], min_index = v;
    
    return min_index;
}

void Prim::PrintSolution(Prim *PrimInstance)
{
    std::cout << "\nSolution : \n";
    for(size_t i = 1; i < PrimInstance->nVertices; i++)
    {
        std::cout << PrimInstance->solution[i] << " <-> " << i << " " << PrimInstance->vertices[i][PrimInstance->solution[i]] << " \n"; 
    } 
}

void Prim::primMST(Prim *PrimInstance)
{
    PrimInstance->solution = new int[PrimInstance->nVertices];
    int key[PrimInstance->nVertices];
    bool mstSet[PrimInstance->nVertices] = {false};

    for(int &i : key)
        i = INT_MAX;
    
    key[0] = 0;
    PrimInstance->solution[0] = -1;

    for(size_t i = 0; i < PrimInstance->nVertices - 1; i++)
    {
        int minIndex = MinVertexKey(PrimInstance, key, mstSet);
        std::cout << minIndex << " \n";
        mstSet[minIndex] = true;
        
        for(size_t j = 0; j < PrimInstance->nVertices; j++)
        {
            if(PrimInstance->vertices[i][j] &&  mstSet[j] == false && PrimInstance->vertices[i][j] < key[j])
                PrimInstance->solution[j] = minIndex, key[j] = PrimInstance->vertices[i][j];
        }

    }

}

