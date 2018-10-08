#include "dijkstra.h"


Dijkstra::Dijkstra()
{

}


int Dijkstra::OpenFile(Dijkstra *DijkstraInstance, const char *argv)
{

    DijkstraInstance->file.open(argv, std::fstream::in);
    
    if(DijkstraInstance->file.is_open())
    {
        int counter  = 0;
        std::string line; 
        getline(DijkstraInstance->file, line);
        std::stringstream input(line);
        input >> DijkstraInstance->nVertices;

        DijkstraInstance->vertices =  new int*[DijkstraInstance->nVertices];

        for(size_t i = 0; i <= DijkstraInstance->nVertices; i++)
            DijkstraInstance->vertices[i] = new int[DijkstraInstance->nVertices];

        for(;getline(DijkstraInstance->file, line);)
        {
            
            input = std::stringstream(line);
            
            for(size_t i = counter; i < DijkstraInstance->nVertices; i++)
                input >> DijkstraInstance->vertices[counter][i + 1]; 
                   
            
            counter++;
        }

        for(size_t i  = 0; i < DijkstraInstance->nVertices; i++)
            for(size_t j = 0; j < DijkstraInstance->nVertices && DijkstraInstance->vertices[i][j] == 0; j++)
                    DijkstraInstance->vertices[i][j] = DijkstraInstance->vertices[j][i];
            
        
        return 1;
    }

    return 0;
}


void Dijkstra::PrintMatrix(Dijkstra *DijkstraInstance)
{
    for(size_t i  = 0; i < DijkstraInstance->nVertices; i++)
    {
        std::cout << "\n";
        for(size_t j  = 0; j < DijkstraInstance->nVertices; j++)
            std::cout << DijkstraInstance->vertices[i][j] << " ";
             
    }
}

int Dijkstra::MinDistance(Dijkstra *DijkstraInstance, bool *VertexIN)
{
    int min = INT_MAX, min_index;
    for(size_t v = 0; v < DijkstraInstance->nVertices; v++)
         if(VertexIN[v] == false && DijkstraInstance->solution[v] <= min)
             min = DijkstraInstance->solution[v], min_index = v;
    //std::cout << min_index;
    return min_index;
}

void Dijkstra::PrintSolution(Dijkstra *DijkstraInstance)
{
    std::cout << "\nSolution : \n";
    for(size_t i = 1; i < DijkstraInstance->nVertices; i++)
        std::cout << i << " <-> " << DijkstraInstance->solution[i] << "\n"; 
     
}

void Dijkstra::dijSPA(Dijkstra *DijkstraInstance, int source)
{
    DijkstraInstance->solution = new int[DijkstraInstance->nVertices];
    bool mstSet[DijkstraInstance->nVertices] = {false};

    for(size_t i = 0; i < DijkstraInstance->nVertices; i++)
        DijkstraInstance->solution[i] = INT_MAX, mstSet[i] = false;;
    
    DijkstraInstance->solution[source] = 0;

    for(size_t i = 0; i < DijkstraInstance->nVertices - 1; i++)
    {
        int minIndex = MinDistance(DijkstraInstance, mstSet);
        mstSet[minIndex] = true;
        
        for(size_t j = 0; j < DijkstraInstance->nVertices; j++)
        {
             if(!mstSet[j] && DijkstraInstance->vertices[minIndex][j] && DijkstraInstance->solution[minIndex] != INT_MAX && DijkstraInstance->solution[minIndex] + DijkstraInstance->vertices[minIndex][j] < DijkstraInstance->solution[j])
                 DijkstraInstance->solution[j] = DijkstraInstance->solution[minIndex] + DijkstraInstance->vertices[minIndex][j];
        }

    }

}
