#pragma once

#ifndef _CAMADA_DE_REDE_H_
#define _CAMADA_DE_REDE_H_

#include "../CamadaEnlace/CamadaEnlace.hpp"

class CamadaEnlance;

class CamadaRede
{
    
private:
    CamadaEnlace *camadaEnlace;
    /* data */
public:
    CamadaRede(/* args */);
    void DefinirCamadaDeBaixo(CamadaEnlace *camadaEnlace);
    ~CamadaRede();
};

#endif