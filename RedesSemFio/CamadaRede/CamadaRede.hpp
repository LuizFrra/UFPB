#pragma once

#ifndef _CAMADA_DE_REDE_H_
#define _CAMADA_DE_REDE_H_

#include "../Pacote/Pacote.hpp"

#include <vector>

class CamadaEnlace;
class Hospedeiro;

class CamadaRede
{
    
private:
    // Hospedeiro a qual a camada pertence
    Hospedeiro *hospedeiro;

    // Camada a qual Rede presta serviço
    CamadaEnlace *camadaEnlace;

    // Contador do Pacote
    uint PacoteID;

    // Fila de Aguardando ACK dos nós Vizinho = MACK, Primeiro argumento é o contador do Pacote e o Segundo Quem enviou o Pacote
    std::vector<std::pair<uint, Hospedeiro>> MACKS;
    
    /* data */
public:
    CamadaRede(Hospedeiro *hospedeiro);
    void DefinirCamadaDeBaixo(CamadaEnlace *camadaEnlace);
    ~CamadaRede();
};

#endif