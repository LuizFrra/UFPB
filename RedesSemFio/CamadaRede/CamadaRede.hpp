#pragma once

#ifndef _CAMADA_DE_REDE_H_
#define _CAMADA_DE_REDE_H_
#define DEBUG true


#include "../Pacote/Pacote.hpp"
#include "../TabelaRoteamento/TabelaRoteamento.hpp"
#include <vector>
#include <algorithm>

class CamadaEnlace;
class Hospedeiro;
class TabelaRoteamento;

class CamadaRede
{
    
private:
    TabelaRoteamento *tabelaRoteamento;

    // Hospedeiro a qual a camada pertence
    Hospedeiro *hospedeiro;

    // Camada a qual Rede presta serviço
    CamadaEnlace *camadaEnlace;

    // Contador do Pacote
    uint PacoteID;

    // Fila de Aguardando ACK dos nós Vizinho = MACK, Primeiro argumento é o contador do Pacote e o Segundo Quem enviou o Pacote
    std::vector<std::pair<uint, Hospedeiro>> MACKS;
    
    // Fila De Pacotes De Data Aguardando Rota
    std::vector<Pacote> PacotesAguardandoRota;

    // Lista de pacotes recebidos, primeiro pair é  o ID do mesmo e o segundo pair quem originiou o mesmo
    std::vector<std::pair<uint, std::vector<int>>> PacotesRecebidos;
    
    /* data */
public:
    CamadaRede(Hospedeiro *hospedeiro);
    void DefinirCamadaDeBaixo(CamadaEnlace *camadaEnlace);
    void ImprimirMac(std::vector<int> vetorMac);
    void EnviarMensagem(Pacote pacote);
    void ReceberPacoteCamadaEnlance(Pacote pacote);
    bool AdicionarPacoteAosRecebidos(Pacote pacote);
    Pacote CriarPacoteRREPPara(Pacote pacoteRREQ);
    void CriarPacoteRREQPara(Pacote pacote);
    bool AdicionarDestinoAoPacote(Pacote &pacote);
    void ImprimeInformacoesOrigemDestino(Pacote pacote, bool isDestino);
    ~CamadaRede();
};

#endif