#include "Pista.h"
#include "Autodromo.h"
#include "Corrida.h"
#include "Carro.h"
#include "Piloto.h"
#include "Garagem.h"
#include <sstream>
#include <iostream>

Pista::Pista(int nCar, double comp)
{
	nMax = nCar;
	comprimento = comp;
	comecou = NAO_COMECOU;
}

int Pista::getNMax()const
{
	return nMax;
}

double Pista::getComprimento()const
{
	return comprimento;
}

vector<Corrida*>& Pista::getCorridas()
{
	return corridas;
}

int Pista::nParticipantes() const
{
	return corridas.size();
}

void Pista::adicionarCarro(Carro* c)
{
	if (corridas.size() <= nMax)
		corridas.push_back(new Corrida(c));
	else
		cout << "Numero maximo de carros atingido!";
}

void Pista::parPilotoCarro(Piloto* p, Carro* c)
{
	if (comecou == NAO_COMECOU) {
		for (auto ptr = corridas.begin(); ptr != corridas.end(); ptr++) {
			if ((*ptr)->getCarro() == c)
				if ((*ptr)->getParticipante() == nullptr)
					(*ptr)->setParticipante(p);
				else {
					(*ptr)->getParticipante()->saiCarro();
					(*ptr)->setParticipante(p);
				}

		}
	}
	
}

void Pista::comecarCorrida()
{
	int n=0;
	if (corridas.size() >= 2) {
		for (auto ptr = corridas.begin(); ptr != corridas.end(); ptr++) {
			if ((*ptr)->getParticipante() != nullptr)
				n++;
		}
		if (n == corridas.size())
			comecou = JA_COMECOU;
		else
			cout << "Existem carros vazios" << endl;
	}
	else
		cout << "Nao tem carros suficientes" << endl;
}


void Pista::terminarCorrida(Garagem* g)
{
	if (comecou == JA_COMECOU) {
		for (auto ptr = corridas.begin(); ptr != corridas.end(); ptr++) {
			(*ptr)->getParticipante()->saiCarro();
			g->adicionaCarro((*ptr)->getCarro());
			delete (*ptr);
		}
	}
	comecou = NAO_COMECOU;
	
}

void Pista::avancaTempo(int sec)
{
	if (comecou == JA_COMECOU) {
		for (auto ptr = corridas.begin(); ptr != corridas.end(); ptr++) {
			(*ptr)->avancaPosicao((*ptr)->getCarro()->passouTempo(sec));
			
		}
		verificaLugar();
	}
}

void Pista::removerCarroemEmergencia(Garagem* g)
{
	for (auto ptr = corridas.begin(); ptr != corridas.end(); ptr++) {
		if ((*ptr)->getCarro()->getEmergencia() == EMERGENCIA_ON) {
			(*ptr)->getParticipante()->saiCarro();
			g->adicionaCarro((*ptr)->getCarro());
			delete (*ptr);
		}

	}
}

void Pista::verificaLugar()
{
	int n = 1;
	for (auto ptr = corridas.begin(); ptr != corridas.end(); ptr++) {
		n = 1;
		for (auto pt = corridas.begin() + 1; pt != corridas.end(); pt++) {
			if ((*ptr)->getPosicao() < (*pt)->getPosicao())
				n++;
		}
		(*ptr)->setLugar(n);
	}
}
bool Pista::getComecou()const {
	return comecou;
}
void Pista::setComecou(bool c) {
	comecou = c;
}

string Pista::getAsString() const
{
	ostringstream oss;
	oss << "Pista com " << comprimento<<" metros de comprimento e "<< nMax <<" maximo de carros" << endl;
	return oss.str();
}

Pista::~Pista()
{
}
