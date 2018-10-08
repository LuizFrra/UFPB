#ifndef PRIM_H_
#define PRIM_H_

#include <fstream>
#include <vector>
#include <sstream>
#include <cstring>
#include <iostream>
#include <limits.h> 

struct Edges
{
    int from;
    int destine;
    int cost;
};


class Prim
{
    private:
        std::fstream file;
        size_t nVertices;
        int *solution;
        int **vertices;
        static int MinVertexKey(Prim *PrimInstance ,int *key, bool *VertexIN);
        
    public:
        Prim();
        static int OpenFile(Prim *PrimInstance, const char *argv);
        static void PrintMatrix(Prim *PrimInstance);
        static void primMST(Prim *PrimInstance);
        static void PrintSolution(Prim *PrimInstance);
        

};

#endif