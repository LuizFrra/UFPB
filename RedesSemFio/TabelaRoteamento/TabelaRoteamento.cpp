#include "TabelaRoteamento.hpp"

TabelaRoteamento::TabelaRoteamento(std::vector<int> Origem)
{
    this->Origem = Origem;
}

bool TabelaRoteamento::VerificarSeExisteRotaParaDestino(std::vector<int> Destino)
{
    for(auto it = Roteamentos.begin(); it != Roteamentos.end(); ++it)
    {
        if(it->first == Destino)
        {
            UltimaBusca.first = Destino;
            UltimaBusca.second = it->second;
            return true;
        }
    }

    return false;
}

std::vector<int> TabelaRoteamento::ObterNextPara(std::vector<int> Destino)
{
    if(UltimaBusca.first == Destino)
    {
        return UltimaBusca.second;
    }
    else
    {
        std::vector<int> v;
        return v;
    }
    
}

void TabelaRoteamento::AprenderRoteamento(std::vector<std::vector<int>> Caminho)
{

}

TabelaRoteamento::~TabelaRoteamento()
{

}