#ifndef _TSP_H_
#define _TSP_H_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <unistd.h> 
#include <cstdlib>


struct vertex
{
    int destine;
    int weight;
};


struct edges
{
    vertex *vertices;
    int cost = 0;
};

int compare (const void * a, const void * b);

class TSP{
    private:
    
    edges *matrix;
    int nCitys;
    std::fstream tspInstance;
    edges *solution;
    int swapi, swapj;

    public:

    TSP();
    TSP(const char *argv);

    bool OpenFile(const char *argv);
    bool ReadFile();
    void PrintMatrix();
    edges NearestNeightbour();
    unsigned long GetRandomNumber(int min, int max);
    unsigned long seed(unsigned long a, unsigned long b, unsigned long c);
    int swap();
    int GetCost(vertex *vertices);

};


#endif