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

Pacote CamadaRede::CriarPacoteRREPPara(Pacote pacoteRREQ)
{
    Pacote pacoteRREP = Pacote(hospedeiro->PegarEnderecoMac(), pacoteRREQ.GetOrigem(), TipoPacote::RREP, PacoteID);
    PacoteID++;
    
    auto caminhoRREQ = pacoteRREQ.PegarCaminho();
    std::reverse(caminhoRREQ.begin(), caminhoRREQ.end());
    for(auto it = caminhoRREQ.begin(); it != caminhoRREQ.end(); ++it)
    {
        pacoteRREP.AdicionarCaminho(*it);
    }

    return pacoteRREP;
}

void CamadaRede::CriarPacoteRREQPara(Pacote pacote)
{
    PacotesAguardandoRota.push_back(pacote);
    Pacote pacoteRREQ = Pacote(hospedeiro->PegarEnderecoMac(), pacote.GetDestino(), TipoPacote::RREQ, PacoteID);
    PacoteID++;
    pacoteRREQ.AdicionarCaminho(hospedeiro->PegarEnderecoMac());
    camadaEnlace->AdicionarPacoteParaEnvio(pacoteRREQ);
}

bool CamadaRede::AdicionarDestinoAoPacote(Pacote &pacote)
{
    pacote.AdicionarCaminho(hospedeiro->PegarEnderecoMac());

    return true;
}

bool CamadaRede::AdicionarPacoteAosRecebidos(Pacote pacote)
{
    auto pacoteIdentificacao = std::make_pair(pacote.GetIdentificador(), pacote.GetOrigem());
    auto iteradorPacotesRecebidos = std::find(PacotesRecebidos.begin(), PacotesRecebidos.end(), pacoteIdentificacao);

    if(iteradorPacotesRecebidos != PacotesRecebidos.end())
        return false;

    PacotesRecebidos.push_back(pacoteIdentificacao);
    return true;
}

void CamadaRede::EnviarMensagem(Pacote pacote)
{
    pacote.AdicionarUID(PacoteID);
    PacoteID++;
    //ImprimirMac(pacote.GetOrigem());
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
        // Portanto é criado um pacote RREQ para se descobrir uma rota
        CriarPacoteRREQPara(pacote);
    }
}

