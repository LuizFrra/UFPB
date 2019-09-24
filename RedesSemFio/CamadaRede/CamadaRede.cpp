#include "CamadaRede.hpp"
#include "../CamadaEnlace/CamadaEnlace.hpp"
#include "../Hospedeiro/Hospedeiro.hpp"
#include <iostream>
#include <iomanip>
//#include "../TabelaRoteamento/TabelaRoteamento.cpp"

CamadaRede::CamadaRede(Hospedeiro *hospedeiro)
{
    this->hospedeiro = hospedeiro;
    PacoteID = 1;
    
    tabelaRoteamento = new TabelaRoteamento(hospedeiro->PegarEnderecoMac());
}
    
void CamadaRede::DefinirCamadaDeBaixo(CamadaEnlace *camadaEnlace)
{
    this->camadaEnlace = camadaEnlace;
}

void CamadaRede::EnviarMensagem(Pacote pacote)
{
    pacote.AdicionarUID(PacoteID);
    //ImprimirMac(pacote.GetOrigem());
    PacoteID++;
    auto EnderecoMacDestino = pacote.GetDestino();

    if(tabelaRoteamento->VerificarSeExisteRotaParaDestino(EnderecoMacDestino))
    {
        //std::cout << "Oi";
        pacote.AdicionarNext(tabelaRoteamento->ObterNextPara(EnderecoMacDestino));
        camadaEnlace->AdicionarPacoteParaEnvio(pacote);
    }
    else
    {
        // Nessa condição Não há um caminho para o pacote e o memso ira ficar em espera ate que seja encontrada
        PacotesAguardandoRota.push_back(pacote);
        Pacote pacoteRREQ = Pacote(hospedeiro->PegarEnderecoMac(), pacote.GetDestino(), TipoPacote::RREQ, PacoteID);
        pacoteRREQ.AdicionarCaminho(hospedeiro->PegarEnderecoMac());
        PacoteID++;
        camadaEnlace->AdicionarPacoteParaEnvio(pacoteRREQ);
    }
}

