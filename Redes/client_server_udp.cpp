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
            tv.tv_sec = 0;
            tv.tv_usec = 0;
            setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv));
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

    char* client_server_udp::startGame(/*char *jogada, int *validPlay*/)
    {
        if(isServ)
        {
            sendMenssage("91");
            receiveMenssage();
            imprimeMatriz();
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
            std::cout << "Preparando a Matriz.\n";
            memset(jogoDaVelha, -1, sizeof(jogoDaVelha) * 4 * 4);
            std::cout << "Matriz Preparada.\n";
        }

        if(code[1] == '2')
        {
            std::cout << "As Matrizes não batem, o jogo precisa ser reinciado." << std::endl;
            memset(jogoDaVelha, -1, sizeof(jogoDaVelha) * 4 * 4);
            isServ = !isServ;
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
        return 0;
    }

    char* client_server_udp::matrizToChar()
    {
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                if(jogoDaVelha[i + 1][j + 1] == -1)
                    matriz[i * 3 + j] = '2';
                
                else if(jogoDaVelha[i + 1][j + 1] == 1)
                    matriz[i * 3 + j] = '1';
                
                else if(jogoDaVelha[i + 1][j + 1] == 0)
                    matriz[i * 3 + j] = '0';
            }
        }
        return matriz;        
    }

    bool client_server_udp::validPLay(char *jogada)
    {
        if(!isdigit(jogada[0]) || !isdigit(jogada[1]) && !(jogada[0] - 48 <= 3 && jogada[1] - 48 <= 3))
            return false;

        if(jogoDaVelha[jogada[0] - 48][jogada[1] - 48] == -1)
            return true;

        return false;
    }

    int client_server_udp::fazerJogada()
    {
        if(isServ)
        {
            //validateRound();
            char jogada[3];
            std::cin.clear();
            fflush(stdin);
            std::cout << "Faça sua Jogada" << std::endl;
            std::cin >> jogada;
            while(!validPLay(jogada))
            {
                std::cout << "Jogada Inválida, jogue novamente !" << std::endl;
                std::cin.clear();
                fflush(stdin);
                std::cin >> jogada;
            }
            sendMenssage(jogada);
            changeMatriz(1, jogada);
            imprimeMatriz();
            if(checkWinner())
                return 1;
            std::cout << "Aguardando a jogada do adversário." << std::endl;
            receiveMenssage();
            changeMatriz(0, buffer);
            imprimeMatriz();
            if(checkWinner())
                return 1;
            validateRound();
        }
        else
        {

            std::cout << "Aguardando a jogada do adversário." << std::endl;
            receiveMenssage();
            changeMatriz(1, buffer);
            imprimeMatriz();
            if(checkWinner())
                return 1;
            char jogada[3];
            std::cin.clear();
            fflush(stdin);
            std::cout << "Faça sua Jogada" << std::endl;
            std::cin >> jogada;
            while(!validPLay(jogada))
            {
                std::cout << "Jogada Inválida, jogue novamente !" << std::endl;
                std::cin.clear();
                fflush(stdin);
                std::cin >> jogada;
            }
            sendMenssage(jogada);
            changeMatriz(0, jogada);
            imprimeMatriz();
            if(checkWinner())
                return 1;
            validateRound();
        }
        return 0;
    }

    void client_server_udp::changeMatriz(int value, char* jogada)
    {
        jogoDaVelha[jogada[0] - 48][jogada[1] - 48] = value;
    }

    bool client_server_udp::validateRound()
    {
        if(isServ)
        {
            sendMenssage(matrizToChar());
            receiveMenssage();
            if(strcmp(buffer, matriz) == 0)
                return true;
            sendMenssage("92");
            receiveMenssage();
        }
        else
        {
            receiveMenssage();
            sendMenssage(matrizToChar());
            if(strcmp(buffer, matriz) == 0)
                return true;
            receiveMenssage();
            sendMenssage("92");
        }
        
    }



    bool client_server_udp::checkWinner()
    {
        int w = checkWinner();
        if( w != 2)
        {
            if((w == 1 && isServ) || (w == 0 && !isServ))
                std::cout << "Parabéns você ganhou !" << std::endl;
            else
                std::cout << "O Adversário ganhou seu merda !" << std::endl;
            
            isServ = !isServ;
            memset(jogoDaVelha, -1, sizeof(jogoDaVelha) * 4 * 4);
            return true;
        }
        return false;
    }





    int client_server_udp::checkWinnerTable()
    {
        if((jogoDaVelha[1][1] == 1) && (jogoDaVelha[1][2] == 1) && (jogoDaVelha[1][3] == 1))
            return 1;

        if((jogoDaVelha[2][1] == 1) && (jogoDaVelha[2][2] == 1) && (jogoDaVelha[2][3] == 1))
            return 1;

        if((jogoDaVelha[3][1] == 1) && (jogoDaVelha[3][2] == 1) && (jogoDaVelha[3][3] == 1))
            return 1;

        if((jogoDaVelha[1][1] == 1) && (jogoDaVelha[2][1] == 1) && (jogoDaVelha[3][1] == 1))
            return 1;

        if((jogoDaVelha[1][2] == 1) && (jogoDaVelha[2][2] == 1) && (jogoDaVelha[3][2] == 1))
            return 1;

        if((jogoDaVelha[1][3] == 1) && (jogoDaVelha[2][3] == 1) && (jogoDaVelha[3][3] == 1))
            return 1;

        if((jogoDaVelha[1][1] == 1) && (jogoDaVelha[2][2] == 1) && (jogoDaVelha[3][3] == 1))
            return 1;

        if((jogoDaVelha[1][3] == 1) && (jogoDaVelha[2][2] == 1) && (jogoDaVelha[3][1] == 1))
            return 1;

        //Condições para jogador 2 ganhar

        if((jogoDaVelha[1][1] == 0) && (jogoDaVelha[1][2] == 0) && (jogoDaVelha[1][3] == 0))
            return 0;

        if((jogoDaVelha[2][1] == 0) && (jogoDaVelha[2][2] == 0) && (jogoDaVelha[2][3] == 0))
            return 0;

        if((jogoDaVelha[3][1] == 0) && (jogoDaVelha[3][2] == 0) && (jogoDaVelha[3][3] == 0))
            return 0;

        if((jogoDaVelha[1][1] == 0) && (jogoDaVelha[2][1] == 0) && (jogoDaVelha[3][1] == 0))
            return 0;

        if((jogoDaVelha[1][2] == 0) && (jogoDaVelha[2][2] == 0) && (jogoDaVelha[3][2] == 0))
            return 0;

        if((jogoDaVelha[1][3] == 0) && (jogoDaVelha[2][3] == 0) && (jogoDaVelha[3][3] == 0))
            return 0;

        if((jogoDaVelha[1][1] == 0) && (jogoDaVelha[2][2] == 0) && (jogoDaVelha[3][3] == 0))
            return 0;

        if((jogoDaVelha[1][3] == 0) && (jogoDaVelha[2][2] == 0) && (jogoDaVelha[3][1] == 0))
            return 0;
        
        //ninguem ganhou
        return 2;
    }
}