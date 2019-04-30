#ifndef CLIENT_SERVER_UDP_H
#define CLIENT_SERVER_UDP_H

#include <iostream>
#include <netinet/in.h>

namespace CLIENT_SERVER_UDP{
    
    class client_server_udp
    {
    private:
        int sockfd;
        sockaddr_in addrMe;
        sockaddr_in addrDest;
        char buffer[512];
        bool isServ;
        timeval tv;
        int jogoDaVelha[4][4];
        /* data */
    public:
        client_server_udp(/* args */);
        client_server_udp(const char *ip, const int port);
        int gameFuncionality(char *code);
        char* fazerJogada(/*char *jogada, int *validPlay*/);
        char* sendMenssage(char *menssage);
        char* receiveMenssage();
        int imprimeMatriz();
        //bool connectTo(const std::string addrress, int port);
        //int beServer();
        //int beClient(const std::string menssage);
        //~client_server_udp();
    };
}


#endif
