#include <iostream>
#include "Coordenador/Coordenador.hpp"

int main(int argc, char const *argv[])
{
    int num = 0;
    Coordenador *coordenador = new Coordenador(10, 10);

    std::pair<int,int> Coordenadas = std::make_pair(1, 1);
    coordenador->AdicionarHospedeiro(std::make_pair(1, 2), 2);
    coordenador->AdicionarHospedeiro(std::make_pair(2, 4), 2);
    coordenador->AdicionarHospedeiro(std::make_pair(1, 4), 2);
    coordenador->AdicionarHospedeiro(std::make_pair(3, 3), 2);
    coordenador->AdicionarHospedeiro(std::make_pair(4, 3), 1);
    // coordenador->AdicionarHospedeiro(std::make_pair(4, 3), 2);
    // coordenador->AdicionarHospedeiro(std::make_pair(4, 3), 2);
    // coordenador->AdicionarHospedeiro(std::make_pair(4, 3), 2);
    // coordenador->AdicionarHospedeiro(std::make_pair(4, 3), 2);
    // coordenador->AdicionarHospedeiro(std::make_pair(4, 3), 2);
    // coordenador->AdicionarHospedeiro(std::make_pair(4, 3), 2);
    // coordenador->AdicionarHospedeiro(std::make_pair(4, 3), 2);
    // coordenador->AdicionarHospedeiro(std::make_pair(4, 3), 2);
    // coordenador->AdicionarHospedeiro(std::make_pair(4, 3), 2);
    // coordenador->AdicionarHospedeiro(std::make_pair(4, 3), 2);
    //coordenador->AdicionarHospedeiro(Coordenadas, 1);
    
    coordenador->ImprimirHospedeiros(false);
    coordenador->ImprimirMatrizDeAdjacencia();
    coordenador->EnviarMensagem(1, 3, "De 1 Para 3");
    coordenador->EnviarMensagem(1, 2, "De 1 Para 2");
    coordenador->EnviarPacote();
    coordenador->EnviarPacote();
    coordenador->EnviarPacote();
    coordenador->EnviarPacote();
    coordenador->EnviarPacote();
    coordenador->EnviarPacote();
    coordenador->EnviarPacote();
    coordenador->EnviarPacote();
    coordenador->EnviarPacote();
    coordenador->EnviarPacote();
    coordenador->EnviarPacote();
    // coordenador->EnviarMensagem(5, 3, "De 5 Para 3");
    // coordenador->AdicionarHospedeiro(std::make_pair(5, 3), 2);
    // coordenador->EnviarPacote();
    // coordenador->EnviarPacote();
    // coordenador->EnviarMensagem(2, 1, "De 2 Para 1");
    // coordenador->EnviarPacote();
    // coordenador->EnviarPacote();
    // coordenador->EnviarPacote();
    // coordenador->EnviarPacote();
    // coordenador->AdicionarHospedeiro(std::make_pair(4, 3), 2);
    // coordenador->EnviarPacote();
    // coordenador->EnviarPacote();
    // coordenador->EnviarPacote();
    // coordenador->EnviarPacote();
    // coordenador->EnviarPacote();    
    // while (std::cin)
    // {
    //     coordenador->EnviarPacote();

    // }
    
    //camadaFisica->ImprimirEnderecosMac();
    return 0;
}
