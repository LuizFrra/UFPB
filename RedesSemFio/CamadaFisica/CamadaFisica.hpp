#pragma once

#ifndef _CAMADA_FISICA_H_
#define _CAMADA_FISICA_H_

#include <unistd.h>
#include <algorithm>

#include "../Pacote/Pacote.hpp"

class CamadaEnlace;
class Hospedeiro;

class CamadaFisica
{

private:
    Hospedeiro *hospedeiro;

    /* data */
    CamadaEnlace *camadaEnlace;
    // Utilizado para indicar a localização de Cada Roteador

public:
    CamadaFisica(Hospedeiro *hospedeiro);
    void DefinirCamadaDeCima(CamadaEnlace *camadaEnlace);
    ~CamadaFisica();
};

#endif