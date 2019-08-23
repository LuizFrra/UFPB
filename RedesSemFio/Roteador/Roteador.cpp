#include "Roteador.hpp"

Roteador::Roteador(uint8 EnderecoMac[6], uint8 IpDaRede[4], int TamanhoMaxBuffer, uint32 Alcance, uint32 PosicaoX, uint32 PosicaoY)
{
    *this->EnderecoMac = *EnderecoMac;
    *this->IpDaRede = *IpDaRede;
    this->TamanhoMaxBuffer = TamanhoMaxBuffer;
    this->Alcance = Alcance;
    this->PosicaoX = PosicaoX;
    this->PosicaoY = PosicaoY;
};

Roteador::~Roteador()
{

};

Hospedeiro Roteador::AdicionarHospedeiro()
{

};