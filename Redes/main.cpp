#include "client_server_udp.h"

using namespace CLIENT_SERVER_UDP;

int main(int argc, char const *argv[])
{
    int jogoDaVelha[4][4] = {{-1, -1, -1, -1},
                            {-1, -1, -1, -1},
                            {-1, -1, -1, -1},
                            {-1, -1, -1, -1}};

    char jogada[2];
    int validPlay = 1;

    client_server_udp *me = new client_server_udp(50000);

    while(validPlay)
    {
        char *menssage = me->fazerJogada((char*)jogada, &validPlay);
        std::cout << menssage << std::endl;
        
        jogoDaVelha[int(menssage[0]) - 48][int(menssage[1]) - 48] = 0;
        jogoDaVelha[int(menssage[2]) - 48][int(menssage[3]) - 48] = 1;             
        
        for(int i = 1; i < 4; i++)
        {
            for(int j = 1; j < 4; j++)
            {
                std::cout << " | " << jogoDaVelha[i][j];
            }
            std::cout << std::endl;
        }
    }
    return 0;
}
