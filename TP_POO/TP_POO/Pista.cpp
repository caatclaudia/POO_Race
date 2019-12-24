#include "Pista.h"
#include "Autodromo.h"
#include "Corrida.h"
#include "Carro.h"
#include "Piloto.h"
#include "Garagem.h"
#include "Consola.h"
#include <sstream>
#include <iostream>

Pista::Pista(const int nCar, const double comp):nMax (nCar),comprimento(comp)
{
	comecou = NAO_COMECOU;
	for (int i = 0; i < nMax * 2; i++) {
		vector<char> temp;
		for (int j = 0; j < COLUNAS; j++)
			temp.push_back(' ');
		grelha.push_back(temp);
	}
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

Corrida* Pista::getCorridaN(int num)
{
	return corridas[num];
}

void Pista::adicionaCorrida(Corrida* novo)
{
	corridas.push_back(novo);
}

int Pista::nParticipantes() const
{
	return corridas.size();
}

char Pista::getGrelhaXY(int x, int y) const
{
	return grelha[x][y];
}

//bool Pista::adicionarCarro(Carro* c)
//{
//	if (((int)(corridas.size())) <= nMax) {
//		corridas.push_back(new Corrida(c));
//		return true;
//	}
//	else {
//		Consola::gotoxy(76, 2);
//		cout << "Numero maximo de carros atingido!";
//	}
//	return false;
//}
//
//void Pista::parPilotoCarro(Piloto* p, Carro* c)
//{
//	if (comecou == NAO_COMECOU) {
//		for (auto ptr = corridas.begin(); ptr != corridas.end(); ptr++) {
//			if ((*ptr)->getCarro() == c)
//				if ((*ptr)->getParticipante() == nullptr)
//					(*ptr)->setParticipante(p);
//				else {
//					(*ptr)->getParticipante()->saiCarro();
//					(*ptr)->setParticipante(p);
//				}
//		}
//	}
//}

void Pista::removerPar(Corrida *c)
{
	for (auto ptr = corridas.begin(); ptr != corridas.end(); ) {
		if (*(ptr) == c)
			ptr = corridas.erase(ptr);
		else
			ptr++;
	}
}

void Pista::atualizaPontuacao()
{
	verificaLugar();
	if (comecou == JA_TERMINOU) {
		for (int i = 0; i < (int)corridas.size(); i++) {
			if (corridas[i]->continuaDisponivel()) {
				if (corridas[i]->getLugar() == 1)
					corridas[i]->getParticipante()->acrescentaPontuacao(10);
				else if (corridas[i]->getLugar() == 2)
					corridas[i]->getParticipante()->acrescentaPontuacao(5);
				else if (corridas[i]->getLugar() == 3)
					corridas[i]->getParticipante()->acrescentaPontuacao(2);
			}
		}
	}
}

int Pista::comecarCorrida()
{
	int n=0;
	if (corridas.size() >= 2) {
		for (auto ptr = corridas.begin(); ptr != corridas.end(); ptr++) {
			if ((*ptr)->getParticipante() != nullptr)
				n++;
		}
		if (n == corridas.size()) {
			comecou = JA_COMECOU;
			for (auto ptr = corridas.begin(); ptr != corridas.end(); ptr++) {
				(*ptr)->getParticipante()->iniciaCompeticao();
				(*ptr)->getParticipante()->setSegundos();
				(*ptr)->setPosicao(0);
				(*ptr)->getParticipante()->passouTempo(1, this);
				(*ptr)->setTravar(false);
			}
		}
		else	//Existem carros vazios
			return 0;
	}
	else	//Nao tem carros suficientes
		return -1;
	return 1;
}


void Pista::terminarCorrida(Garagem* g)
{
	if (comecou == JA_COMECOU) {
		comecou = JA_TERMINOU;
		atualizaPontuacao();
		for (auto ptr = corridas.begin(); ptr != corridas.end(); ptr++) {
			(*ptr)->getParticipante()->saiCarro();
			g->adicionaCarro((*ptr)->getCarro());
			(*ptr)->setPosicao(0);
			(*ptr)->setTravar(true);
		}
	}
}

void Pista::terminarCorrida()
{
	if (comecou == JA_COMECOU) {
		comecou = JA_TERMINOU;
		atualizaPontuacao();
		for (auto ptr = corridas.begin(); ptr != corridas.end(); ptr++) {
			(*ptr)->setPosicao(0);
			(*ptr)->setTravar(true);
		}
	}
}

void Pista::avancaTempo(int sec)
{
	if (comecou == JA_COMECOU) {
		for (auto ptr = corridas.begin(); ptr != corridas.end(); ptr++) {
			if (!(*ptr)->getTravar())
				(*ptr)->avancaPosicao((*ptr)->getParticipante()->passouTempo(sec, this));
			else if ((*ptr)->getCarro()->getVelocidade() > 0)
				(*ptr)->getParticipante()->travarCarro();
			if ((*ptr)->getPosicao() >= comprimento)
				(*ptr)->setPosicao((int)comprimento);
		}
		if (haCampeao())
			terminarCorrida();
		verificaLugar();
	}
}

void Pista::removerCarro(char c)
{
	for (auto ptr = corridas.begin(); ptr != corridas.end(); ) {
		if ((*ptr)->getCarro()->getID() == c) {
			(*ptr)->getParticipante()->saiCarro();
			ptr = corridas.erase(ptr);
		}
		else
			ptr++;
	}
	verificaLugar();
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

bool Pista::haCampeao() const
{
	for (auto ptr = corridas.begin(); ptr != corridas.end(); ptr++) {
		if ((*ptr)->getPosicao() >= comprimento)
			return true;
	}
	return false;
}

int Pista::atualizaPares()
{
	int num = 0;
	for (int i = 0; i < (int)corridas.size(); i++)
		if (corridas[i]->continuaDisponivel())
			num++;
	return num;
}

int Pista::getComecou()const 
{
	return comecou;
}

void Pista::setComecou(int c) 
{
	comecou = c;
}

string Pista::getAsString() const
{
	ostringstream oss;
	oss << "(" << comprimento<<"m / "<< nMax <<" carros)";
	return oss.str();
}

//void Pista::listaCarros() const
//{
//	int x = 1;
//	for (int i = 0; i < (int)corridas.size(); i++) {
//		Consola::gotoxy(76, x++);
//		cout << corridas[i]->getParticipante()->getAsString();
//	}
//}

void Pista::carregaGrelha() 
{
	auto ptr = corridas.begin();
	for (int i = 0; i <= nMax * 2 && ptr != corridas.end(); i++) {
		int pos = (COLUNAS * (*ptr)->getPosicao()) / (int)comprimento;
		for (int j = 0; j < COLUNAS; j++) {
			if (i % 2 == 0) {
				if (pos == j) {
					if ((*ptr)->getCarro()->getCondutor())
						grelha[i][j] = toupper((*ptr)->getCarro()->getID());	//MAIUSCULA
					else
						grelha[i][j] = tolower((*ptr)->getCarro()->getID());	//MINUSCULA
				}
				else
					grelha[i][j] = ' ';
				if ((*ptr)->getPosicao() > comprimento)
					grelha[i][COLUNAS - 1] = toupper((*ptr)->getCarro()->getID());
			}
			else {
				grelha[i][j] = '-';
			}
		}
		if (i % 2 == 0)
			ptr++;
	}
}

vector< vector< char> > Pista::getGrelha()const
{
	return grelha;
}

Pista::~Pista()
{
	corridas.clear();
}
