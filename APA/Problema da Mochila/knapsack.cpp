#include "knapsack.h"

using std::cout;
//Peso Valor

Knapsack::Knapsack()
{

}

int Knapsack::OpenFile(Knapsack *knapsackInstance, const char *argv)
{
    knapsackInstance->file.open(argv, std::fstream::in);
    int value = 0, weight = 0;
    

    if(knapsackInstance->file.is_open())
    {
        int counter = 0;
        std::string line;
        getline(knapsackInstance->file, line);
        std::stringstream input(line);
        input >> knapsackInstance->maxObjects;
        input >> knapsackInstance->maxWeight;
        knapsackInstance->values = new int[knapsackInstance->maxObjects];
        knapsackInstance->weights = new int[knapsackInstance->maxObjects];
        
        for(;getline(knapsackInstance->file, line);)
        {
            std::stringstream input(line);

            input >> knapsackInstance->weights[counter];
            input >> knapsackInstance->values[counter];
            ++counter;
        }

        for(size_t i = 0; i < knapsackInstance->maxObjects; i++ )
            cout << knapsackInstance->values[i] << " " << knapsackInstance->weights[i] << " \n";

        
        int n = Knapsack::MaxValue(knapsackInstance->maxObjects ,knapsackInstance->maxWeight, knapsackInstance->weights, knapsackInstance->values);

        return n;
    }
}

int Knapsack::MaxValueCompare(int w1, int w2)
{
    return w1 > w2 ? w1 : w2;
}

int Knapsack::MaxValue(int size, int weight, int *weights, int *values)
{
    int **k = new int *[size + 1];
    
    for(size_t j = 0; j < size + 1; j++)
        k[j] = new int[weight + 1];
    
    for(size_t i = 0; i <= size; i++)
    {
        for(size_t w = 0; w <= weight; w++)
        {
            if(i == 0 || w == 0)
                k[i][w] = 0;
            else if(weights[i - 1] <= w)
                k[i][w] = Knapsack::MaxValueCompare(values[i - 1] + k[i - 1][w - weights[i - 1]], k[i - 1][w]);
            else
                k[i][w] = k[i - 1][w];
        }
    }

    return k[size][weight];
}