void CamadaRede::ReceberPacoteCamadaEnlance(Pacote pacote)
{
    // Obtem principais dados do pacote
    auto destinoPacote = pacote.GetDestino();
    auto tipoPacote = pacote.GetTipoPacote();
    auto pacoteFoward = pacote.GetNext();
    auto origemPacote = pacote.GetOrigem();
    auto identificadorPacote = pacote.GetIdentificador();
    // Verifica se o pacote que está chegando foi enviado pelo proprio host
    // Ele não pode receber um pacote originado por ele
    if(origemPacote == hospedeiro->PegarEnderecoMac())
        return; // Se for apenas ignora o pacote
    
    // Ignora o pacote caso seja de RREP e DATA que tem que ter next, e o next nao for para o hospedeiro atual
    if((tipoPacote == TipoPacote::RREP || tipoPacote == TipoPacote::DATA) && pacote.GetNext() != hospedeiro->PegarEnderecoMac())
       return;

    // Adiciona o pacote a lista de recebidos, caso a funcao retorne true, foi adicionado com sucesso
    // Caso retorne false, significa que é um pacote que já passou por esse hospedeiro
    if(!AdicionarPacoteAosRecebidos(pacote))
        return; // Se é um pacote antigo, apenas ignora

    if(!DEBUG)
        ImprimeInformacoesOrigemDestino(pacote, false);

    // Verifica se um pacote de Dados e o endereco de destino é o mesmo do hospedeiro atual
    if(tipoPacote == TipoPacote::DATA && destinoPacote == hospedeiro->PegarEnderecoMac())
    {
        if(DEBUG)
        {
            ImprimeInformacoesOrigemDestino(pacote, true);
            std::cout << "Abaixo Conteudo do Pacote : \n";
            std::cout << pacote.GetDados(hospedeiro->PegarEnderecoMac()) << "\n";
        }
    }
    // Caso tenha recebido um pacote de DATA em que não é destino, significa que é o next
    // Entao verifica se tem uma rota para o mesmo
    else if(tipoPacote == TipoPacote::DATA && destinoPacote != hospedeiro->PegarEnderecoMac())
    {
        if(tabelaRoteamento->VerificarSeExisteRotaParaDestino(destinoPacote))
        {
            // Se existir adiciona ao next do pacote
            pacote.AdicionarNext(tabelaRoteamento->ObterNextPara(destinoPacote));
            camadaEnlace->AdicionarPacoteParaEnvio(pacote);
        }
        // Caso não exista, criar um RREQ para o pacote
        else
        {
            pacote.AdicionarNext(std::vector<int>());
            CriarPacoteRREQPara(pacote);
        }
    }
    // Verifica se um pacote é do tipo RREQ e o Destino não é o hospedeiro atual
    else if(tipoPacote == TipoPacote::RREQ && destinoPacote != hospedeiro->PegarEnderecoMac())
    {
        if(DEBUG)
            ImprimeInformacoesOrigemDestino(pacote, false);

        // Caso afirmativo, adiciona o proprio endereco ao caminho do pacote
        pacote.AdicionarCaminho(hospedeiro->PegarEnderecoMac());
        
        // Verifica se o vizinho é alcançavel
        // Como meu possível vizinho foi adicionado antes do hospedeiro atual, sua posicao é uma antes da do hospedeiro Atual
        auto posicaoVizinho = pacote.PegarCaminho().size() - 2;
        
        // Valida a Posicao do Vizinho
        auto vizinho = posicaoVizinho < pacote.PegarCaminho().size() ? pacote.PegarCaminho().at(posicaoVizinho)
                                : std::vector<int>();
        
        // Se o Vizinho for valido, ou seja, empty retornar false e for alcançavel, a rota pode ser aprendida
        if(!vizinho.empty())
        {
            if(hospedeiro->AlcancoMac(vizinho))
            {
                tabelaRoteamento->AprenderRoteamento(pacote.PegarCaminho());
                VerificarNextPacotesEEnviar();
            }
        }
        
        // Feito isso, é possível adicionar o pacote na camada de enlance para que seja inundado
        // Como a inundacao é feita para todos os vizinhos, pode enviar diretamente
        camadaEnlace->AdicionarPacoteParaEnvio(pacote);
    }
    // Verifica se um pacote é do tipo RREQ e o Destino é o hospedeiro Atual
    else if(tipoPacote == TipoPacote::RREQ && destinoPacote == hospedeiro->PegarEnderecoMac())
    {
        if(DEBUG)
            ImprimeInformacoesOrigemDestino(pacote, true);
        // Caso afirmativo, adiciona o proprio endereco ao caminho do pacote
        pacote.AdicionarCaminho(hospedeiro->PegarEnderecoMac());
        // Pega todo o caminho do pacote ate chegar ao destino
        auto caminhoPacote = pacote.PegarCaminho();
        // Cria um pacote de RREP
        auto pacoteRREP = CriarPacoteRREPPara(pacote);
        // Verifica se consegue Alcancar o Hospedeiro Que lhe enviou este pacote, pois a rota só pode ser aprendida
        // Se quem lhe enviou o pacote for alcançavel pelo hospedeiro Atual
        // Como o caminho é invertido ao criar o RREP, o vizinho deve está na posicao 1
        auto posicaoVizinho = 1;
        
        // Verifica se a posicao do Vizinho é uma posicao valida
        auto vizinho = posicaoVizinho < caminhoPacote.size() ? pacoteRREP.PegarCaminho().at(posicaoVizinho) 
                                : std::vector<int>();
        
        if(vizinho.empty())
        {
            // Caso tenha verdadeiro, tentou acessar uma posicao que não existe
            // Portanto Apenas cria um RREQ para o pacote e o coloca na lista de espera
            // A rota Não pode ser aprendida
            pacote.AdicionarNext(std::vector<int>());
            CriarPacoteRREQPara(pacote);
            
            return;
        }
        else
        {
            // Caso seja !falso, verificar se o vizinho é alcançavel
            if(hospedeiro->AlcancoMac(vizinho))
            {
                // Aprende A Rota
                tabelaRoteamento->AprenderRoteamento(pacoteRREP.PegarCaminho());
                VerificarNextPacotesEEnviar();
                // Caso senha Alcançavel, adiciona o mesmo no NEXT  do pacote
                pacoteRREP.AdicionarNext(vizinho);
                
                //ImprimirMac(vizinho);
                // Envia o pacote para a camada De enlace
                camadaEnlace->AdicionarPacoteParaEnvio(pacoteRREP);
            }
        }
    }
    // Verifica se o Pacote é do tipo RREP e não é o Destino
    else if(tipoPacote == TipoPacote::RREP && destinoPacote != hospedeiro->PegarEnderecoMac())
    {
        if(DEBUG)
            ImprimeInformacoesOrigemDestino(pacote, false);
        // ABCD -> DCBA
        // Verifica se o endereco do hospedeiro atual está na rota e em Qual Posicao
        int posicaoHospedeiroAtual = -1, contador = 0;
        auto caminhoPacote = pacote.PegarCaminho();
        for(auto it = caminhoPacote.begin(); it != caminhoPacote.end(); ++it)
        {
            if(*it == hospedeiro->PegarEnderecoMac())
            {
                posicaoHospedeiroAtual = contador;
                break;
            }
            contador++;
        }
        // Se a posicaoHospedeiroAtual continuar negativa, significa que o mesmo não está no caminho do pacote
        // Sendo necessario criar um pacote de RREQ para o mesmo
        if(posicaoHospedeiroAtual < 0)
        {
            pacote.AdicionarNext(std::vector<int>());
            CriarPacoteRREQPara(pacote);
        }
        // Se a posicao Estiver positiva, significa que o endereco do hospedeiro atual foi encontrado, portanto se
        // encontra no caminho, agora é possivel verificar se ele alcança o seu vizinho que está na posicao +1
        // Se alcancar, pode aprender a rota, caso contrario, sera necessario um novo RREQ
        else
        {
            auto vizinho = posicaoHospedeiroAtual < caminhoPacote.size() ? caminhoPacote.at(posicaoHospedeiroAtual + 1) :
                                std::vector<int>();
            // Verifica se empty retornou false, se tiver retornado false, se tiver, verifica se o mac é alcançavel
            if(!vizinho.empty())
            {
                if(hospedeiro->AlcancoMac(vizinho))
                {
                    // se for alcançavel, aprende a rota
                    tabelaRoteamento->AprenderRoteamento(caminhoPacote);
                    VerificarNextPacotesEEnviar();
                    
                    // Coloca o Next do vizinho no pacote
                    pacote.AdicionarNext(vizinho);
                    // Envia o pacote para a camada de Enlance
                    camadaEnlace->AdicionarPacoteParaEnvio(pacote);
                }
            }
            // Se chegou ate aqui, significa que o hospedeiro atual não está no caminho deste pacote
            // Portanto deve-se criar um RREQ para o mesmo
            else
            {
                // Passar um Next vazio para o mesmo
                pacote.AdicionarNext(std::vector<int>());
            
                // Criar um Pacote do tipo RREQ, colocando o atual na lista de espera
                CriarPacoteRREQPara(pacote);
            } 
        }
    }
    // Se chegou um RREP onde o destino do mesmo é igual ao endereco do hospedeiro atual
    // basta aprender a rota 
    else if(tipoPacote == TipoPacote::RREP && destinoPacote == hospedeiro->PegarEnderecoMac())
    {
        if(DEBUG)
            ImprimeInformacoesOrigemDestino(pacote, true);
        tabelaRoteamento->AprenderRoteamento(pacote.PegarCaminho());
        // Feito isso, basta iterar os pacotes verificando se existe uma rota para o mesmo
        VerificarNextPacotesEEnviar();
    }
}

