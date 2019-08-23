#ifndef PACOTE_H_
#define PACOTE_H_
#include <stdint.h>
#include <string>

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

class Pacote
{

private:
    /* data */
    
    // Versão do Protocolo, neste caso será utilizado o IPV4, logo a versão será 4
    uint8 Versao;
    
    /* Indica o tamanho do cabeçalho, para que seja possível saber onde começa de fato os dados, Pode variar devido
       Ao conjunto de opções disponíveis, se um pacote for fragmentado, ira incluir o tamanho do atributo
       Flags, offset, Identificador */
    uint32 TamanhoCabecalho;
    
    // Indica o Tamanho de todo o pacote, Incluindo o Cabeçalho
    uint16 Comprimento;
    
    // Campo Utilizado para identificar a qual Conjunto de Pacote o fragmento pertence
    uint16 Identificador;
    
    // Indica se o pacote está fragmentado, caso esteja possui valor 1 (menos o último fragmento)
    bool Flags;
    
    // Indica a posição original do fragmento caso seja fragmentado, múltiplo de 8
    uint16 OffSet;
    
    // Limitada a vida útil de um pacote, pode ser utilizado para limitar os saltos
    uint8 TTL;
    
    // Campo de Verificação de cabeçalho, Recalculado em cada roteador
    uint64 Checksum;

    // Ip de Origem
    uint8 Origem[4];

    // Iṕ de Destino
    uint8 Destino[4];

    // Dados
    std::string Dados;

public:
    Pacote(uint8 Origem[4], uint8 Destino[4], uint8 TTL, std::string Dados);
    Pacote(uint8 Origem[4], uint8 Destino[4], uint16 Identificador, bool Flags,uint16 OffSet, uint8 TTL, std::string Dados);
    ~Pacote();
    bool ChecarCheckSum();
};

#endif