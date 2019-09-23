#pragma once
#ifndef _CAMADA_DE_ENLACE_H_
#define _CAMADA_DE_ENLACE_H_

#include "../Pacote/Pacote.hpp"

class CamadaFisica;
class CamadaRede;
class Hospedeiro;

class CamadaEnlace
{

private:
    Hospedeiro *hospedeiro;

    CamadaRede *camadaRede;
    
    CamadaFisica *camadaFisica;
    /* data */
public:
    CamadaEnlace(Hospedeiro *hospedeiro);
    void DefinirCamadaDeCima(CamadaRede *camadaRede);
    void DefinirCamadaDeBaixo(CamadaFisica *camadaFisica);
    ~CamadaEnlace();
};

#endif