void CamadaRede::VerificarNextPacotesEEnviar()
{
    auto tamanhoListaAguardandoRotas = PacotesAguardandoRota.size();
    for(int contador = 0; contador < tamanhoListaAguardandoRotas; contador++)
    {
        auto pacote = PacotesAguardandoRota.at(0);

        if(tabelaRoteamento->VerificarSeExisteRotaParaDestino(pacote.GetDestino()))
        {
            pacote.AdicionarNext(tabelaRoteamento->ObterNextPara(pacote.GetDestino()));
            camadaEnlace->AdicionarPacoteParaEnvio(pacote);
            PacotesAguardandoRota.erase(PacotesAguardandoRota.begin());
            tamanhoListaAguardandoRotas = PacotesAguardandoRota.size();
        }
        else
        {
            // Coloca na ultima posicao e remove da primeira, Nao altera o tamanho do vetor
            PacotesAguardandoRota.push_back(pacote);
            PacotesAguardandoRota.erase(PacotesAguardandoRota.begin());
        }
    }
}

void CamadaRede::ImprimeInformacoesOrigemDestino(Pacote pacote, bool isDestino)
{
    std::cout << "Pacote do tipo ";
    auto tipoPacote = pacote.GetTipoPacote();
    
    switch (tipoPacote)
    {
        case TipoPacote::RREQ:
            std::cout << "RREQ";
            break;
        case TipoPacote::RREP:
            std::cout << "RREP";
            break;
        case TipoPacote::DATA:
            std::cout << "DATA";
            break;
        default:
            break;
    } 

    std::cout << ", Originado Em : ";
    ImprimirMac(pacote.GetOrigem());
    std::cout << ", Com identificador : " << pacote.GetIdentificador() << ", Chegou a";
    if(isDestino)
        std::cout << "o Destino";
    ImprimirMac(hospedeiro->PegarEnderecoMac());
    std::cout << ".\n";
}
// void CamadaRede::ReceberPacoteCamadaEnlance(Pacote pacote)
// {
//     auto destinoPacote = pacote.GetDestino();
//     auto tipoPacote = pacote.GetTipoPacote();
//     auto macHospedeiro = hospedeiro->PegarEnderecoMac();
//     // Verifica se ta recebendo um pacote enviado por ele mesmo e return
//     if(pacote.GetOrigem() == hospedeiro->PegarEnderecoMac())
//         return;

