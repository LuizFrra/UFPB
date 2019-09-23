#include "CamadaFisica.hpp"
#include "../CamadaEnlace/CamadaEnlace.hpp"
#include "../Hospedeiro/Hospedeiro.hpp"
#include <iostream>
#include <iomanip>

CamadaFisica::CamadaFisica(Hospedeiro *hospedeiro)
{
    this->hospedeiro = hospedeiro;
}

void CamadaFisica::DefinirCamadaDeCima(CamadaEnlace *camadaEnlace)
{
    this->camadaEnlace = camadaEnlace;
}

void CamadaFisica::RepassarPacoteParaHospedeiro(Pacote pacote)
{
    auto hospedeiros = hospedeiro->ObterHospedeiros();

    for(auto it = hospedeiros.begin(); it != hospedeiros.end(); ++it)
    {
        if(hospedeiro->IsRecheable((*it)->PegarCoordenadas()))
        {
            (*it)->PegarCamadaFisica()->ReceberPacoteDeHospedeiro(pacote);
        }
    }
}



void CamadaFisica::ReceberPacoteDeHospedeiro(Pacote pacote)
{
    EnviarPacoteParaCamadaEnlace(&pacote);
}

void CamadaFisica::EnviarPacoteParaCamadaEnlace(Pacote *pacote)
{
    camadaEnlace->ReceberPacoteCamadaFisica(pacote);
}

void CamadaFisica::ImprimirMac(std::vector<int> vetorMac)
{
    for(auto it2 = vetorMac.begin(); it2 != vetorMac.end(); ++it2)
    {
        std::cout << std::hex << std::setw(4) << std::uppercase <<  *it2;
    }
}

CamadaFisica::~CamadaFisica()
{

}