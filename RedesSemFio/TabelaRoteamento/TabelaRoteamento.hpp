#pragma once
#ifndef TABELA_ROTEAMENTO_H_
#define TABELA_ROTEAMENTO_H_

#include <vector>
#include <string>
#include <algorithm>

class TabelaRoteamento
{
private:
    std::vector<int> Origem;

    
    std::vector<std::vector<std::vector<int>>> RotasAprendidas;
    
    // Primeiro Vetor é o Destino
    // O segundo é o Proximo (next)

    std::vector<std::pair<std::vector<int>, std::vector<int>>> Roteamentos;
    
    // Usado para Retonar O Next para enviar ao Destino Sem precisar Iterar Novamente
    // 1 pair é o destino
    // 2 pair é o next
    std::pair<std::vector<int>, std::vector<int>> UltimaBusca;

    /* data */
public:

    TabelaRoteamento(std::vector<int> Origem);
    bool VerificarSeExisteRotaParaDestino(std::vector<int> Destino);
    void AprenderRoteamento(std::vector<std::vector<int>> Caminho);
    std::vector<int> ObterNextPara(std::vector<int> Destino);
    void ImprimirMac(std::vector<int> vetorMac);
    ~TabelaRoteamento();

};



#endif