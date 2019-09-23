#include "CamadaEnlace.hpp"
#include "../CamadaRede/CamadaRede.hpp"
#include "../CamadaFisica/CamadaFisica.hpp"
#include "../Hospedeiro/Hospedeiro.hpp"


CamadaEnlace::CamadaEnlace(Hospedeiro *hospedeiro)
{
    this->hospedeiro = hospedeiro;
}

void CamadaEnlace::AdicionarPacoteParaEnvio(Pacote pacote)
{
    PacotesParaEnvios.push_back(pacote);
    hospedeiro->EntrarNaFilaCoordenador();
    // A Partir Deste ponto a Camada de Enlance Deve Esperar ser Chamada Pelo Coordenador para Enviar os pacotes
    // Para a camada Fisica
}

void CamadaEnlace::EnviarPacotes()
{
    if(PacotesParaEnvios.size() > 0)
    {
        auto pacote = PacotesParaEnvios.front();

    }
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