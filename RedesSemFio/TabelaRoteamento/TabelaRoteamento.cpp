#include "TabelaRoteamento.hpp"
#include <iostream>
#include <iomanip>
TabelaRoteamento::TabelaRoteamento(std::vector<int> Origem)
{
    this->Origem = Origem;
}
// Verifica se Consegue Alcancar Destino
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
    auto iteratorRotasAprendidas = std::find(RotasAprendidas.begin(), RotasAprendidas.end(), Caminho);
    
    if(iteratorRotasAprendidas == RotasAprendidas.end())
        RotasAprendidas.push_back(Caminho);
    
    auto iteradorMacOrigem = std::find(Caminho.begin(), Caminho.end(), Origem);
    
    std::vector<int> macVizinho;
    bool IsVizinho = true;
    //iteradorMacOrigem++;
    for(auto mac = iteradorMacOrigem; mac != Caminho.end(); ++mac)
    {
        if(IsVizinho)
        {
            if(Origem != *mac)
            {
                //ImprimirMac(*mac);
                //std::cout << "\n";
                Roteamentos.push_back(std::make_pair(*mac, *mac));
                macVizinho = *mac;
                IsVizinho = false;
            }
        }else
        {
            //ImprimirMac(*mac);
            //std::cout << "\n";
            Roteamentos.push_back(std::make_pair(*mac, macVizinho));
        }
    }

    IsVizinho = true;
    std::reverse(Caminho.begin(), Caminho.end());
    iteradorMacOrigem = std::find(Caminho.begin(), Caminho.end(), Origem);

    for(auto mac = iteradorMacOrigem; mac != Caminho.end(); ++mac)
    {
        //ImprimirMac(*mac);
        //std::cout << "\n";
        if(IsVizinho)
        {
            if(Origem != *mac)
            {
              //  ImprimirMac(*mac);
               // std::cout << "\n";
                Roteamentos.push_back(std::make_pair(*mac, *mac));
                macVizinho = *mac;
                IsVizinho = false;
            }
        }else
        {
            //ImprimirMac(*mac);
            //std::cout << "\n";
            Roteamentos.push_back(std::make_pair(*mac, macVizinho));
        }
    }

    // for(auto it =Caminho.begin(); it != Caminho.end(); ++it)
    // {
    //     ImprimirMac(*it);
    // }
}

void TabelaRoteamento::ImprimirMac(std::vector<int> vetorMac)
{
    for(auto it2 = vetorMac.begin(); it2 != vetorMac.end(); ++it2)
    {
        std::cout << std::hex << std::setw(4) << std::uppercase <<  *it2;
    }
}

TabelaRoteamento::~TabelaRoteamento()
{

}