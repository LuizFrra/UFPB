#include "krustal.h"

using std::cout;

Krustal::Krustal()
{
    NVertices = 0;
}

int Krustal::OpenFile(Krustal *krustalInstance, const char *argv)
{ 
    krustalInstance->file.open(argv, std::fstream::in);
    
    return krustalInstance->file.is_open() == 1 ? 1 : 0;
}

int Krustal::GetInfoContent(Krustal *krustalInstance)
{
    std::vector<int> row;
    int num = 0;
    int j = 1;
    
    std::string Nv;
    getline(krustalInstance->file, Nv);

    for(std::string line; getline(krustalInstance->file, line);)
    {
        std::vector<int> row;
        int num = 0;
        std::stringstream number(line);
        ++krustalInstance->NVertices;

        for(size_t i = 0; i < j; i++)
            row.push_back(0);

        while(number >> num)
            row.push_back(num);
        
        ++j;
        krustalInstance->numbers.push_back(row);

    }

    ++krustalInstance->NVertices;
    krustalInstance->numbers.push_back(std::vector<int>(krustalInstance->numbers[0].size()));

    for(size_t i = 0; i < krustalInstance->NVertices; i++)
        for(size_t j = 0; krustalInstance->numbers[i][j] == 0 && j < krustalInstance->numbers[0].size() - 1; j++)
                krustalInstance->numbers[i][j] = krustalInstance->numbers[j][i];

    krustalInstance->NEdges = krustalInstance->NVertices - 1;
    
    return 0;
}

void Krustal::PrintNumbers(Krustal *krustalInstance)
{
    for(auto k : krustalInstance->numbers){
        cout << "\n";
        for(auto c : k)        
            cout << c << " ";
    }
}


int Krustal::NVertice(Krustal *krustalInstance)
{
    return krustalInstance->NVertices;
}

int Krustal::CreateEdges(Krustal *krustalInstance)
{
    const int edges = krustalInstance->NVertices;
    krustalInstance->NConj = new int[edges];
    krustalInstance->_edge = new edge *[edges];
    
    for(size_t i = 0; i < edges; i++)
    {
        krustalInstance->_edge[i] = new edge[edges];
        krustalInstance->NConj[i] = i;
    }

    for(size_t i = 0; i < edges; i++)
    {
        for(size_t j = 0; j < edges; j++)
        {
            krustalInstance->_edge[i][j].weight = krustalInstance->numbers[i][j];
            krustalInstance->_edge[i][j].destine = j;
            krustalInstance->_edge[i][j].source = i;
        }
    }

    return 0;
}

int Krustal::QuickSort(edge *_edges, int start, int end)
{
    if(start < end)
    {
        int pivo = Partition(_edges, start, end);
        QuickSort(_edges, start, pivo - 1);
        QuickSort(_edges, pivo + 1, end);
    }
        
        return 1;
}
int Krustal::Partition(edge *_edges, int start, int end)
{
    int pivo = _edges[end].weight;
    int i = start - 1;

    for(int j = start; j < end; j++)
    {
        if(_edges[j].weight <= pivo) //p[j]
        {
            i++;
            edge hold = _edges[i];
            _edges[i] = _edges[j];
            _edges[j] = hold;
        }

    }
    
    ++i;
    edge hold = _edges[end];
    _edges[end] = _edges[i];
    _edges[i] = hold;

    return i;
}

void Krustal::SortKrustal(Krustal *krustalInstance)
{
    int edges = krustalInstance->NVertices;

    for(size_t i = 0; i < edges; i++)
        QuickSort(krustalInstance->_edge[i], 0, edges - 1);

}

void Krustal::PrintEdges(Krustal *krustalInstance)
{
    int NEdges = krustalInstance->NEdges;

    for(size_t i = 0; i <= NEdges; i++)
    {
        for(size_t j = 0; j <= NEdges; j++)
        {
            cout << "\n Edge Source : " << krustalInstance->_edge[i][j].source  << " Edge Destine : " << krustalInstance->_edge[i][j].destine << " Price : " << krustalInstance->_edge[i][j].weight << ".\n";
        }
        cout << "\n";
    }

}