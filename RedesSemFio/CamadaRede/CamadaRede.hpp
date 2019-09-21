#ifndef CAMADA_DE_REDE
#define CAMADA_DE_REDE

#include "../CamadaEnlance/CamadaEnlace.hpp"

class CamadaRede
{
private:
    CamadaEnlace *camadaEnlance;
    /* data */
public:
    CamadaRede(/* args */);
    ~CamadaRede();
    void DefinirCamadaDeBaixo(CamadaEnlace &camadaEnlace);
};

#endif