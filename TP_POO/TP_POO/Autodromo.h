#pragma once
#ifndef AUTODROMO_H
#define AUTODROMO_H

class Pista;
class Piloto;
class Carro;
class Garagem;
class Corrida;
#include <string>
using namespace std;

class Autodromo
{
	const string nome;		
	Pista* p;
	Garagem* gar;

public:

	Autodromo(int N, double comprimento, const string n);

	string getNome()const;
	Pista* getPista()const;
	string getAsString()const;
	Garagem* getGaragem() const;
	void obterInfo()const;
	//void carregaCarros();

	//bool acrescentaCarroPista(Carro *carro);
	//bool acrescentaCarroGaragem(Carro *carro);
	void getAsStringPontPilotos();

	void reverCarros();

	void mostraGaragem() const;

	void mostraGrelha() const;

	~Autodromo();
};
#endif
