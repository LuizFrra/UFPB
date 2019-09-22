#ifndef HOSPEDEIRO_H_
#define HOSPEDEIRO_H_
#include <stdint.h>
#include <list>
#include "../Pacote/Pacote.hpp"

#include "../CamadaEnlace/CamadaEnlace.hpp"
#include "../CamadaFisica/CamadaFisica.hpp"
#include "../CamadaRede/CamadaRede.hpp"

class Hospedeiro
{

private:

    // Endereco da placa de rede *Numero Unico*
    std::vector<int> *EnderecoMac;

    // Variavel que armazenada a Coordenada X do Hospedeiro
    uint CoordenadaX;

    // Variavel que armazenada a Coordenada Y do Hospedeiro
    uint CoordenadaY;

    // Variavel que define o Alcance do Hospedeiro
    uint Alcance;

//    CamadaRede *camadaRede;

//    CamadaEnlace *camadaEnlace;

//    CamadaFisica *camadaFisica;
    

public:
    Hospedeiro(std::vector<int> *EnderecoMac, uint CoordenadaX, uint CoordenadaY);
    ~Hospedeiro();
};

#endif

