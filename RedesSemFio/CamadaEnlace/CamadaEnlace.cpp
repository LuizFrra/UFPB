#include "CamadaEnlace.hpp"
#include "../CamadaRede/CamadaRede.hpp"
#include "../CamadaFisica/CamadaFisica.hpp"


CamadaEnlace::CamadaEnlace(Hospedeiro *hospedeiro)
{
    this->hospedeiro = hospedeiro;
}

void CamadaEnlace::AdicionarPacoteParaEnvio(Pacote pacote)
{
    PacotesParaEnvios.push_back(pacote);
    hospedeiro->EntrarNaFilaCoordenador();
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