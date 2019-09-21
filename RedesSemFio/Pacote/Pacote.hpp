#ifndef PACOTE_H_
#define PACOTE_H_
#include <stdint.h>
#include <string>
#include <vector>

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

enum TipoPacote
{
    Mensagem,
    RouteRequest,
    RouteReply
};

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
    std::vector<int> Origem;

    // Iṕ de Destino
    std::vector<int> Destino;

    // Foward, Se o Valor estiver em 0.0.0.0 Significa que é BROADCAST
    std::vector<int> Next;

    // Dados
    std::string Dados;

    // Variavel que define o tipo do pacote: dados, route request, route reply ...
    TipoPacote tipoPacote;

    // Lista de Hospedeiro pelo qual o pacote passou
    std::vector<std::vector<int>> HospedeirosPeloQualPassou;

public:
    Pacote();
    ~Pacote();
    bool ChecarCheckSum();
    std::vector<int> GetDestino();
    std::vector<int> GetOrigem();
    std::vector<int> GetNext();
};

#endif