//     // Pega as informacoes do pacote como origem e identificador para verificar se ja foi recebido posteriormente
//     std::pair<uint, std::vector<int>> DadosPacote = std::make_pair(pacote.GetIdentificador(), pacote.GetOrigem());
    
//     // Procura se ja recebeu um pacote com mesmo identificador e com mesma origem
//     auto itPacotesRecebidos = std::find(PacotesRecebidos.begin(), PacotesRecebidos.end(), DadosPacote);

//     // Caso tenha recebido ignora, caso contrario adiciona na lista de pacotes recebidos
//     if(itPacotesRecebidos != PacotesRecebidos.end())
//     {
//         std::cout << "Pacote : " << pacote.GetIdentificador() << " Originado de : ";
//         ImprimirMac(pacote.GetOrigem());
//         std::cout << " ||| Ja Passou Aqui : ";
//         ImprimirMac(macHospedeiro);
//         std::cout << "\n";
//         return;
//     }
//     else
//     {
//         PacotesRecebidos.push_back(DadosPacote);
//     }

//     std::cout << "Pacote Originado em : ";
//     ImprimirMac(pacote.GetOrigem());
//     std::cout << " Passou por mim : ";
//     ImprimirMac(hospedeiro->PegarEnderecoMac());
//     std::cout << "\n";
    
