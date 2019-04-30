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
        /* data */
    public:
        client_server_udp(/* args */);
        client_server_udp(const char *ip, const int port);
        char* fazerJogada(char *jogada, int *validPlay);
        int myStatus;
        //bool connectTo(const std::string addrress, int port);
        //int beServer();
        //int beClient(const std::string menssage);
        //~client_server_udp();
    };
}


#endif
