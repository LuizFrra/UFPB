#include "Coordenador.hpp"
#include <iostream>
#include <iomanip>

Coordenador::Coordenador(){}

Coordenador::Coordenador(int CoordenadaXMaxima, int CoordenadaYMaxima)
{
    std::vector<int> BroadCast(6);
    EnderecosMacUtilizados.push_back(BroadCast);
    this->CoordenadaXMaxima = CoordenadaXMaxima;
    this->CoordenadaYMaxima = CoordenadaYMaxima;
    CriarMapa();
    // ImprimirEnderecosMac();    
}

Hospedeiro Coordenador::AdicionarHospedeiro(std::pair<uint, uint> Coordenadas, int Alcance)
{
    if(!ValidaCoordenadas(Coordenadas))
        Coordenadas = GerarCoordenadaMapa();
    
    // std::cout << Coordenadas.first << " " << Coordenadas.second << "\n";

    auto EnderecoMac = CriarEnderecoMac();

    if(Alcance <= 0)
        Alcance = RandomNumber(1, CoordenadaYMaxima - 1);

    Hospedeiro *hospedeiro = new Hospedeiro(EnderecoMac, Coordenadas.first, Coordenadas.second, Alcance, this);
    
    EnderecosMacUtilizados.push_back(EnderecoMac);
    Mapa[Coordenadas.first][Coordenadas.second] = true;
    Hospedeiros.push_back(hospedeiro);
    
    return *hospedeiro;
}

void Coordenador::EnviarMensagem(uint Origem, uint Destino, std::string Data)
{
    //std::cout << Hospedeiros.size();
    if(Origem == Destino || Origem <= 0 || Destino <= 0 || Origem > Hospedeiros.size() || Destino > Hospedeiros.size() )
        return;
    
    int contadorHospedeiros = 1;
    std::list<Hospedeiro*>::iterator OrigemIT;
    std::list<Hospedeiro*>::iterator DestinoIT;
    
    for(auto it = Hospedeiros.begin(); it != Hospedeiros.end(); ++it)
    {
        //std::cout << contadorHospedeiros;
        if(contadorHospedeiros == Origem)
        {
            OrigemIT = it;
        }
        else if(contadorHospedeiros == Destino)
        {
            DestinoIT = it;
        }
        contadorHospedeiros++;
    }
    // std::cout << "\n";
    // ImprimirMac((*OrigemIT)->PegarEnderecoMac());
    // std::cout << "\n";
    // ImprimirMac((*DestinoIT)->PegarEnderecoMac());
    (*OrigemIT)->EnviarMensagem(Data, (*DestinoIT)->PegarEnderecoMac());
}

int Coordenador::EnviarPacote()
{
    if(HospedeirosQueDesejamRealizarAlgo.size() > 0)
    {
        auto tarefa = HospedeirosQueDesejamRealizarAlgo.front();
        tarefa->EnviarPacoteParaVizinho();
        HospedeirosQueDesejamRealizarAlgo.pop_front();
    }
    return HospedeirosQueDesejamRealizarAlgo.size();
}

std::list<Hospedeiro*> *Coordenador::ObterHospedeiros()
{   
    return &Hospedeiros;
}

bool Coordenador::HospedeiroAlcancaMac(Hospedeiro *hospedeiro, std::vector<int> vetorMac)
{
    for(auto it = Hospedeiros.begin(); it != Hospedeiros.end(); it++)
    {
        if(vetorMac == (*it)->PegarEnderecoMac())
        {
            return hospedeiro->IsRecheable((*it)->PegarCoordenadas());
        }
    }

    return false;
}

/********************************************************************************************************************/
/********************************************************************************************************************/
/********************************************************************************************************************/
/****************************************************UTILIDADES******************************************************/
/********************************************************************************************************************/
/********************************************************************************************************************/
/********************************************************************************************************************/

void Coordenador::ImprimirMac(std::vector<int> vetorMac)
{
    for(auto it2 = vetorMac.begin(); it2 != vetorMac.end(); ++it2)
    {
        std::cout << std::hex << std::setw(4) << std::uppercase <<  *it2;
    }
}

void Coordenador::ImprimirHospedeiros(bool MostratAlcancaveis)
{   int contadorHospedeiros = 0;

    for(std::list<Hospedeiro*>::iterator it = Hospedeiros.begin(); it != Hospedeiros.end(); ++it)
    {
        std::cout << std::dec << ++contadorHospedeiros << ". ";
        std::vector<int> vetorMac = (*it)->PegarEnderecoMac();
        ImprimirMac(vetorMac);

        if(MostratAlcancaveis)
            ImprimirHospedeirosAlcancaveisPorHospedeiro(it);

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
                ImprimirMac(vetorMac);
                std::cout << "\n";
            }
        }
   }
}

void Coordenador::ImprimirMatrizDeAdjacencia()
{   
    int contadorHospedeiros = 0;
    int contadorHospedeirosInterno = 0;

    std::cout << "    ";
    for(int i = 1; i <= Hospedeiros.size(); i++)
    {
        if(i < 10)
            std::cout << std::dec << i << "  ";
        else
        {
            std::cout << std::dec << i << " ";
        }   
    }
    std::cout << "\n";
    for(auto it = Hospedeiros.begin(); it != Hospedeiros.end(); ++it)
    {   
        if(contadorHospedeiros + 1 < 10)
            std::cout << std::dec << contadorHospedeiros + 1 << " . ";
        else
            std::cout << std::dec << contadorHospedeiros + 1 << ". ";
        
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
    std::cout << "\n";
}

bool Coordenador::ValidaCoordenadas(std::pair<uint, uint> Coordenadas)
{
    if(Coordenadas.first < (CoordenadaXMaxima) && Coordenadas.second < (CoordenadaYMaxima))
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
        // for(std::vector<int>::iterator it2 = it1->begin(); it2 != it1->end(); ++it2)
        // {
        //     std::cout << std::hex << std::setw(4) << std::uppercase << (*it2);
        // }
        ImprimirMac(*it1);
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