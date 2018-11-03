#include "tsp.h"

TSP::TSP()
{
    
}


TSP::TSP(const char *argv)
{
    std::cout << "Tentando abrir o arquivo : " << argv << " ...\n";
    if(!OpenFile(argv))
        exit(1);

    ReadFile();
    std::cout << "Matriz montanda : \n";
    //PrintMatrix();
    
    std::cout << "Começando Execução do Algoritimo do Vizinho Mais Próximo ... \n";
    edges solution = NearestNeightbour();
    std::cout << "Solução encontrada : ";
    for(size_t i = 0; i <= nCitys; i++)
        std::cout << solution.vertices[i].destine << " ";
    std::cout << "\nCalculando Custo ... \n" << solution.cost << "\n"; 
    
}


bool TSP::OpenFile(const char *argv)
{
    tspInstance.open(argv, std::fstream::in);

    if(tspInstance.is_open())
    {
        std::cout << "O arquivo foi aberto com sucesso ... \n";
        return true;
    }
    std::cout << "Ocorreu algum problema durante a abertura do arquivo, verifique o caminho ... \n";
    return false;
}

bool TSP::ReadFile()
{
    std::cout << "Lendo o arquivo ... \n";
    std::cout << "Obtendo a quantidade de cidades ... \n";
    
    std::string lines;

    std::getline(tspInstance, lines);
    std::stringstream input(lines);
    input >> nCitys;
    std::cout << "Alocando espaço para as " << nCitys << " x " << nCitys<< " distâncias entre cidades ... \n"; 

    matrix = new edges[nCitys];

    for(size_t i = 0; i <= nCitys; i++)
        matrix[i].vertices = new vertex[nCitys];

    std::cout << "Espaço alocado com Sucesso ... " << std::endl;
    std::cout << "Montando a matriz de adjacência ... \n";

    for(size_t i = 0; getline(tspInstance, lines); i++)
    {
        std::stringstream data(lines);
        int distance = 0;
        for(size_t j = 0; data >> distance; j++)
        { 
            if(i != j)    
                matrix[i].vertices[j].weight = distance;
            else
                matrix[i].vertices[j].weight = INT32_MAX;
            
            matrix[i].vertices[j].destine = j;
        } 
    }

    // return false;
}

void TSP::PrintMatrix()
{
    for(size_t i = 0; i < nCitys; i++)
    {
        for(size_t j = 0; j < nCitys; j++)
        {
                std::cout << "Distancia do vertice " << i << " Para o " << matrix[i].vertices[j].destine << " Tem custo " << matrix[i].vertices[j].weight << "\n";
         }
        std::cout << "\n";
    }

}

edges TSP::NearestNeightbour()
{
    solution = new edges[1];
    solution[0].vertices = new vertex[nCitys + 1];
    bool *solutionInclude = new bool[nCitys];
    for(size_t i = 0; i < nCitys; i++)
        solutionInclude[i] = false;
    
    //Passo 1 :  Começar com um vértice Aleatorio
    std::cout << "Selecionando um vértice aleatoriamente ... \n";
    int currentVertix =  GetRandomNumber(0, nCitys);
    std::cout << "Vertice Inicial : " << currentVertix << " ...\n";

    //Passo 2: Incluir este vértice no Incio e no Final da Solução
    solution[0].vertices[0].destine = currentVertix;
    solution[0].vertices[nCitys].destine = currentVertix;
    solutionInclude[currentVertix] = true;    
    //Passo 3: Encontrar o vértice mais próximo do vértice atual
    //Passo 3.1 : Ordenar os Vértices
    for(size_t i = 0; i < nCitys; i++)
        qsort(matrix[i].vertices, nCitys, sizeof(vertex), compare);

    //Passo 3.2 : Realizar a busca local
    for(size_t i = 0; i < nCitys - 1; i++)
    {
        int minValue = INT32_MAX;
        int minVertex = minValue;
        for(size_t j = 0; j < nCitys; j++)
        {
            if((matrix[currentVertix].vertices[j].weight < minValue) && !solutionInclude[matrix[currentVertix].vertices[j].destine])
            {
                minVertex = matrix[currentVertix].vertices[j].destine;
                minValue = matrix[currentVertix].vertices[j].weight;
            }
        }
        //std::cout << minVertex << "\n";
        solutionInclude[minVertex] = true;
        currentVertix = minVertex;
        solution[0].vertices[i + 1].destine = minVertex;
        solution[0].vertices[i + 1].weight = minValue;
        solution[0].cost += minValue;
    }
    for(size_t i = 0; i < nCitys; i++)
        if(matrix[solution[0].vertices[nCitys - 1].destine].vertices[i].destine == solution[0].vertices[nCitys].destine)
            solution[0].cost += matrix[solution[0].vertices[nCitys - 1].destine].vertices[i].weight;
    
    return solution[0];
}

unsigned long TSP::GetRandomNumber(int min, int max)
{
    return ((seed(clock(), time(NULL), getpid())) % (max - min)) + min;
}

unsigned long TSP::seed(unsigned long a, unsigned long b, unsigned long c)
{
    a=a-b;  a=a-c;  a=a^(c >> 13);
    b=b-c;  b=b-a;  b=b^(a << 8);
    c=c-a;  c=c-b;  c=c^(b >> 13);
    a=a-b;  a=a-c;  a=a^(c >> 12);
    b=b-c;  b=b-a;  b=b^(a << 16);
    c=c-a;  c=c-b;  c=c^(b >> 5);
    a=a-b;  a=a-c;  a=a^(c >> 3);
    b=b-c;  b=b-a;  b=b^(a << 10);
    c=c-a;  c=c-b;  c=c^(b >> 15);
    return c;
}

int compare (const void * a, const void * b)
{
    vertex *orderA = (vertex *) a;
    vertex *orderB = (vertex *) b;

    return (orderA->weight - orderB->weight);
}
