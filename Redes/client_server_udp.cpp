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

        std::cout << "Enviado Hello !\n"; 
        sendto(sockfd, (char*)menssage, strlen(menssage)+1, MSG_CONFIRM, (struct sockaddr*)&addrDest, sizeof(addrDest));
        std::cout << "Hello Enviado.\n";

        std::cout << "Aguardando O Eco do Hello.\n";
        tv.tv_sec = 1;
        tv.tv_usec = 0;        
        setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv));
        
        socklen_t len;
        int n = 0;
        n = recvfrom(sockfd, &buffer, 512, MSG_WAITALL, (struct sockaddr*)&addrDest, &len);
        
        if(n > 0)
        {
            isServ = false;
            std::cout << "Eu devo ser Cliente.\n";
        }
        else
        {
            isServ = true;
            std::cout << "Eu devo ser Servidor.\n";
            tv.tv_sec = 0;
            tv.tv_usec = 0;
            setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv));
            std::cout << "Aguardando Jogador.\n";
            n = recvfrom(sockfd, &buffer, 512, MSG_WAITALL, (struct sockaddr*)&addrDest, &len);
            std::cout << "Jogador Encontrando.\n";
            sendto(sockfd, (char*)menssage, strlen(menssage)+1, MSG_CONFIRM, (struct sockaddr*)&addrDest, sizeof(addrDest));

        }
        
        // if(bindResult < 0)
        // {
        //     myStatus = 0;
        //     std::cout << "Eu sou cliente.\n";
        //     // Entao eu devo começar sendo cliente
            
        //     addrMe.sin_port = htons(50001);
        //     bindResult = bind(sockfd, (struct sockaddr*)&addrMe, sizeof(addrMe));
        //     if(bindResult < 0)
        //         std::cout << "Error Bind.\n";
        //     std::cout << "Aguardando Conexão com o Servidor...\n";
        //     addrDest.sin_family = AF_INET;
        //     addrDest.sin_port = htons(port);
        //     addrDest.sin_addr.s_addr = INADDR_ANY;

        //     socklen_t len;
        //     int n = sendto(sockfd, (char*)menssage, strlen(menssage) + 1, MSG_CONFIRM, (struct sockaddr*)&addrDest, sizeof(addrDest));            
        //     n = recvfrom(sockfd, &buffer, 512, MSG_WAITALL, (struct sockaddr*)&addrDest, &len);
        //     if(n > 0)
        //         std::cout << buffer << std::endl;
        //     if(*buffer == *menssage)            
        //         std::cout << "Conexão realizada com sucesso.\n";
        // }
        // else
        // {
        //     myStatus = 1;
        //     std::cout << "Eu sou Servidor.\n";
        //     // Entao eu devo começar sendo servidor

        //     int bindResult = bind(sockfd, (struct sockaddr*)&addrMe, sizeof(addrMe));
        //     std::cout << "Aguardando Conexão com o Cliente...\n";
        //     socklen_t len;
        //     int n = 0;    
        //     n = recvfrom(sockfd, &buffer, 512, MSG_WAITALL, (struct sockaddr*)&addrDest, &len);
        //     if(n > 0)
        //         std::cout << buffer << std::endl;
        //     if(*buffer == *menssage)            
        //         std::cout << "Conexão realizada com sucesso.\n";
            
        //     addrDest.sin_family = AF_INET;
        //     addrDest.sin_port = htons(50001);
        //     addrDest.sin_addr.s_addr = INADDR_ANY;
        //     sendto(sockfd, (char*)menssage, strlen(menssage), MSG_CONFIRM, (struct sockaddr*)&addrDest, sizeof(addrDest));            
        // }
    } 

    char* client_server_udp::fazerJogada(char *jogada, int *validPlay)
    {
        // if(myStatus == 1)
        // {
        //     std::cout << "Fazendo Jogada" << std::endl;
        //     std::cin >> jogada;
        //     sendto(sockfd, (char*)jogada, strlen(jogada), MSG_CONFIRM, (struct sockaddr*)&addrDest, sizeof(addrDest));
        //     socklen_t len;
        //     int n = 0;   
        //     std::cout << "Aguarde a jogada do adversário." << std::endl; 
        //     n = recvfrom(sockfd, &buffer, 512, MSG_WAITALL, (struct sockaddr*)&addrDest, &len);
        //     if(buffer[2] == jogada[0] && buffer[3] == jogada[1])
        //     {
        //         std::cout << "Jogada Válida." << std::endl;
        //         *validPlay = 1;
        //         if(n > 0)
        //             return buffer;
        //     }
        //     else
        //     {
        //         *validPlay = 0;
        //         return buffer;
        //     }
            
        // }
        // else
        // {
        //     socklen_t len;
        //     int n = 0;
        //     std::cout << "Aguarde a jogada do adversário." << std::endl;    
        //     n = recvfrom(sockfd, &buffer, 512, MSG_WAITALL, (struct sockaddr*)&addrDest, &len);
            
        //     std::cout << "Fazendo Jogada" << std::endl;
        //     std::cin >> jogada;
        //     while(jogada[0] == buffer[0] && jogada[1] == buffer[1])
        //     {
        //         std::cout << "Jogada Não Permitida." << std::endl;
        //         std::cin >> jogada;
        //     }
        //     sendto(sockfd, (char*)strcat(jogada, buffer), strlen(jogada) + strlen(buffer), MSG_CONFIRM, (struct sockaddr*)&addrDest, sizeof(addrDest));
        //     if(n > 0)
        //         return jogada;        
        // }
    }
}