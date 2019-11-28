#include "Corrida.h"
#include "Autodromo.h"
#include "Carro.h"
#include "Corrida.h"
#include "Piloto.h"
#include "Pista.h"



Corrida::Corrida(Carro* part)
{
	posicao = 0;
	lugar = NULL;
	carro = part;
	participante = nullptr;
}

int Corrida::getPosicao()const {
	return posicao;
}
void Corrida::setPosicao(int pos) {
	posicao=pos;
}

void Corrida::avancaPosicao(int pos)
{
	posicao += pos;
}

int Corrida::getLugar()const {
	return lugar;
}
void Corrida::setLugar(int lug) {
	lugar = lug;
}

Piloto* Corrida::getParticipante()const {
	return participante;
}
void Corrida::setParticipante(Piloto* pil) {
	participante = pil;
	pil->entraCarro(carro);
}

Carro* Corrida::getCarro()const {
	return carro;
}
void Corrida::setCarro(Carro* car) {
	carro = car;
}

Corrida::~Corrida()
{
}
