#include "CamadaFisica.hpp"
#include "../CamadaEnlace/CamadaEnlace.hpp"

CamadaFisica::CamadaFisica()
{

}

void CamadaFisica::DefinirCamadaDeCima(CamadaEnlace *camadaEnlace)
{
    this->camadaEnlace = camadaEnlace;
}

CamadaFisica::~CamadaFisica()
{

}