void CamadaRede::ReceberPacoteCamadaEnlance(Pacote pacote)
{
    auto destinoPacote = pacote.GetDestino();
    auto tipoPacote = pacote.GetTipoPacote();
    auto macHospedeiro = hospedeiro->PegarEnderecoMac();
    // Verifica se ta recebendo um pacote enviado por ele mesmo e return
    if(pacote.GetOrigem() == hospedeiro->PegarEnderecoMac())
        return;

    // Pega as informacoes do pacote como origem e identificador para verificar se ja foi recebido posteriormente
    std::pair<uint, std::vector<int>> DadosPacote = std::make_pair(pacote.GetIdentificador(), pacote.GetOrigem());
    
    // Procura se ja recebeu um pacote com mesmo identificador e com mesma origem
    auto itPacotesRecebidos = std::find(PacotesRecebidos.begin(), PacotesRecebidos.end(), DadosPacote);

    // Caso tenha recebido ignora, caso contrario adiciona na lista de pacotes recebidos
    if(itPacotesRecebidos != PacotesRecebidos.end())
    {
        std::cout << "Pacote : " << pacote.GetIdentificador() << " Originado de : ";
        ImprimirMac(pacote.GetOrigem());
        std::cout << " ||| Ja Passou Aqui : ";
        ImprimirMac(macHospedeiro);
        std::cout << "\n";
        return;
    }
    else
    {
        PacotesRecebidos.push_back(DadosPacote);
    }

    std::cout << "Pacote Originado em : ";
    ImprimirMac(pacote.GetOrigem());
    std::cout << " Passou por mim : ";
    ImprimirMac(hospedeiro->PegarEnderecoMac());
    std::cout << "\n";
    
    //std::cout << "vamo";
    if(tipoPacote == TipoPacote::DATA && destinoPacote == macHospedeiro)
    {
        std::cout << "\n\n\n Mensagem Recebida : ";
        std::cout << "\n\n Enviada Por : ";
        ImprimirMac(pacote.GetOrigem());
        std::cout << "\n\n Para : ";
        ImprimirMac(pacote.GetDestino());
        std::cout << "\n\n";
        // Pacote com dados, Pegar o dado e imprime
        // RESPONDER PACOTE COM ACK
        std::cout << pacote.GetDados(macHospedeiro) << "\n";
        //std::cout << "Eu Sou o Destino";
    }
    else if(tipoPacote == TipoPacote::DATA && destinoPacote != macHospedeiro)
    {
        if(tabelaRoteamento->VerificarSeExisteRotaParaDestino(pacote.GetDestino()))
        {
            pacote.AdicionarNext(tabelaRoteamento->ObterNextPara(pacote.GetDestino()));
            camadaEnlace->AdicionarPacoteParaEnvio(pacote);
        }
        else
        {
            PacotesAguardandoRota.push_back(pacote);
            Pacote pacoteRREQ = Pacote(hospedeiro->PegarEnderecoMac(), pacote.GetDestino(), TipoPacote::RREQ, PacoteID);
            pacoteRREQ.AdicionarCaminho(hospedeiro->PegarEnderecoMac());
            PacoteID++;
            camadaEnlace->AdicionarPacoteParaEnvio(pacoteRREQ);
        }
        
    }
    else if(tipoPacote == TipoPacote::RREQ && macHospedeiro != destinoPacote)
    {
        // Pacote de Route Request porem não é destino
        // Adicionar a assinatura ao pacote e reenvia o mesmo
        std::cout << "Nao sou o destino : ";
        ImprimirMac(pacote.GetDestino());
        std::cout << " Reencaminhando Pacote para Vizinhos \n";
        pacote.AdicionarCaminho(hospedeiro->PegarEnderecoMac());
        camadaEnlace->AdicionarPacoteParaEnvio(pacote);
    }
    else if(tipoPacote == TipoPacote::RREQ && macHospedeiro == destinoPacote)
    {
        std::cout << "Eu Sou o Destino : ";
        ImprimirMac(macHospedeiro);
        std::cout << "\n";
        // Pacote de Route Request porém é Destino
        // Pega o caminho do pacote, E inverte o Mesmo
        pacote.AdicionarCaminho(macHospedeiro);
        auto pacoteCaminho = pacote.PegarCaminho();
        std::cout << "Esse pacote Passou por : \n";
        Pacote pacoteRespostaRREP = Pacote(macHospedeiro, pacote.GetOrigem(), TipoPacote::RREP, PacoteID);
        PacoteID++;
        for(auto it = pacoteCaminho.rbegin(); it != pacoteCaminho.rend(); ++it)
        {      
                ImprimirMac(*it);
                pacoteRespostaRREP.AdicionarCaminho(*it);
                std::cout << "\n";
        }
        std::cout << "Ate Chegar Aqui\n\n";
        // Ver Se Consegue alcancar o Ultimo que envio para mim, estará na posicao 1
        auto possivelVizinho = pacoteRespostaRREP.PegarCaminho().at(1);
        auto vizinhoAlcancavel = hospedeiro->AlcancoMac(possivelVizinho);

        if(vizinhoAlcancavel)
        {
            tabelaRoteamento->AprenderRoteamento(pacoteRespostaRREP.PegarCaminho());
            
            if(tabelaRoteamento->VerificarSeExisteRotaParaDestino(possivelVizinho))
            {
                pacoteRespostaRREP.AdicionarNext(tabelaRoteamento->ObterNextPara(possivelVizinho));
                camadaEnlace->AdicionarPacoteParaEnvio(pacoteRespostaRREP);
                // Iterar sob os pacotes aguardando espera para ver se tem caminho e enviar
            }
        }else
        {
            PacotesAguardandoRota.push_back(pacoteRespostaRREP);
            Pacote pacoteRREQ = Pacote(macHospedeiro, pacote.GetOrigem(), TipoPacote::RREP, PacoteID);
            PacoteID++;
            camadaEnlace->AdicionarPacoteParaEnvio(pacoteRREQ);
        }
    }else if(tipoPacote == TipoPacote::RREP && macHospedeiro != pacote.GetDestino())
    {
        int posicaoOrigem = 0;
        //std::cout << pacote.PegarCaminho().size();
        auto caminho = pacote.PegarCaminho();
        for(auto iterador = caminho.begin(); iterador != caminho.end(); ++iterador)
        {
            if(macHospedeiro == *iterador)
                break;
            //ImprimirMac(*iterador);
            posicaoOrigem++;
        }
        // Nao faço a minima ideia do que acontece aqui -- debugar
        if(posicaoOrigem >= caminho.size()) posicaoOrigem = posicaoOrigem - 2;
        //std::cout << pacote.PegarCaminho().size() << "\n\n";
        auto possivelVizinho = pacote.PegarCaminho().at(posicaoOrigem + 1);
        auto vizinhoAlcancavel = hospedeiro->AlcancoMac(possivelVizinho);
        if(vizinhoAlcancavel)
        {
            //std::cout << "aqui";
            tabelaRoteamento->AprenderRoteamento(caminho);
            //std::cout << "aqui\n\n\n";
            if(tabelaRoteamento->VerificarSeExisteRotaParaDestino(possivelVizinho))
            {
                pacote.AdicionarNext(tabelaRoteamento->ObterNextPara(possivelVizinho));
                camadaEnlace->AdicionarPacoteParaEnvio(pacote);
                // Iterar sob os pacotes aguardando espera para ver se tem caminho e enviar
            }
        }else
        {
            PacotesAguardandoRota.push_back(pacote);
            Pacote pacoteRREQ = Pacote(macHospedeiro, pacote.GetOrigem(), TipoPacote::RREP, PacoteID);
            PacoteID++;
            camadaEnlace->AdicionarPacoteParaEnvio(pacoteRREQ);
        }
    }else if(tipoPacote == TipoPacote::RREP && macHospedeiro == pacote.GetDestino())
    {
        std::cout << "O Pacote de Route Reply Originado por : ";
        ImprimirMac(pacote.GetOrigem());
        std::cout << " Chegou Ao Destino : ";
        ImprimirMac(macHospedeiro);
        std::cout << "\n";
        auto caminho = pacote.PegarCaminho();
        tabelaRoteamento->AprenderRoteamento(caminho);
    }
    
    int numPacotesAguardandoRota = PacotesAguardandoRota.size();
    for(int i = numPacotesAguardandoRota - 1; i >= 0; i--)
    {
        Pacote pacoteAguardandoRota = PacotesAguardandoRota.at(i);
        //ImprimirMac(pacoteAguardandoRota.GetDestino());
        if(tabelaRoteamento->VerificarSeExisteRotaParaDestino(pacoteAguardandoRota.GetDestino()))
        {
            //std::cout << numPacotesAguardandoRota << "\n";
            pacoteAguardandoRota.AdicionarNext(tabelaRoteamento->ObterNextPara(pacoteAguardandoRota.GetDestino()));
            camadaEnlace->AdicionarPacoteParaEnvio(pacoteAguardandoRota);
            PacotesAguardandoRota.pop_back();
            numPacotesAguardandoRota = PacotesAguardandoRota.size();
        }
    }
    //std::cout << numPacotesAguardandoRota << "\n";
}

void CamadaRede::ImprimirMac(std::vector<int> vetorMac)
{
    for(auto it2 = vetorMac.begin(); it2 != vetorMac.end(); ++it2)
    {
        std::cout << std::hex << std::setw(4) << std::uppercase <<  *it2;
    }
}

CamadaRede::~CamadaRede()
{

}