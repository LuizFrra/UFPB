#ifndef HOSPEDEIRO_H_
#define HOSPEDEIRO_H_
#include <stdint.h>
#include <list>
#include "../Pacote/Pacote.hpp"

class CamadaRede;
class CamadaEnlace;
class CamadaFisica;
class Coordenador;

class Hospedeiro
{

private:
    Coordenador *coordenador;

    // Endereco da placa de rede *Numero Unico*
    std::vector<int> EnderecoMac;

    // Variavel que armazenada a Coordenada X do Hospedeiro
    uint CoordenadaX;

    // Variavel que armazenada a Coordenada Y do Hospedeiro
    uint CoordenadaY;

    // Variavel que define o Alcance do Hospedeiro
    uint Alcance;

    // Camada de Rede Do Hospedeiro
    CamadaRede *camadaRede;

    // Camada de Enlance Do Hospedeiro
    CamadaEnlace *camadaEnlace;

    // Camada Fisica do Hospedeiro
    CamadaFisica *camadaFisica;
    
    // Contém todas as mensagem que o Hospedeiro deseja enviar, primeira chave da pair contém a mensagem e a segunda destino
    // std::vector<std::pair<std::string, std::vector<int>>> MensagensParaEnviar;

public:
    Hospedeiro(std::vector<int> EnderecoMac, uint CoordenadaX, uint CoordenadaY, uint Alcance, Coordenador *coordenador);
    void EnviarMensagem(std::string mensagem, std::vector<int> Destino);
    std::vector<int> PegarEnderecoMac();
    bool IsRecheable(std::pair<uint, uint> Coordenadas);
    std::pair<uint, uint> PegarCoordenadas();
    void EntrarNaFilaCoordenador();
    void EnviarPacoteParaVizinho();
    std::list<Hospedeiro*> ObterHospedeiros();
    CamadaFisica* PegarCamadaFisica();
    void ImprimirMac(std::vector<int> vetorMac);
    bool AlcancoMac(std::vector<int> vetorMac);
    ~Hospedeiro();

};

#endif

