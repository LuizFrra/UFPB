#include "client_server_udp.h"

using namespace CLIENT_SERVER_UDP;

int main(int argc, char const *argv[])
{
    // int jogoDaVelha[4][4] = {{-1, -1, -1, -1},
    //                         {-1, -1, -1, -1},
    //                         {-1, -1, -1, -1},
    //                         {-1, -1, -1, -1}};

    char jogada[3];
    // int validPlay = 1;

    client_server_udp *me = new client_server_udp("192.168.0.44", 31112);
    *me->startGame();

    while(true)
    {
        // std::cin.clear();
        // fflush(stdin);
        // std::cin >> jogada;
        
        // while(!me->fazerJogada(jogada))
        // {
        //     std::cout << "Jogada Inválida, jogue novamente !" << std::endl;
        //     std::cin.clear();
        //     fflush(stdin);
        //     std::cin >> jogada;
        // }
        me->fazerJogada();
        //me->imprimeMatriz();
        
        //std::cout << "Aguardando Jogada do Adversário !" << std::endl;

    }

    return 0;
}
