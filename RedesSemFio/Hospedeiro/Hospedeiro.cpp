#include "Hospedeiro.hpp"
#include <iostream>
#include <math.h>

#include "../CamadaEnlace/CamadaEnlace.cpp"
#include "../CamadaFisica/CamadaFisica.cpp"
#include "../CamadaRede/CamadaRede.cpp"
#include "../Coordenador/Coordenador.cpp"

Hospedeiro::Hospedeiro(std::vector<int> EnderecoMac, uint CoordenadaX, uint CoordenadaY, uint Alcance, Coordenador *coordenador)
{
    this->coordenador = coordenador;

    this->CoordenadaX = CoordenadaX;
    this->CoordenadaY = CoordenadaY;
    this->EnderecoMac = EnderecoMac;
    this->Alcance = Alcance;
    camadaEnlace = new CamadaEnlace(this);
    camadaFisica = new CamadaFisica(this);
    camadaRede = new CamadaRede(this);

    camadaRede->DefinirCamadaDeBaixo(camadaEnlace);
    camadaFisica->DefinirCamadaDeCima(camadaEnlace);
    camadaEnlace->DefinirCamadaDeBaixo(camadaFisica);
    camadaEnlace->DefinirCamadaDeCima(camadaRede);
}

void Hospedeiro::EnviarMensagem(std::string mensagem, std::vector<int> Destino)
{
    if(mensagem.size() > 0 && Destino.size() == 6)
    {
        Pacote pacote = Pacote(this->EnderecoMac, Destino, mensagem, TipoPacote::DATA);
        camadaRede->EnviarMensagem(pacote);
    }
}

void Hospedeiro::EntrarNaFilaCoordenador()
{
    coordenador->HospedeirosQueDesejamRealizarAlgo.push_back(this);
}

bool Hospedeiro::IsRecheable(std::pair<uint, uint> Coordenadas)
{
    //std::cout << this->CoordenadaX << " primeiras " << Coordenadas.first << "\n";

    int primeiraParte = pow((int)this->CoordenadaX - (int)Coordenadas.first, 2); 
    int segundaParte = pow((int)this->CoordenadaY - (int)Coordenadas.second, 2);

    //std::cout << primeiraParte << " " << segundaParte << "\n";
    float distanciaDoisPontos = std::sqrt(primeiraParte + segundaParte);
    //std::cout << distanciaDoisPontos << "\n";
    return distanciaDoisPontos <= (float)Alcance ? true : false;
}

std::pair<uint, uint> Hospedeiro::PegarCoordenadas()
{
    return std::make_pair(CoordenadaX, CoordenadaY);
}

// Retorna a camada Fisica do Hospedeiro para que ele possa dar um Push no dado 
CamadaFisica* Hospedeiro::PegarCamadaFisica()
{
    return camadaFisica;
}


std::vector<int> Hospedeiro::PegarEnderecoMac()
{
    // std::cout << "Ola";
    return EnderecoMac;
}

Hospedeiro::~Hospedeiro()
{

}