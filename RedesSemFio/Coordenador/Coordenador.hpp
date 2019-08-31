#ifndef _COORDENADOR_
#define _COORDENADOR_
#include <unistd.h>
#include <algorithm>
#include "../Roteador/Roteador.hpp"

class Coordenador
{
private:
    std::list<uint8*> EnderecosMacUtilizados;
    
    // Lista que contém todos os Ips Públicos
    std::list<uint8*> EnderecosIpUtilizados;

    std::list<Roteador*> Roteadores;

    ulong RandomNumber(int max, int min);

    ulong seed(unsigned long a, unsigned long b, unsigned long c);

    uint8* CriarEnderecoMac();

    uint8* CriarEnderecoIp();
    /* data */
public:
    Coordenador(/* args */);
    ~Coordenador();
};
#endif