//     //std::cout << "vamo";
//     if(tipoPacote == TipoPacote::DATA && destinoPacote == macHospedeiro)
//     {
//         std::cout << "================================================================\n";
//         std::cout << "================================================================\n";
//         std::cout << "================================================================\n";
//         std::cout << "\n\n\nMensagem Recebida : ";
//         std::cout << "\n\nEnviada Por : ";
//         ImprimirMac(pacote.GetOrigem());
//         std::cout << "\n\nPara : ";
//         ImprimirMac(pacote.GetDestino());
//         std::cout << "\n\n";
//         // Pacote com dados, Pegar o dado e imprime
//         // RESPONDER PACOTE COM ACK
//         std::cout << pacote.GetDados(macHospedeiro) << "\n";
//         std::cout << "================================================================\n";
//         std::cout << "================================================================\n";
//         std::cout << "================================================================\n";
//         //std::cout << "Eu Sou o Destino";
//     }
//     else if(tipoPacote == TipoPacote::DATA && destinoPacote != macHospedeiro)
//     {
//         if(tabelaRoteamento->VerificarSeExisteRotaParaDestino(pacote.GetDestino()))
//         {
//             pacote.AdicionarNext(tabelaRoteamento->ObterNextPara(pacote.GetDestino()));
//             camadaEnlace->AdicionarPacoteParaEnvio(pacote);
//         }
//         else
//         {
//             PacotesAguardandoRota.push_back(pacote);
//             Pacote pacoteRREQ = Pacote(hospedeiro->PegarEnderecoMac(), pacote.GetDestino(), TipoPacote::RREQ, PacoteID);
//             pacoteRREQ.AdicionarCaminho(hospedeiro->PegarEnderecoMac());
//             PacoteID++;
//             camadaEnlace->AdicionarPacoteParaEnvio(pacoteRREQ);
//         }
        
//     }
//     else if(tipoPacote == TipoPacote::RREQ && macHospedeiro != destinoPacote)
//     {
//         // Pacote de Route Request porem não é destino
//         // Adicionar a assinatura ao pacote e reenvia o mesmo
//         std::cout << "Nao sou o destino : ";
//         ImprimirMac(pacote.GetDestino());
//         std::cout << " Reencaminhando Pacote para Vizinhos \n";
//         pacote.AdicionarCaminho(hospedeiro->PegarEnderecoMac());
//         camadaEnlace->AdicionarPacoteParaEnvio(pacote);
//     }
//     else if(tipoPacote == TipoPacote::RREQ && macHospedeiro == destinoPacote)
//     {
//         std::cout << "Eu Sou o Destino : ";
//         ImprimirMac(macHospedeiro);
//         std::cout << "\n";
//         // Pacote de Route Request porém é Destino
//         // Pega o caminho do pacote, E inverte o Mesmo
//         pacote.AdicionarCaminho(macHospedeiro);
//         auto pacoteCaminho = pacote.PegarCaminho();
//         std::cout << "Esse pacote Passou por : \n";
//         Pacote pacoteRespostaRREP = Pacote(macHospedeiro, pacote.GetOrigem(), TipoPacote::RREP, PacoteID);
//         PacoteID++;
//         for(auto it = pacoteCaminho.rbegin(); it != pacoteCaminho.rend(); ++it)
//         {      
//                 ImprimirMac(*it);
//                 pacoteRespostaRREP.AdicionarCaminho(*it);
//                 std::cout << "\n";
//         }
//         std::cout << "Ate Chegar Aqui\n\n";
//         // Ver Se Consegue alcancar o Ultimo que envio para mim, estará na posicao 1
//         auto possivelVizinho = pacoteRespostaRREP.PegarCaminho().at(1);
//         auto vizinhoAlcancavel = hospedeiro->AlcancoMac(possivelVizinho);

//         if(vizinhoAlcancavel)
//         {
//             tabelaRoteamento->AprenderRoteamento(pacoteRespostaRREP.PegarCaminho());
            
