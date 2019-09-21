#ifndef _COORDENADOR_
#define _COORDENADOR_
#include <unistd.h>
#include <algorithm>
#include "../Hospedeiro/Hospedeiro.hpp"


class Coordenador
{
private:
    std::vector<std::vector<int>> EnderecosMacUtilizados;

    ulong RandomNumber(int max, int min);

    ulong seed(unsigned long a, unsigned long b, unsigned long c);

    std::vector<int> CriarEnderecoMac();
    /* data */
public:
    void ImprimirEnderecosMac();
    Coordenador(/* args */);
    ~Coordenador();
};
#endif