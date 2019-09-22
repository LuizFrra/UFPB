#pragma once
#ifndef _CAMADA_DE_ENLACE_H_
#define _CAMADA_DE_ENLACE_H_

class CamadaFisica;
class CamadaRede;

class CamadaEnlace
{

private:
    CamadaRede *camadaRede;
    CamadaFisica *camadaFisica;
    /* data */
public:
    CamadaEnlace(/* args */);
    void DefinirCamadaDeCima(CamadaRede *camadaRede);
    void DefinirCamadaDeBaixo(CamadaFisica *camadaFisica);
    ~CamadaEnlace();
};

#endif