#include "Pacote.hpp"

Pacote::Pacote(std::vector<int> origem, std::vector<int> destino, std::string dados, TipoPacote tipoPacote)
{
    Origem = origem;
    Destino = destino;
    Dados = dados;
    this->tipoPacote = tipoPacote;
    Identificador = 0;
}

Pacote::Pacote(std::vector<int> origem, std::vector<int> destino, TipoPacote tipoPacote, uint Identificador)
{
    if(tipoPacote == TipoPacote::RREP || tipoPacote == TipoPacote::RREQ)
    {
        this->tipoPacote = tipoPacote;
        Origem = origem;
        Destino = destino;
        this->Identificador = Identificador;
    }

}

void Pacote::AdicionarCaminho(std::vector<int> HospedeiroAtual)
{
    if(tipoPacote == TipoPacote::RREQ  || tipoPacote == TipoPacote::RREP)
        if(HospedeiroAtual.size() == 6)
            HospedeirosPeloQualPassou.push_back(HospedeiroAtual);
}

void Pacote::AdicionarNext(std::vector<int> next)
{   
    if(tipoPacote == TipoPacote::DATA || tipoPacote == TipoPacote::RREP)
        Next = next;
}

uint Pacote::AdicionarUID(uint UID)
{
    if(Identificador == 0 && UID > 0)
        Identificador = UID;
    
    return Identificador;
}

std::vector<std::vector<int>> Pacote::PegarCaminho()
{
   if(tipoPacote == TipoPacote::RREQ || tipoPacote == TipoPacote::RREP)
   {
       return HospedeirosPeloQualPassou;
   }

   std::vector<std::vector<int>> v;
   return v;
}

std::vector<int> Pacote::GetDestino()
{
    return Destino;
}

std::vector<int> Pacote::GetOrigem()
{
    return Origem;
}

std::vector<int> Pacote::GetNext()
{
    return Next;
}

TipoPacote Pacote::GetTipoPacote()
{
    return this->tipoPacote;
}

std::string Pacote::GetDados(std::vector<int> destino)
{
    return destino == Destino ? Dados : "";
}

uint Pacote::GetIdentificador()
{
    return Identificador;
}

Pacote::~Pacote()
{

};