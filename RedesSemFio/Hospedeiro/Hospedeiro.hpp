#ifndef HOSPEDEIRO_H_
#define HOSPEDEIRO_H_
#include <stdint.h>

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

class Hospedeiro
{

private:
    // Ip do hospedeiro na rede
    uint8 Ip[4];

    // Endereco da placa de rede do hospedeiro
    uint8 EnderecoMac[6][2];

public:
    Hospedeiro(uint8 IP, uint8 EnderecoMac[6][2]);
    ~Hospedeiro();
};

#endif

