#include <iostream>
#include "Coordenador/Coordenador.hpp"

int main(int argc, char const *argv[])
{
    Coordenador *coordenador = new Coordenador(5, 5);

    //std::pair<int,int> Coordenadas = std::make_pair(1, 1);
    coordenador->AdicionarHospedeiro(std::make_pair(1, 2), 2);
    coordenador->AdicionarHospedeiro(std::make_pair(2, 4), 2);
    coordenador->AdicionarHospedeiro(std::make_pair(1, 4), 2);
    coordenador->AdicionarHospedeiro(std::make_pair(3, 3), 2);
    coordenador->AdicionarHospedeiro(std::make_pair(4, 3), 1);
    //coordenador->AdicionarHospedeiro(Coordenadas, 1);
    
    coordenador->ImprimirHospedeiros(false);
    coordenador->ImprimirMatrizDeAdjacencia();
    coordenador->EnviarMensagem(2, 1);
    //coordenador->EnviarMensagem(1, 3);
    coordenador->EnviarPacote();
    coordenador->EnviarPacote();
    coordenador->EnviarPacote();
    //coordenador->EnviarMensagem(4, 2);
    coordenador->EnviarPacote();
    //coordenador->EnviarPacote();
    //coordenador->EnviarPacote();
    //coordenador->EnviarPacote();
    //camadaFisica->ImprimirEnderecosMac();
    return 0;
}
