#include "client_server_udp.h"
#include <sys/socket.h>
#include <sys/time.h>
#include <string.h>
#include <string>
#include <arpa/inet.h>

namespace CLIENT_SERVER_UDP
{
    client_server_udp::client_server_udp(/* args */)
    {

    }

    client_server_udp::client_server_udp(const char *ip, const int port)
    {
        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        char *menssage = "Hi"; 

        if(sockfd < 0)
            std::cout << "Não Foi Possível criar o Socket\n";

        memset(&addrMe, 0, sizeof(addrMe));
        memset(&addrDest, 0, sizeof(addrDest));

        addrMe.sin_family = AF_INET;
        addrMe.sin_port = htons(port);
        addrMe.sin_addr.s_addr = INADDR_ANY;
        int bindResult = bind(sockfd, (struct sockaddr*)&addrMe, sizeof(addrMe));

        addrDest.sin_family = AF_INET;
        addrDest.sin_port = htons(port);
        addrDest.sin_addr.s_addr = inet_addr(ip); 

        std::cout << "Buscando Jogadores.\n"; 
        sendto(sockfd, (char*)menssage, strlen(menssage)+1, MSG_CONFIRM, (struct sockaddr*)&addrDest, sizeof(addrDest));
        //std::cout << "Hello Enviado.\n";

        std::cout << "Aguardando...\n";
        tv.tv_sec = 1;
        tv.tv_usec = 0;        
        setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv));
        
        socklen_t len;
        int n = 0;
        n = recvfrom(sockfd, &buffer, 512, MSG_WAITALL, (struct sockaddr*)&addrDest, &len);
        
        if(n > 0)
        {
            std::cout << "Jogador Encontrando.\n";
            isServ = false;
        }
        else
        {
            isServ = true;
            tv.tv_sec = 0;
            tv.tv_usec = 0;
            setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv));
            //std::cout << "Aguardando Jogador.\n";
            n = recvfrom(sockfd, &buffer, 512, MSG_WAITALL, (struct sockaddr*)&addrDest, &len);
            std::cout << "Jogador Encontrando.\n";
            sendto(sockfd, (char*)menssage, strlen(menssage)+1, MSG_CONFIRM, (struct sockaddr*)&addrDest, sizeof(addrDest));

        }          
    } 

    char* client_server_udp::sendMenssage(char *menssage)
    {
        sendto(sockfd, (char*)menssage, strlen(menssage)+1, MSG_CONFIRM, (struct sockaddr*)&addrDest, sizeof(addrDest));
    }

    char* client_server_udp::receiveMenssage()
    {
        socklen_t len;
        int n = 0;
        recvfrom(sockfd, &buffer, 512, MSG_WAITALL, (struct sockaddr*)&addrDest, &len);

        if(buffer[0] == '9')
            gameFuncionality(buffer);

        return buffer;
    }

    char* client_server_udp::fazerJogada(/*char *jogada, int *validPlay*/)
    {
        if(isServ)
        {
            sendMenssage("91");
            receiveMenssage();
            imprimeMatriz()
        }
        else
        {
            receiveMenssage();
            sendMenssage("91");
            imprimeMatriz();
        }
    }

    int client_server_udp::gameFuncionality(char *code)
    {
        
        if(code[1] == '1')
        {
            std::cout << "Preparando Jogo.\n";
            memset(&jogoDaVelha, -1, sizeof(jogoDaVelha));
        }
        return 0;
    }

    int client_server_udp::imprimeMatriz()
    {
        for(int i = 1; i < 4; i++)
        {
            for(int j = 1; j < 4; j++)
            {
                std::cout << jogoDaVelha[i][j] << " | ";
            }
            std::cout << std::endl;
        }
    }
}