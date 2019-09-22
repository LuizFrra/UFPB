#include "Coordenador.hpp"
#include <iostream>
#include <iomanip>


Coordenador::Coordenador(int CoordenadaXMaxima, int CoordenadaYMaxima)
{
    std::vector<int> BroadCast(6);
    EnderecosMacUtilizados.push_back(BroadCast);
    this->CoordenadaXMaxima = CoordenadaXMaxima;
    this->CoordenadaYMaxima = CoordenadaYMaxima;
    CriarMapa();

    // ImprimirEnderecosMac();    
}

Hospedeiro Coordenador::AdicionarHospedeiro(std::pair<uint, uint> Coordenadas)
{
    if(!ValidaCoordenadas(Coordenadas))
        Coordenadas = GerarCoordenadaMapa();
    
    // std::cout << Coordenadas.first << " " << Coordenadas.second << "\n";

    auto EnderecoMac = CriarEnderecoMac();
    Hospedeiro *hospedeiro = new Hospedeiro(&EnderecoMac, Coordenadas.first, Coordenadas.second);
    Mapa[Coordenadas.first][Coordenadas.second] = true;
    Hospedeiros.push_back(hospedeiro);

    return *hospedeiro;
}


/********************************************************************************************************************/
/********************************************************************************************************************/
/********************************************************************************************************************/
/****************************************************UTILIDADES******************************************************/
/********************************************************************************************************************/
/********************************************************************************************************************/
/********************************************************************************************************************/

bool Coordenador::ValidaCoordenadas(std::pair<uint, uint> Coordenadas)
{
    if(Coordenadas.first < (CoordenadaXMaxima - 1) && Coordenadas.second < (CoordenadaYMaxima - 1))
    {
        if(Mapa[Coordenadas.first][Coordenadas.second])
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    return true;
}

std::pair<int, int> Coordenador::GerarCoordenadaMapa()
{
    std::pair<int, int> Coordenadas;

    Coordenadas.first = RandomNumber(0, CoordenadaXMaxima - 1);
    Coordenadas.second = RandomNumber(0, CoordenadaYMaxima - 1);

    while (Mapa[Coordenadas.first][Coordenadas.second])
    {
        Coordenadas.first = RandomNumber(0, CoordenadaXMaxima - 1);
        Coordenadas.second = RandomNumber(0, CoordenadaYMaxima - 1);
    }

    return Coordenadas;
}

void Coordenador::CriarMapa()
{
    Mapa = new bool*[CoordenadaXMaxima];

    for(int i = 0; i < CoordenadaYMaxima; i++)
        Mapa[i] = new bool[CoordenadaYMaxima];

    for(int i = 0; i < CoordenadaXMaxima; i++)
        for(int j = 0; j < CoordenadaYMaxima; j++)
            Mapa[i][j] = false;    
}

void Coordenador::ImprimirEnderecosMac()
{
    for(std::vector<std::vector<int>>::iterator it1 = EnderecosMacUtilizados.begin(); it1 != EnderecosMacUtilizados.end(); ++it1)
    {
        std::cout << "1. ";
        for(std::vector<int>::iterator it2 = it1->begin(); it2 != it1->end(); ++it2)
        {
            std::cout << std::hex << std::setw(4) << std::uppercase << (*it2);
        }
        std::cout << "\n";
    }
}

std::vector<int> Coordenador::CriarEnderecoMac()
{
    std::vector<std::vector<int>>::iterator it;

    while (true)
    {
        std::vector<int> EnderecoMac;
        for(int i = 0; i < 6; i++)
        {
            EnderecoMac.push_back(RandomNumber(0, 255));
        }

        it = std::find(EnderecosMacUtilizados.begin(), EnderecosMacUtilizados.end(), EnderecoMac);

        if(it == EnderecosMacUtilizados.end())
            return EnderecoMac;
    }
};

ulong Coordenador::RandomNumber(int min, int max)
{
    return ((seed(clock(), time(NULL), getpid())) % (max - min + 1)) + min;
}

ulong Coordenador::seed(unsigned long a, unsigned long b, unsigned long c)
{
    a=a-b;  a=a-c;  a=a^(c >> 13);
    b=b-c;  b=b-a;  b=b^(a << 8);
    c=c-a;  c=c-b;  c=c^(b >> 13);
    a=a-b;  a=a-c;  a=a^(c >> 12);
    b=b-c;  b=b-a;  b=b^(a << 16);
    c=c-a;  c=c-b;  c=c^(b >> 5);
    a=a-b;  a=a-c;  a=a^(c >> 3);
    b=b-c;  b=b-a;  b=b^(a << 10);
    c=c-a;  c=c-b;  c=c^(b >> 15);
    return c;
}