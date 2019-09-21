#ifndef CAMADA_DE_ENLACE
#define CAMADA_DE_ENLACE

#include "../CamadaRede/CamadaRede.hpp"
#include "../CamadaEnlance/CamadaEnlace.hpp"

class CamadaEnlace
{
private:
    CamadaFisica *camadaFisica;
    CamadaRede *CamadaRede;
    /* data */
public:
    CamadaEnlace(/* args */);
    ~CamadaEnlace();
    
    void DefinirCamadaDeCima(CamadaRede &camadaRede);
    void DefinirCamadaDeBaixo(CamadaFisica &camadaFisica);
};

#endif