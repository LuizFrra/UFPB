#include <iostream>
#include "Coordenador/Coordenador.hpp"

int main(int argc, char const *argv[])
{
    Coordenador *coordenador = new Coordenador(5, 5);

    //std::pair<int,int> Coordenadas = std::make_pair(1, 1);
    coordenador->AdicionarHospedeiro(std::make_pair(1, 2), 2);
    coordenador->AdicionarHospedeiro(std::make_pair(2, 4), 2);
    coordenador->AdicionarHospedeiro(std::make_pair(1, 4), 4);
    coordenador->AdicionarHospedeiro(std::make_pair(3, 3), 2);
    coordenador->AdicionarHospedeiro(std::make_pair(4, 3), 1);
    //coordenador->AdicionarHospedeiro(Coordenadas, 1);
    
    coordenador->ImprimirHospedeiros(false);
    coordenador->ImprimirMatrizDeAdjacencia();
    coordenador->EnviarMensagem(1, 5);
    //camadaFisica->ImprimirEnderecosMac();
    return 0;
}
