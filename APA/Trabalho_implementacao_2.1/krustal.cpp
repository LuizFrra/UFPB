#include "krustal.h"

using std::cout;

Krustal::Krustal()
{
    NEdges = 0;
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
        ++krustalInstance->NEdges;

        for(size_t i = 0; i < j; i++)
            row.push_back(0);

        while(number >> num)
            row.push_back(num);
        
        ++j;
        krustalInstance->numbers.push_back(row);

    }

    ++krustalInstance->NEdges;
    krustalInstance->numbers.push_back(std::vector<int>(krustalInstance->numbers[0].size()));

    for(size_t i = 0; i < krustalInstance->NEdges; i++)
        for(size_t j = 0; krustalInstance->numbers[i][j] == 0 && j < krustalInstance->numbers[0].size() - 1; j++)
                krustalInstance->numbers[i][j] = krustalInstance->numbers[j][i];

    
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


int Krustal::FNEdges(Krustal *krustalInstance)
{
    return krustalInstance->NEdges;
}

int Krustal::CreateEdges(Krustal *krustalInstance)
{
    const int edges = krustalInstance->NEdges;
    const int widthEdge = (edges * edges) - edges;
    krustalInstance->_edge = new edge[widthEdge];

    for(size_t i = 0, k = 0; i < edges; i++)
    {
        for(size_t j = 0; j < edges; j++)
        {
            if(i != j)
            {
                krustalInstance->_edge[k].weight = krustalInstance->numbers[i][j];
                krustalInstance->_edge[k].destine = j;
                krustalInstance->_edge[k].source = i;
                krustalInstance->_edge[k].set = i;
                k++;
            }

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
        if(_edges[j].weight <= pivo)
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
    int edges = krustalInstance->NEdges;

    QuickSort(krustalInstance->_edge, 0, (edges * edges) - edges - 1);

}

void Krustal::PrintEdges(Krustal *krustalInstance)
{
    int edges = krustalInstance->NEdges;
    int widthEdge =  (edges * edges) - edges - 1;
     
    for(size_t i = 0; i <= widthEdge; i++)
        cout << "\n Edge Source : " << krustalInstance->_edge[i].source  << " Edge Destine : " << krustalInstance->_edge[i].destine << " Price : " << krustalInstance->_edge[i].weight << ".\n";    
    
    cout << "\n";
    
}