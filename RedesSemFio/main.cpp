#include <iostream>
#include "Coordenador/Coordenador.hpp"

int main(int argc, char const *argv[])
{
    int num = 0;
    Coordenador *coordenador = new Coordenador(6, 6);

    //std::pair<int,int> Coordenadas = std::make_pair(1, 1);
    coordenador->AdicionarHospedeiro(std::make_pair(1, 2), 2);
    coordenador->AdicionarHospedeiro(std::make_pair(2, 4), 2);
    coordenador->AdicionarHospedeiro(std::make_pair(1, 4), 2);
    coordenador->AdicionarHospedeiro(std::make_pair(3, 3), 2);
    coordenador->AdicionarHospedeiro(std::make_pair(4, 3), 1);
    //coordenador->AdicionarHospedeiro(Coordenadas, 1);
    
    coordenador->ImprimirHospedeiros(false);
    coordenador->ImprimirMatrizDeAdjacencia();
    coordenador->EnviarMensagem(1, 5, "Por favor Pega Mizera Fudida");
    coordenador->EnviarPacote();
    coordenador->EnviarPacote();
    coordenador->EnviarPacote();
    coordenador->EnviarPacote();
    coordenador->EnviarPacote();
    coordenador->EnviarPacote();
    coordenador->AdicionarHospedeiro(std::make_pair(5, 3), 2);
    coordenador->EnviarPacote();
    coordenador->EnviarPacote();
    coordenador->EnviarMensagem(5, 1, "De 5 Para 1");
    coordenador->EnviarPacote();
    coordenador->EnviarPacote();
    coordenador->EnviarPacote();
    coordenador->EnviarPacote();
    coordenador->EnviarPacote();
    coordenador->EnviarPacote();
    coordenador->EnviarPacote();
    coordenador->EnviarPacote();
    coordenador->EnviarPacote();    
    while (std::cin)
    {
        coordenador->EnviarPacote();
    }
    
    //camadaFisica->ImprimirEnderecosMac();
    return 0;
}
