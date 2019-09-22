#include "CamadaEnlace.hpp"
#include "../CamadaRede/CamadaRede.hpp"
#include "../CamadaFisica/CamadaFisica.hpp"

CamadaEnlace::CamadaEnlace(/* args */)
{

}
    
void CamadaEnlace::DefinirCamadaDeCima(CamadaRede *camadaRede)
{
    this->camadaRede = camadaRede;
}

void CamadaEnlace::DefinirCamadaDeBaixo(CamadaFisica *camadaFisica)
{
    this->camadaFisica = camadaFisica;
}
    
CamadaEnlace::~CamadaEnlace()
{

}