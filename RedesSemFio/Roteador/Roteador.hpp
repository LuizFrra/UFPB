#ifndef ROTEADOR_H_
#define ROTEADOR_H_
#include <list>
#include <map>
#include "../Hospedeiro/Hospedeiro.hpp"
#include "../Pacote/Pacote.hpp"

class Roteador
{

private:
    // Endereco da placa de rede do Roteador
    uint8 EnderecoMac[6];

    // Endereco do roteador naquela rede
    uint8 IpDaRede[4];

    // Lista com os Dispositivos conectados ao roteador
    std::list<Hospedeiro> Hospedeiros;

    // Lista com os roteadores Vizinhos
    std::list<Roteador> Vizinhos;

    // Buffer do roteador
    std::list<Pacote> Buffer;

    // Tabela de Custo do roteador, que será utilizado para determinar o alcance
    std::map<uint8[3], uint64> TabelaDeCusto;
    
    int TamanhoMaxBuffer;

    uint32 Alcance, PosicaoY, PosicaoX;
    
    /* data */
public:
    Roteador(uint8 EnderecoMac[6], uint8 IpDaRede[4], int TamanhoMaxBuffer, uint32 Alcance, uint32 PosicaoX, uint32 PosicaoY);
    ~Roteador();
    Hospedeiro AdicionarHospedeiro();

};

#endif