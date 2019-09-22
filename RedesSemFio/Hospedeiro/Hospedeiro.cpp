#include "Hospedeiro.hpp"
#include "../CamadaEnlace/CamadaEnlace.cpp"
#include "../CamadaFisica/CamadaFisica.cpp"
#include "../CamadaRede/CamadaRede.cpp"

Hospedeiro::Hospedeiro(std::vector<int> *EnderecoMac, uint CoordenadaX, uint CoordenadaY)
{
    this->CoordenadaX = CoordenadaX;
    this->CoordenadaY = CoordenadaY;
    this->EnderecoMac = EnderecoMac;

    camadaEnlace = new CamadaEnlace();
    camadaFisica = new CamadaFisica();
    camadaRede = new CamadaRede();

    camadaRede->DefinirCamadaDeBaixo(camadaEnlace);
    camadaFisica->DefinirCamadaDeCima(camadaEnlace);
    camadaEnlace->DefinirCamadaDeBaixo(camadaFisica);
    camadaEnlace->DefinirCamadaDeCima(camadaRede);

    TomDeOcupado = false;
}


// Retorna a camada Fisica do Hospedeiro para que ele possa dar um Push no dado 
CamadaFisica* Hospedeiro::PegarCamadaFisica()
{
    return camadaFisica;
}

bool Hospedeiro::PegarTomDeOcupado()
{
    return TomDeOcupado;
}

bool Hospedeiro::DefinirTomDeOcupado(bool valor)
{
    if(TomDeOcupado && !valor) // Se Tom de Ocupado for Verdadeiro e Valor Falso, entao deve colocar falso
        TomDeOcupado = false;
    else if(!TomDeOcupado && valor) // Se tom de Ocupado for false e valor true, entao deve colocar true
        TomDeOcupado = true;

    return TomDeOcupado;
}

Hospedeiro::~Hospedeiro()
{

}