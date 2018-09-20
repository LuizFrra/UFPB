#ifndef _KRUSTAL_H_
#define _KRUSTAL_H_

#include <vector>
#include <fstream>

class Krustal
{
    private:

        std::fstream file;
        char line[400];
        std::vector<std::vector<int> > numbers;
        std::vector<int> uniqueNum;
        int NVertices;

    public:

        Krustal();
        static int GetInfoContent(Krustal *krustalInstance);
        static int OpenFile(Krustal *krustalInstance, const char *argv);
        static void PrintNumbers(Krustal *krustalInstance);
        static int NVertice(Krustal *krustalInstance);

};


#endif