#include "Coordenador.hpp"
#include <iostream>
#include <iomanip>


Coordenador::Coordenador()
{
    // Roteador *roteador = new Roteador(CriarEnderecoMac(), CriarEnderecoIp(), 10, 1000, 10, 10);
    // Roteadores.push_back(roteador);
    // roteador = new Roteador(CriarEnderecoMac(), CriarEnderecoIp(), 10, 1000, 12, 12);
    // roteador->AdicionarVizinho(Roteadores.front());
    // roteador->ImprimirMacVizinhos();
    // Roteadores.front()->ImprimirMacVizinhos();
    // std::cout << "Ip\n";
    // roteador->ImprimirIpVizinhos();
    // Roteadores.front()->ImprimirIpVizinhos();
    EnderecosMacUtilizados.push_back(CriarEnderecoMac());
    EnderecosMacUtilizados.push_back(CriarEnderecoMac());
    EnderecosMacUtilizados.push_back(CriarEnderecoMac());
    EnderecosMacUtilizados.push_back(CriarEnderecoMac());
    ImprimirEnderecosMac();

};



/********************************************************************************************************************/
/********************************************************************************************************************/
/********************************************************************************************************************/
/****************************************************UTILIDADES******************************************************/
/********************************************************************************************************************/
/********************************************************************************************************************/
/********************************************************************************************************************/

void Coordenador::ImprimirEnderecosMac()
{
    for(std::vector<std::vector<int>>::iterator it1 = EnderecosMacUtilizados.begin(); it1 != EnderecosMacUtilizados.end(); ++it1)
    {
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