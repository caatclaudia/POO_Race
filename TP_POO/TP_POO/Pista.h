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
	char getGrelhaXY(int x, int y) const;

	void removerPar(Corrida* c);
	void atualizaPontuacao();
	int comecarCorrida();
	void terminarCorrida(Garagem* g);
	void terminarCorrida();
	void avancaTempo(int sec=1);
	void removerCarro(char c);
	
	void verificaLugar();

	bool haCampeao()const;

	int atualizaPares();

	int getComecou()const;
	void setComecou(int c);

	string getAsString()const;

	void carregaGrelha();
	vector< vector< char> > getGrelha()const;

	void limpaPista();

	~Pista();
};
#endif
