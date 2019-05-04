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
        char matriz[9];
        timeval tv;
        int jogoDaVelha[4][4];
        /* data */
    public:
        client_server_udp(/* args */);
        client_server_udp(const char *ip, const int port);
        int gameFuncionality(char *code);
        void startGame(/*char *jogada, int *validPlay*/);
        void sendMenssage(char *menssage);
        char* receiveMenssage();
        int imprimeMatriz();
        char* matrizToChar();
        bool validPLay(char *jogada);
        bool positionPlayed(int row, int column);
        int fazerJogada();
        void changeMatriz(int value, char* jogada);
        bool validateRound();
        int checkWinnerTable();
        bool checkWinner();
    };
}


#endif
