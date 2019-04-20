#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h> 
#include <unistd.h> 

int main(int argc, char const *argv[])
{
    //char buffer[512];
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    // /std::string menssage = "ola";

    if( sockfd < 0 )
    {
        std::cout << "Não foi possível criar o socket.\n";
        return sockfd;
    }

    sockaddr_in serv;
    memset(&serv, 0, sizeof(serv));

    serv.sin_port = htons(50000);
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;

    //int bindResult = bind(sockfd, (struct sockaddr*)&serv, sizeof(serv));
    //std::cout << bindResult << std::endl;
    // int bindReuslt = bind(sockfd, (struct sockaddr*)&serv, sizeof(serv));
    
    // if( bindReuslt < 0 )
    // {
    //     std::cout << "Não foi possível nomear o socket.\n";
    //     return bindReuslt;
    // }
    char *menssage = (char*)argv[1]; 
    int n = sendto(sockfd, (char*)menssage, strlen(menssage)+1, MSG_CONFIRM, (struct sockaddr*)&serv, sizeof(serv));
    std::cout << n << std::endl;
    close(sockfd);
    
    return 0;
}
