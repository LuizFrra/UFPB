#ifndef _COORDENADOR_
#define _COORDENADOR_
#include <unistd.h>
#include <algorithm>
#include "../Hospedeiro/Hospedeiro.hpp"


class Coordenador
{
private:
    std::vector<std::vector<int>> EnderecosMacUtilizados;

    std::vector<Hospedeiro*> Hospedeiros;

    ulong RandomNumber(int max, int min);

    ulong seed(unsigned long a, unsigned long b, unsigned long c);

    std::vector<int> CriarEnderecoMac();

    // Coordenada que indica o X Maximo do "mapa"
    int CoordenadaXMaxima;

    // Coordenada que indica o Y Maximo do "mapa"
    int CoordenadaYMaxima;

    // Variavel Utilizada para indicar os espaços livres e ocupados do mapa
    bool **Mapa;

    // Funcao responsável por alocar o espaço de memória para o mapa
    void CriarMapa();

    // Funcao Responsavel por gerar as coordenadas do mapa caso a mesma não seja passada pelo usuario ou o usuario passou errada
    std::pair<int, int> GerarCoordenadaMapa();

    // Funcao Para validar Coordenadas
    bool ValidaCoordenadas(std::pair<uint, uint> Coordenadas);
    /* data */
public:
    void ImprimirEnderecosMac();
    Coordenador(int CoordenadaXMaxima, int CoordenadaYMaxima);
    ~Coordenador();
    Hospedeiro AdicionarHospedeiro(std::pair<uint,uint> Coordenadas);
};
#endif