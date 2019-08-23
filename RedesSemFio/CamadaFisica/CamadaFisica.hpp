#ifndef CAMADA_FISICA_H_
#define CAMADA_FISICA_H_
#include "../Roteador/Roteador.hpp"
#include <unistd.h>
#include <algorithm>

class CamadaFisica
{

private:
    /* data */
    
    // Lista de todos os roteadores que participam
    //std::list<Roteador> Roteadores;

    // Lista que contém todos os endereço Mac utilizados para evitar repetição
    std::list<uint8*> EnderecosMacUtilizados;
    
    // Lista que contém todos os Ips Públicos
    std::list<uint8*> EnderecosIpUtilizados;

    // Utilizado para indicar a localização de Cada Roteador
    uint16 **Regiao;

    uint16 X, Y;

    unsigned long RandomNumber(int max, int min);

    unsigned long seed(unsigned long a, unsigned long b, unsigned long c);

    uint8* CriarEnderecoMac();

    uint8* CriarEnderecoIp();

public:
    CamadaFisica(int X, int Y);
    ~CamadaFisica();
    void ImprimirEnderecosMac();
    void InstalarRoteador(uint32 Alcance, uint32 PosicaoX, uint32 PosicaoY);

};

#endif