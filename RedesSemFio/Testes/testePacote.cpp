#include "../Pacote/Pacote.hpp"
#include <iostream>

int main(int argc, char const *argv[])
{
    /* code */
    uint8 Origem[4] = {192, 168, 0, 1};
    uint8 Destino[4] = {192, 168, 0, 2};
    std::string Dados = "ola luiz";
    
    // Criando um pacote
    Pacote *pacote = new Pacote(Origem, Destino, (uint8)15, Dados);
    
    // Verificando se o CheckSum Bate
    if( pacote->ChecarCheckSum() )
        std::cout << "Ok" << std::endl;
    
    // Acessando o terceiro byte do Ip Destino
    std::cout << pacote->GetDestino()[2] * 1;

    return 0;
}
