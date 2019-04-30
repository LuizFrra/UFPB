#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h> 

int main(int argc, char const *argv[])
{
    char buffer[512];
    //std::string buffer;
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if( sockfd < 0 )
    {
        std::cout << "Não foi possível criar o socket.\n";
        return sockfd;
    }

    sockaddr_in client, serv;
    memset(&client, 0, sizeof(client));
    memset(&serv, 0, sizeof(serv));

    serv.sin_port = htons(50000);
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;

    int bindReuslt = bind(sockfd, (struct sockaddr*)&serv, sizeof(serv));
    
    if( bindReuslt < 0 )
    {
        std::cout << "Não foi possível nomear o socket.\n";
        return bindReuslt;
    }
    timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv));
    socklen_t len;
    int n = 0;
    std::cout << "Aguardando mensagem .... \n";
    while(1)
    {
        std::cout << "loop start\n";
        n = recvfrom(sockfd, &buffer, 512, MSG_WAITALL, (struct sockaddr*)&client, &len);
        if(n > 0)
            std::cout << buffer << client.sin_port << std::endl;
        std::cout << "loop end\n";
    }
    close(sockfd);
    /* code */
    return 0;
}
