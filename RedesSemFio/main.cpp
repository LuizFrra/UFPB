#include <iostream>
#include "Coordenador/Coordenador.hpp"
#include <sstream>
#include <string>
void ExibirMenu()
{
    //std::system("clear");
    std::cout << "\nMenu Principal\n";
    std::cout << "1. Adicionar Hospedeiro\n";
    std::cout << "2. Enviar Mensagem\n";
    std::cout << "3. Executar Round\n";
    std::cout << "4. Imprimir Informacoes Hospedeiros\n";
    std::cout << "5. Executar Todos Rounds\n";
}

int main(int argc, char const *argv[])
{
    // int num = 0;
    Coordenador *coordenador = new Coordenador(10, 10);

    // std::pair<int,int> Coordenadas = std::make_pair(1, 1);
    coordenador->AdicionarHospedeiro(std::make_pair(1, 2), 2);
    coordenador->AdicionarHospedeiro(std::make_pair(2, 3), 2);
    coordenador->AdicionarHospedeiro(std::make_pair(3, 4), 3);
    // coordenador->AdicionarHospedeiro(std::make_pair(3, 3), 2);
    // coordenador->AdicionarHospedeiro(std::make_pair(4, 3), 1);
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
    // coordenador->AdicionarHospedeiro(Coordenadas, 1);
    
    coordenador->ImprimirHospedeiros(false);
    coordenador->ImprimirMatrizDeAdjacencia();
    coordenador->EnviarMensagem(1, 3, "De 1 Para 3");
    // coordenador->EnviarMensagem(1, 2, "De 1 Para 2");
    // coordenador->EnviarMensagem(5, 3, "De 5 Para 3");
    // coordenador->AdicionarHospedeiro(std::make_pair(5, 3), 2);
    // coordenador->EnviarMensagem(2, 1, "De 2 Para 1");
    // coordenador->AdicionarHospedeiro(std::make_pair(4, 3), 2);
    // coordenador->EnviarMensagem(16, 3, "De 16 Para 3");
    // coordenador->EnviarMensagem(15, 7, "De 15 Para 7");
    
    while (coordenador->EnviarPacote())
    {

    }
    // int N = -1;
    // int M = -1;
    // while (true)
    // {
    //     std::cout << "Defina o Tamanho Do mapa NxM\n";
    //     std::cout << "N : ";
    //     std::cin >> N;
    //     std::cout << "\nM : ";
    //     std::cin >> M;
    //     if(N > 0 && M > 0)
    //         break;
    // }
    
    // Coordenador *coordenador = new Coordenador(N, M);

    // //ExibirMenu();
    // int opcao = -1;
    // int coordenadaX;
    // int coordenadaY;
    // int alcance;
    // int numHospedeiros = 0;
    // int origem = -1;
    // int destino = -1;
    // std::string nada;
    // std::string mensagem;
    // while (true)
    // {
    //     ExibirMenu();
    //     std::cin >> opcao;
    //     switch (opcao)
    //     {
    //     case 1:
    //         std::cout << "\nVoce Escolheu Adicionar Hospedeiro, Digite a Coordenada do Hospedeiro NxM : \n";
    //         while (true)
    //         {
    //             std::cout << "N : ";
    //             std::cin >> coordenadaX;
    //             std::cout << "\nM : ";
    //             std::cin >> coordenadaY;

    //             if((coordenadaY > M || coordenadaX > N) || (coordenadaY < 1 || coordenadaX < 1))
    //                 std::cout << "\nCoordenadas Invalidas, Tente Novamente.\n";
    //             else
    //             {
    //                 std::cout << "\nDefina o Alcance do Hospedeiro : \n";
    //                 std::cin >> alcance;
    //                 if(alcance > 0)
    //                     break;
    //                 else
    //                     std::cout << "\nAlcance Invalido.\n";
    //             }
    //         }
    //         coordenador->AdicionarHospedeiro(std::make_pair(coordenadaX, coordenadaY), alcance);
    //         std::cout << "\n\n";
    //         coordenador->ImprimirHospedeiros(false);
    //         std::cout << "\n\n";
    //         coordenador->ImprimirMatrizDeAdjacencia();
    //         numHospedeiros++;
    //         std::system("clear");
    //         break;
    //     case 2:
    //         while(true)
    //         {
    //             std::cout << "\nVoce Escolheu Enviar Mensagem, Coloque O Numero de origem, destino e a mensagem\n";
    //             std::cout << "Origem : ";
    //             std::cin >> origem;
    //             std::cout << "\nDestino : ";
    //             std::cin >> destino;
    //             if((origem > 0 && origem <= numHospedeiros) && (destino > 0 && destino <=numHospedeiros) && origem != destino)
    //                 break;
    //             else
    //                 std::cout << "\n Destino Ou Hospedeiro Invalidos.\n";
    //         }
    //         std::cout << "\nDigire a Mensagem : ";
    //         //std::cin >> mensagem;
    //         std::cin.ignore();
    //         std::getline(std::cin, mensagem);
    //         std::cout <<"\n\n";
    //         coordenador->EnviarMensagem(origem, destino, mensagem);
    //         std::system("clear");
    //         break;
    //     case 3:
    //         coordenador->EnviarPacote();
    //         break;
    //     case 4:
    //         std::cout << "\n\n";
    //         coordenador->ImprimirHospedeiros(false);
    //         std::cout << "\n\n";
    //         coordenador->ImprimirMatrizDeAdjacencia();
    //         std::cout << "\nDigite Qualquer Tecla Para Continuar.\n";
    //         std::cin.ignore();
    //         std::getline(std::cin, nada);
    //         std::system("clear");
    //         break;
    //     case 5:
    //         while(coordenador->EnviarPacote());
    //         std::cout << "\nDigite Qualquer Tecla Para Continuar.\n";
    //         std::cin.ignore();
    //         std::getline(std::cin, nada);
    //         std::system("clear");
    //         break;
    //     default:
    //         break;
    //     }
    // }
    
    //camadaFisica->ImprimirEnderecosMac();
    return 0;
}
