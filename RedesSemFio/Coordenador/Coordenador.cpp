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
    int Alcance = RandomNumber(1, CoordenadaYMaxima);
    Hospedeiro *hospedeiro = new Hospedeiro(EnderecoMac, Coordenadas.first, Coordenadas.second, Alcance);
    
    EnderecosMacUtilizados.push_back(EnderecoMac);
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

void Coordenador::ImprimirHospedeiros(bool MostratAlcancaveis)
{   int contadorHospedeiros = 0;

    for(std::list<Hospedeiro*>::iterator it = Hospedeiros.begin(); it != Hospedeiros.end(); ++it)
    {
        std::cout << std::dec << ++contadorHospedeiros << ". ";
        std::vector<int> vetorMac = (*it)->PegarEnderecoMac();
        for(auto it2 = vetorMac.begin(); it2 != vetorMac.end(); ++it2)
        {
            std::cout << std::hex << std::setw(4) << std::uppercase <<  *it2;
        }
        if(MostratAlcancaveis)
            ImprimirHospedeirosAlcancaveisPorHospedeiro(it);
        //return;
        std::cout << "\n";
    }
}

void Coordenador::ImprimirHospedeirosAlcancaveisPorHospedeiro(std::list<Hospedeiro*>::iterator hospedeiro)
{
    int contadorHospedeirosAlcancaveis = 0;
    for(auto it = Hospedeiros.begin(); it != Hospedeiros.end(); ++it)
    {
        ++contadorHospedeirosAlcancaveis;
        if((*it)->PegarEnderecoMac() != (*hospedeiro)->PegarEnderecoMac())
        {  
            if((*hospedeiro)->IsRecheable((*it)->PegarCoordenadas()))
            {
                std::cout << "\n" << "    ";
                auto vetorMac = (*it)->PegarEnderecoMac();
                std::cout << std::dec << contadorHospedeirosAlcancaveis << ". ";
                for(auto it2 = vetorMac.begin(); it2 != vetorMac.end(); ++it2)
                {
                    std::cout << std::hex << std::setw(4) << std::uppercase <<  *it2;
                }
                std::cout << "\n";
            }
        }
   }
}

void Coordenador::ImprimirMatrizDeAdjacencia()
{   
    int contadorHospedeiros = 0;
    int contadorHospedeirosInterno = 0;

    for(auto it = Hospedeiros.begin(); it != Hospedeiros.end(); ++it)
    {
        for(auto it2 = Hospedeiros.begin(); it2 != Hospedeiros.end(); ++it2)
        {
            if(contadorHospedeiros == contadorHospedeirosInterno)
            {
                std::cout << "9  ";
            }
            else if((*it)->IsRecheable((*it2)->PegarCoordenadas()))
            {
                std::cout << "1  ";
            }       
            else
            {
                std::cout << "0  ";
            }  
            contadorHospedeirosInterno++;
        }
        contadorHospedeirosInterno = 0;
        contadorHospedeiros++;
        std::cout << "\n";
    }
}

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
    for(std::list<std::vector<int>>::iterator it1 = EnderecosMacUtilizados.begin(); it1 != EnderecosMacUtilizados.end(); ++it1)
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
    std::list<std::vector<int>>::iterator it;

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