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

    client_server_udp *me = new client_server_udp("192.168.0.44", 21112);
    *me->startGame();

    while(true)
    {
        if(me->fazerJogada() == 1)
            *me->startGame();
    }

    return 0;
}
