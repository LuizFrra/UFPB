#include "Pacote.hpp"

Pacote::Pacote(uint8 Origem[4], uint8 Destino[4], uint8 TTL, std::string Dados)
{
    Identificador = 0;
    OffSet = 0;
    Flags = 0;

    this->TTL = TTL;
    this->Dados = Dados;
    *this->Origem = *Origem;
    *this->Destino = *Destino;

    Versao = 4;

    TamanhoCabecalho = Checksum = sizeof(Versao) + sizeof(Comprimento) + sizeof(Checksum) + (sizeof(Destino) * 4)
                            + (sizeof(Origem) * 4) + sizeof(TTL);
    Comprimento = TamanhoCabecalho + Dados.length();
    
};

Pacote::Pacote(uint8 Origem[4], uint8 Destino[4], uint16 Identificador, bool Flags,uint16 OffSet, uint8 TTL, std::string Dados)
{
    Versao = 4;
    this->TTL = TTL;

    TamanhoCabecalho = Checksum = sizeof(Versao) + sizeof(Comprimento) + sizeof(Checksum) + (sizeof(Destino) * 4)
                            + (sizeof(Origem) * 4) + sizeof(TTL) + sizeof(Identificador) + sizeof(OffSet) + sizeof(Flags);
    Comprimento = TamanhoCabecalho + Dados.length();
};

Pacote::~Pacote()
{
    delete []Origem;
    delete []Destino;
};

// Checa o CheckSum, Realizando apenas para o cabeçalho
bool Pacote::ChecarCheckSum()
{
    // If e Else para checar se o pacote é do tipo fragmentado ou não
    if(OffSet != 0 || (OffSet == 0 && Flags == true))
    {   
        // Calcular o atual tamanho do cabeçalho do pacote
        int currentCheckSum = Checksum = sizeof(Versao) + sizeof(Comprimento) + sizeof(Checksum) + (sizeof(Destino) * 4)
                            + (sizeof(Origem) * 4) + sizeof(TTL) + sizeof(Identificador) + sizeof(OffSet) + sizeof(Flags);
        
        // Checa se é igual ao original
        if(currentCheckSum == Checksum)
            return true;
        else
            return false;
    }
    else
    {
        // Calcula o atual tamanho do cabeçalho do pacote
        int currentCheckSum = Checksum = sizeof(Versao) + sizeof(Comprimento) + sizeof(Checksum) + (sizeof(Destino) * 4)
                            + (sizeof(Origem) * 4) + sizeof(TTL);
        
        // Checa se é igual ao original
        if(currentCheckSum == Checksum)
            return true;
        else
            return false;
    }
    
};

uint8 *Pacote::GetDestino()
{
    return Destino;
}

uint8 *Pacote::GetOrigem()
{
    return Origem;
}


