#ifndef _KNAPSACK_H_
#define _KNAPSACK_H_

#include <vector>
#include <fstream>
#include <cstring>
#include <sstream>
#include <iostream>

class Knapsack
{
    private:
        int *weights;
        int *values;
        int maxWeight;
        int maxObjects;
        std::fstream file;
        static int MaxValue(int size, int weight, int *weights, int *values);
        static int MaxValueCompare(int w1, int w2);

    public:
        Knapsack();
        static int OpenFile(Knapsack *knapsackInstance, const char *argv);
};


#endif