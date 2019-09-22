#include "Hospedeiro.hpp"


Hospedeiro::Hospedeiro(std::vector<int> *EnderecoMac, uint CoordenadaX, uint CoordenadaY)
{
    this->CoordenadaX = CoordenadaX;
    this->CoordenadaY = CoordenadaY;
    this->EnderecoMac = EnderecoMac;
}

Hospedeiro::~Hospedeiro()
{

}