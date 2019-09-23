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
    RREQ,
    RREP,
    DATA,
    RERR,
    UACK,
    MACK
};

class Pacote
{

private:
    /* data */

    // Campo Utilizado para identificar a qual Conjunto de Pacote o fragmento pertence
    uint Identificador;

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
    Pacote(std::vector<int> origem, std::vector<int> destino, std::string dados, TipoPacote tipoPacote);
    Pacote(std::vector<int> origem, std::vector<int> destino, TipoPacote tipoPacote);
    void AdicionarCaminho(std::vector<int> HospedeiroAtual);
    void AdicionarNext(std::vector<int> next);
    uint AdicionarUID(uint UID);
    std::vector<int> GetDestino();
    std::vector<int> GetOrigem();
    std::vector<int> GetNext();
    std::vector<std::vector<int>> PegarCaminho();
    ~Pacote();
};

#endif