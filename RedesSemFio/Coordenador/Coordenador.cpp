#include "Coordenador.hpp"
#include <iostream>



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


};



/********************************************************************************************************************/
/********************************************************************************************************************/
/********************************************************************************************************************/
/****************************************************UTILIDADES******************************************************/
/********************************************************************************************************************/
/********************************************************************************************************************/
/********************************************************************************************************************/

uint8* Coordenador::CriarEnderecoMac()
{
    while(true)
    {
        uint8 *EnderecoMac = new uint8[6];
        
        for(int i = 0; i < 6; i++)
        {
            EnderecoMac[i] = (uint8)RandomNumber(0, 255);
            //std::cout << std::hex << EnderecoMac[i] * 1;
        }
        //std::cout << "\n";
        
        std::list<uint8*>::iterator it;
        
        it = std::find(EnderecosMacUtilizados.begin(), EnderecosMacUtilizados.end(), EnderecoMac);

        if(it == EnderecosMacUtilizados.end())
            return EnderecoMac;
    }

};

uint8* Coordenador::CriarEnderecoIp()
{
    while(true)
    {
        uint8 *EnderecoIp = new uint8[4];

        for (int i = 0; i < 4; i++)
        {
            EnderecoIp[i] = (uint8)RandomNumber(0, 255);
            //std::cout << std::hex << EnderecoIp[i] * 1;
        }
        //std::cout << "\n";

        std::list<uint8*>::iterator it = std::find(EnderecosIpUtilizados.begin(), EnderecosIpUtilizados.end(), EnderecoIp);

        if(it == EnderecosIpUtilizados.end())
            return EnderecoIp;
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