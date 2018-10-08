#ifndef DIJKSTRA_H_
#define DIJKSTRA_H_

#include <fstream>
#include <vector>
#include <sstream>
#include <cstring>
#include <iostream>
#include <limits.h> 


class Dijkstra
{
    private:
        std::fstream file;
        size_t nVertices;
        int *solution;
        int **vertices;
        static int MinDistance(Dijkstra *DijkstraInstance , bool *VertexIN);
        
    public:
        Dijkstra();
        static int OpenFile(Dijkstra *DijkstraInstance, const char *argv);
        static void PrintMatrix(Dijkstra *DjkistraInstance);
        static void dijSPA(Dijkstra *DijkstraInstance, int source);
        static void PrintSolution(Dijkstra *DijkstraInstance);
        

};

#endif