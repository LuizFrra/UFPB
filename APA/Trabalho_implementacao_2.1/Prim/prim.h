#ifndef PRIM_H_
#define PRIM_H_

#include <fstream>
#include <vector>
#include <sstream>
#include <cstring>
#include <iostream>

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
        //std::vector< std::vector<int> > vertices;
        size_t nVertices;
        int **vertices;
    public:
        Prim();
        static int OpenFile(Prim *PrimInstance, const char *argv);
        static void PrintMatrix(Prim *PrimInstance);
        

};

#endif