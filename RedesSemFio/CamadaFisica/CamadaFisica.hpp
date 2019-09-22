#pragma once

#ifndef _CAMADA_FISICA_H_
#define _CAMADA_FISICA_H_

#include <unistd.h>
#include <algorithm>

#include "../CamadaEnlace/CamadaEnlace.hpp"

class CamadaEnlance;

class CamadaFisica
{

private:
    /* data */
    CamadaEnlace *camadaEnlace;
    // Utilizado para indicar a localização de Cada Roteador

public:
    CamadaFisica();
    void DefinirCamadaDeCima(CamadaEnlace *camadaEnlace);
    ~CamadaFisica();
};

#endif