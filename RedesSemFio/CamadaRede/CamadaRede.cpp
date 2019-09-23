#include "CamadaRede.hpp"
#include "../CamadaEnlace/CamadaEnlace.hpp"
#include "../Hospedeiro/Hospedeiro.hpp"

CamadaRede::CamadaRede(Hospedeiro *hospedeiro)
{
    this->hospedeiro = hospedeiro;
}
    
void CamadaRede::DefinirCamadaDeBaixo(CamadaEnlace *camadaEnlace)
{
    this->camadaEnlace = camadaEnlace;
}


CamadaRede::~CamadaRede()
{

}