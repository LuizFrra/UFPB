#ifndef PACOTE_H_
#define PACOTE_H_
#include <stdint.h>
#include <string>

class Pacote
{
private:
    /* data */
    
    // Versão do Protocolo, neste caso será utilizado o IPV4, logo a versão será 4
    uint8_t Versao;
    
    // Indica o tamanho do cabeçalho, para que seja possível saber onde começa de fato os dados, Pode variar devido
    // Ao conjunto de opções disponíveis, se um pacote for fragmentado, ira incluir o tamanho do atributo
    // Flags, offset, Identificador
    uint32_t TamanhoCabecalho;
    
    // Indica o Tamanho de todo o pacote, Incluindo o Cabeçalho
    uint16_t Comprimento;
    
    // Campo Utilizado para identificar a qual Conjunto de Pacote o fragmento pertence
    uint16_t Identificador;
    
    // Indica se o pacote está fragmentado, caso esteja possui valor 1 (menos o último fragmento)
    bool Flags;
    
    // Indica a posição original do fragmento caso seja fragmentado, múltiplo de 8
    uint16_t OffSet;
    
    // Limitada a vida útil de um pacote, pode ser utilizado para limitar os saltos
    uint8_t TTL;
    
    // Campo de Verificação de cabeçalho, Recalculado em cada roteador
    uint64_t Checksum;

    // Ip de Origem
    std::string Origem;

    // Iṕ de Destino
    std::string Destino;

    // Dados
    std::string Dados;

public:
    Pacote(/* args */);
    ~Pacote();
};

Pacote::Pacote(/* args */)
{
}

Pacote::~Pacote()
{
}


#endif