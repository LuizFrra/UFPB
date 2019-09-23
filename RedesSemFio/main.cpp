#include <iostream>
#include "Coordenador/Coordenador.hpp"

int main(int argc, char const *argv[])
{
    Coordenador *coordenador = new Coordenador(5, 5);

    std::pair<int,int> Coordenadas = std::make_pair(1, 1);
    coordenador->AdicionarHospedeiro(Coordenadas);
    coordenador->AdicionarHospedeiro(Coordenadas);
    coordenador->AdicionarHospedeiro(Coordenadas);
    coordenador->AdicionarHospedeiro(Coordenadas);
    coordenador->AdicionarHospedeiro(Coordenadas);
    
    coordenador->ImprimirHospedeiros(false);
    coordenador->ImprimirMatrizDeAdjacencia();
    //camadaFisica->ImprimirEnderecosMac();
    return 0;
}
