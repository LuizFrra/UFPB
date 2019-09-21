#ifndef HOSPEDEIRO_H_
#define HOSPEDEIRO_H_
#include <stdint.h>
#include <list>
#include "../Pacote/Pacote.hpp"

class Hospedeiro
{

private:

    // Endereco da placa de rede *Numero Unico*
    uint8 EnderecoMac[6];
    

public:
    Hospedeiro(uint8 IpNaRede, uint8 *EnderecoMac);
    void CriarPacote(uint8 Destino[4], uint64 numeroPacotes, std::list<std::string> dados);
    void CriarPacote(uint8 Destino[4], uint64 numeroPacotes);
    ~Hospedeiro();
};

#endif

