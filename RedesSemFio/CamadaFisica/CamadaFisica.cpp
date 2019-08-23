#include "CamadaFisica.hpp"
#include <iostream>

CamadaFisica::CamadaFisica(int X, int Y)
{
    Regiao = new uint16*[X];

    for(int i = 0; i < X; i++)
    {
        Regiao[i] = new uint16[Y];
    }
};

uint8* CamadaFisica::CriarEnderecoMac()
{
    while(true)
    {
        uint8 *EnderecoMac = new uint8[6];
        
        for(int i = 0; i < 6; i++)
            EnderecoMac[i] = (uint8)RandomNumber(0, 255);
        
        std::list<uint8*>::iterator it;
        
        it = std::find(EnderecosMacUtilizados.begin(), EnderecosMacUtilizados.end(), EnderecoMac);

        if(it == EnderecosMacUtilizados.end())
            return EnderecoMac;
    }

};

uint8* CamadaFisica::CriarEnderecoIp()
{
    while(true)
    {
        uint8 *EnderecoIp = new uint8[4];

        for (int i = 0; i < 4; i++)
            EnderecoIp[i] = (uint8)RandomNumber(0, 255);
        
        std::list<uint8*>::iterator it = std::find(EnderecosIpUtilizados.begin(), EnderecosIpUtilizados.end(), EnderecoIp);

        if(it == EnderecosIpUtilizados.end())
            return EnderecoIp;
    }
};

void CamadaFisica::InstalarRoteador(uint32 Alcance, uint32 PosicaoX, uint32 PosicaoY)
{
    uint8 *EnderecoMac = CriarEnderecoMac();
    
    uint8 *EnderecoIp = CriarEnderecoIp();
    
    Roteador *roteador = new Roteador(EnderecoMac, EnderecoIp, 10, 5, 0, 0);

};

unsigned long CamadaFisica::RandomNumber(int min, int max)
{
    return ((seed(clock(), time(NULL), getpid())) % (max - min + 1)) + min;
}

unsigned long CamadaFisica::seed(unsigned long a, unsigned long b, unsigned long c)
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

void CamadaFisica::ImprimirEnderecosMac()
{
    EnderecosMacUtilizados.push_back(CriarEnderecoMac());
    EnderecosMacUtilizados.push_back(CriarEnderecoMac());
    EnderecosMacUtilizados.push_back(CriarEnderecoMac());
    EnderecosMacUtilizados.push_back(CriarEnderecoMac());
    EnderecosMacUtilizados.push_back(CriarEnderecoMac());
    for(std::list<uint8*>::iterator it = EnderecosMacUtilizados.begin(); it != EnderecosMacUtilizados.end(); it++)
    {
        std::cout << (int*)*it << std::endl;
    }
}