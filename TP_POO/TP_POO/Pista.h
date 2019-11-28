#pragma once
#ifndef PISTA_H
#define PISTA_H
#define JA_COMECOU 1
#define NAO_COMECOU 0
#define JA_TERMINOU -1

#define COLUNAS 70

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
	const int nMax;
	const double comprimento;
	vector<Corrida*> corridas;
	int comecou;

	vector< vector< char> > grelha;
public:
	Pista(const int nCar, const double comp);
	int getNMax()const;
	double getComprimento()const;
	vector<Corrida*>& getCorridas();
	Corrida* getCorridaN(int num);
	void adicionaCorrida(Corrida* novo);
	int nParticipantes()const;

	bool adicionarCarro(Carro* c);
	void parPilotoCarro(Piloto* p, Carro* c);
	void atualizaPontuacao();
	void comecarCorrida();
	void terminarCorrida(Garagem* g);
	void avancaTempo(int sec=1);
	void removerCarroemEmergencia(Garagem* g);
	
	void verificaLugar();

	bool haCampeao()const;

	int getComecou()const;
	void setComecou(int c);

	string getAsString()const;

	void listaCarros()const;

	void carregaGrelha();
	vector< vector< char> > GetGrelha()const;
	void mostraGrelha()const;

	~Pista();
};
#endif
