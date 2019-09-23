#pragma once
#ifndef _CAMADA_DE_ENLACE_H_
#define _CAMADA_DE_ENLACE_H_

#include "../Pacote/Pacote.hpp"
#include <list>

class CamadaFisica;
class CamadaRede;
class Hospedeiro;

class CamadaEnlace
{

private:
    Hospedeiro *hospedeiro;

    CamadaRede *camadaRede;
    
    CamadaFisica *camadaFisica;

    std::list<Pacote> PacotesParaEnvios;
    /* data */
public:
    CamadaEnlace(Hospedeiro *hospedeiro);
    void DefinirCamadaDeCima(CamadaRede *camadaRede);
    void DefinirCamadaDeBaixo(CamadaFisica *camadaFisica);
    void AdicionarPacoteParaEnvio(Pacote pacote);
    void EnviarPacotesParaCamadaFisica();
    ~CamadaEnlace();
};

#endif