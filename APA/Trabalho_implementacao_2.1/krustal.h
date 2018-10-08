#ifndef _KRUSTAL_H_
#define _KRUSTAL_H_

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


struct edge
{
    int source;
    int destine;
    int weight;
    int set;
};


class Krustal
{
    private:

        struct edge *_edge;
        std::fstream file;
        std::vector<std::vector<int> > numbers;
        std::vector<edge> MinTree;
        int NEdges;
        int *NConj;
        size_t WidthArray;
        static int QuickSort(edge *_edges, int start, int end);
        static int Partition(edge *_edges, int start, int end); 
        static void Union(edge edges, edge _edge, Krustal *krustalInstance);

    public:

        Krustal();
        static int GetInfoContent(Krustal *krustalInstance);
        static int OpenFile(Krustal *krustalInstance, const char *argv);
        static void PrintNumbers(Krustal *krustalInstance);
        static int FNEdges(Krustal *krustalInstance);
        static int CreateEdges(Krustal *krustalInstance);
        static void PrintEdges(Krustal *krustalInstance);
        static void SortKrustal(Krustal *krustalInstance);
        static void GetMinTree(Krustal *krustalInstance);
        static void PrintMinTree(Krustal *krustalInstance);
};



#endif