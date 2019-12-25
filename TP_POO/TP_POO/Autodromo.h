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

	void carregaEnergia(int id, float n);
	void carregaEnergiaM();

	void avancaTempo();
	int comecarCorrida();
	void terminarCorrida();
	int paresPista() const;

	void reverCarros();
	void tudoGaragem();

	~Autodromo();
};
#endif
