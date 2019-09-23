#include "CamadaRede.hpp"
#include "../CamadaEnlace/CamadaEnlace.hpp"
#include "../Hospedeiro/Hospedeiro.hpp"
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
    PacoteID++;
    auto EnderecoMacDestino = pacote.GetDestino();

    if(tabelaRoteamento->VerificarSeExisteRotaParaDestino(EnderecoMacDestino))
    {
        pacote.AdicionarNext(tabelaRoteamento->ObterNextPara(EnderecoMacDestino));
    }
    
}

CamadaRede::~CamadaRede()
{

}