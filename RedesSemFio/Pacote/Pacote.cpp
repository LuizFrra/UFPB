#include "Pacote.hpp"

Pacote::Pacote()
{

};

Pacote::~Pacote()
{

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

std::vector<int> Pacote::GetDestino()
{
    return Destino;
}

std::vector<int> Pacote::GetOrigem()
{
    return Origem;
}

std::vector<int> Pacote::GetNext()
{
    return Next;
}
