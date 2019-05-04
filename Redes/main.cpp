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

    client_server_udp *me = new client_server_udp("192.168.0.50", 21112);
    me->startGame();

    while(true)
    {
        if(me->fazerJogada() == 1)
        {
            std::cout << "\n\n\n\n\n\n\n" << std::endl;
            me->startGame();
        }
    }

    return 0;
}
