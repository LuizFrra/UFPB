#include "CamadaFisica.hpp"
#include "../CamadaEnlace/CamadaEnlace.hpp"

CamadaFisica::CamadaFisica(Hospedeiro *hospedeiro)
{
    this->hospedeiro = hospedeiro;
}

void CamadaFisica::DefinirCamadaDeCima(CamadaEnlace *camadaEnlace)
{
    this->camadaEnlace = camadaEnlace;
}

CamadaFisica::~CamadaFisica()
{

}