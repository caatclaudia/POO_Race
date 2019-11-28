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
	string nome;		//UNICO //static const???
	Pista* p;
	Garagem* gar;

public:

	Autodromo(int N, double comprimento, string nome);

	string getNome()const;
	Pista* getPista()const;
	string getAsString()const;
	string obterInfo()const;
	~Autodromo();
};
#endif