//             if(tabelaRoteamento->VerificarSeExisteRotaParaDestino(possivelVizinho))
//             {
//                 pacoteRespostaRREP.AdicionarNext(tabelaRoteamento->ObterNextPara(possivelVizinho));
//                 camadaEnlace->AdicionarPacoteParaEnvio(pacoteRespostaRREP);
//                 // Iterar sob os pacotes aguardando espera para ver se tem caminho e enviar
//             }
//         }else
//         {
//             PacotesAguardandoRota.push_back(pacoteRespostaRREP);
//             Pacote pacoteRREQ = Pacote(macHospedeiro, pacote.GetOrigem(), TipoPacote::RREQ, PacoteID);
//             PacoteID++;
//             pacoteRREQ.AdicionarCaminho(hospedeiro->PegarEnderecoMac());
//             camadaEnlace->AdicionarPacoteParaEnvio(pacoteRREQ);
//         }
//     }else if(tipoPacote == TipoPacote::RREP && macHospedeiro != pacote.GetDestino())
//     {
//         int posicaoOrigem = 0;
//         //std::cout << pacote.PegarCaminho().size();
//         auto caminho = pacote.PegarCaminho();
//         for(auto iterador = caminho.begin(); iterador != caminho.end(); ++iterador)
//         {
//             if(macHospedeiro == *iterador)
//                 break;
//             //ImprimirMac(*iterador);
//             posicaoOrigem++;
//         }
//         //std::cout << "\n\n" << caminho.size() << " " << posicaoOrigem << "\n\n";
//         if(posicaoOrigem >= caminho.size() - 1 /*|| caminho.size() == 0*/) return;
//         // Nao faço a minima ideia do que acontece aqui -- debugar
        
//         //if(posicaoOrigem >= caminho.size()) posicaoOrigem = -1;
        
//         //std::cout << std::dec << posicaoOrigem << std::endl;
//         //std::cout << pacote.PegarCaminho().size() << "\n\n";
//         auto possivelVizinho = pacote.PegarCaminho().at(posicaoOrigem + 1);
//         auto vizinhoAlcancavel = hospedeiro->AlcancoMac(possivelVizinho);
//         if(vizinhoAlcancavel)
//         {
//             //std::cout << "aqui";
//             tabelaRoteamento->AprenderRoteamento(caminho);
//             //std::cout << "aqui\n\n\n";
//             if(tabelaRoteamento->VerificarSeExisteRotaParaDestino(possivelVizinho))
//             {
//                 pacote.AdicionarNext(tabelaRoteamento->ObterNextPara(possivelVizinho));
//                 camadaEnlace->AdicionarPacoteParaEnvio(pacote);
//                 // Iterar sob os pacotes aguardando espera para ver se tem caminho e enviar
//             }
//         }else
//         {
//             PacotesAguardandoRota.push_back(pacote);
//             Pacote pacoteRREQ = Pacote(macHospedeiro, pacote.GetOrigem(), TipoPacote::RREQ, PacoteID);
//             pacoteRREQ.AdicionarCaminho(hospedeiro->PegarEnderecoMac());
//             PacoteID++;
//             camadaEnlace->AdicionarPacoteParaEnvio(pacoteRREQ);
//         }
//     }else if(tipoPacote == TipoPacote::RREP && macHospedeiro == pacote.GetDestino())
//     {
//         std::cout << "O Pacote de Route Reply Originado por : ";
//         ImprimirMac(pacote.GetOrigem());
//         std::cout << " Chegou Ao Destino : ";
//         ImprimirMac(macHospedeiro);
//         std::cout << "\n";
//         auto caminho = pacote.PegarCaminho();
//         tabelaRoteamento->AprenderRoteamento(caminho);
//     }
    
//     int numPacotesAguardandoRota = PacotesAguardandoRota.size();
//     for(int i = numPacotesAguardandoRota - 1; i >= 0; i--)
//     {
//         Pacote pacoteAguardandoRota = PacotesAguardandoRota.at(i);
//         //ImprimirMac(pacoteAguardandoRota.GetDestino());
//         if(tabelaRoteamento->VerificarSeExisteRotaParaDestino(pacoteAguardandoRota.GetDestino()))
//         {
//             //std::cout << numPacotesAguardandoRota << "\n";
//             pacoteAguardandoRota.AdicionarNext(tabelaRoteamento->ObterNextPara(pacoteAguardandoRota.GetDestino()));
//             camadaEnlace->AdicionarPacoteParaEnvio(pacoteAguardandoRota);
//             PacotesAguardandoRota.pop_back();
//             numPacotesAguardandoRota = PacotesAguardandoRota.size();
//         }
//     }
//     //std::cout << numPacotesAguardandoRota << "\n";
// }

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