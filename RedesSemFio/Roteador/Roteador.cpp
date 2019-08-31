#include "Roteador.hpp"
#include <iostream>
Roteador::Roteador(uint8 EnderecoMac[6], uint8 IpDaRede[4], int TamanhoMaxBuffer, uint32 Alcance, uint32 PosicaoX, uint32 PosicaoY)
{
    std::copy(EnderecoMac, EnderecoMac + 6, this->EnderecoMac);
    std::copy(IpDaRede, IpDaRede + 3, this->IpDaRede);
    this->TamanhoMaxBuffer = TamanhoMaxBuffer;
    this->Alcance = Alcance;
    this->PosicaoX = PosicaoX;
    this->PosicaoY = PosicaoY;
    // for(int i = 0; i < 6; i++)
    //     std::cout << std::hex << this->EnderecoMac[i] * 1;
};


Roteador* Roteador::AdicionarVizinho(Roteador *Vizinho)
{
    if(Vizinho->EstaNoAlcance(PosicaoX, PosicaoY))
    {
        if(EstaNoAlcance(Vizinho->GetPosicaoX(), Vizinho->GetPosicaoY()))
        {
            Vizinho->Vizinhos.push_back(this);
            Vizinhos.push_back(Vizinho);
        }
    }
    return this;
}

void Roteador::ImprimirMacVizinhos()
{
    for (std::list<Roteador*>::iterator it = Vizinhos.begin(); it != Vizinhos.end(); it++)
    {
        for(int count = 0; count < 6; count++)
        {
            std::cout << std::hex << (*it)->EnderecoMac[count] * 1;
        }
        std::cout << "\n";
        /* code */
    }
    
};

void Roteador::ImprimirIpVizinhos()
{
    for (std::list<Roteador*>::iterator it = Vizinhos.begin(); it != Vizinhos.end(); it++)
    {
        for(int count = 0; count < 4; count++)
        {
            std::cout << std::hex << (*it)->IpDaRede[count] * 1;
        }
        std::cout << "\n";
        /* code */
    }
    
};

bool Roteador::EstaNoAlcance(uint32 X, uint32 Y)
{
    double distancia = sqrt(pow((int)(this->PosicaoX - X), 2) + pow((int)(this->PosicaoY - Y), 2));
    //std::cout << (int)(this->PosicaoX - X) << " Ok\n";

    return distancia <= Alcance ? true : false;
};

uint32 Roteador::GetPosicaoX()
{
    return PosicaoX;
};

uint32 Roteador::GetPosicaoY()
{
    return PosicaoY;
};

Roteador::~Roteador()
{

};
