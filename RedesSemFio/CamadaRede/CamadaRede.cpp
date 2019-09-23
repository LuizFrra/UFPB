#include "CamadaRede.hpp"
#include "../CamadaEnlace/CamadaEnlace.hpp"
#include "../Hospedeiro/Hospedeiro.hpp"
#include <iostream>
#include <iomanip>
//#include "../TabelaRoteamento/TabelaRoteamento.cpp"

CamadaRede::CamadaRede(Hospedeiro *hospedeiro)
{
    this->hospedeiro = hospedeiro;
    PacoteID = 1;
    
    tabelaRoteamento = new TabelaRoteamento(hospedeiro->PegarEnderecoMac());
}
    
void CamadaRede::DefinirCamadaDeBaixo(CamadaEnlace *camadaEnlace)
{
    this->camadaEnlace = camadaEnlace;
}

void CamadaRede::EnviarMensagem(Pacote pacote)
{
    pacote.AdicionarUID(PacoteID);
    //ImprimirMac(pacote.GetOrigem());
    PacoteID++;
    auto EnderecoMacDestino = pacote.GetDestino();

    if(tabelaRoteamento->VerificarSeExisteRotaParaDestino(EnderecoMacDestino))
    {
        //std::cout << "Oi";
        pacote.AdicionarNext(tabelaRoteamento->ObterNextPara(EnderecoMacDestino));
        camadaEnlace->AdicionarPacoteParaEnvio(pacote);
    }
    else
    {
        // Nessa condição Não há um caminho para o pacote e o memso ira ficar em espera ate que seja encontrada
        PacotesAguardandoRota.push_back(pacote);
        Pacote pacoteRREQ = Pacote(hospedeiro->PegarEnderecoMac(), pacote.GetDestino(), TipoPacote::RREQ);
        camadaEnlace->AdicionarPacoteParaEnvio(pacoteRREQ);
    }
}

void CamadaRede::ImprimirMac(std::vector<int> vetorMac)
{
    for(auto it2 = vetorMac.begin(); it2 != vetorMac.end(); ++it2)
    {
        std::cout << std::hex << std::setw(4) << std::uppercase <<  *it2;
    }
}

CamadaRede::~CamadaRede()
{

}