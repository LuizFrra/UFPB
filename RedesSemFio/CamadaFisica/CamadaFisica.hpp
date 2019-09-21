#ifndef CAMADA_FISICA_H_
#define CAMADA_FISICA_H_
#include <unistd.h>
#include <algorithm>

#include "../CamadaEnlance/CamadaEnlace.hpp"

class CamadaFisica
{

private:
    /* data */
    CamadaEnlace *camadaEnlance;
    // Utilizado para indicar a localização de Cada Roteador

public:
    CamadaFisica();
    ~CamadaFisica();

    void DefinirCamadaDeCima(CamadaEnlace &CamadaEnlace);
};

#endif