#pragma once
#ifndef PISTA_H
#define PISTA_H
#define JA_COMECOU true
#define NAO_COMECOU false

class Corrida;
class Autodromos;
class Carro;
class Piloto;
class Garagem;
#include <vector>
#include <string>
using namespace std;

class Pista
{
	int nMax;
	double comprimento;
	//posicao e lugar dos carros ??
	vector<Corrida*> corridas;
	bool comecou;
	
public:
	Pista(int nCar, double comp);
	int getNMax()const;
	double getComprimento()const;
	vector<Corrida*>& getCorridas();
	int nParticipantes()const;

	void adicionarCarro(Carro* c);
	void parPilotoCarro(Piloto* p, Carro* c);
	void comecarCorrida();
	void terminarCorrida(Garagem* g);
	void avancaTempo(int sec);
	void removerCarroemEmergencia(Garagem* g);
	void verificaLugar();

	bool getComecou()const;
	void setComecou(bool c);

	string getAsString()const;

	~Pista();
};
#endif
