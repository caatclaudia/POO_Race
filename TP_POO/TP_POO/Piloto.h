#pragma once

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>

using namespace std;

#define DENTRO_CARRO 1
#define FORA_CARRO 0

class Carro;

class Piloto
{
	const string nome, tipo;	
	Carro *carro;
	int pontuacao, comeca;

public:
	Piloto(const string nome, const string t);
	string getNome()const;
	string getTipo()const;
	Carro* getCarro()const;
	void setCarro(Carro *ob);
	int getPontuacao()const;
	void acrescentaPontuacao(int n);

	bool entraCarro(Carro* ob);
	bool saiCarro();

	void travarCarro();
	void acelararCarro();

	virtual int passouTempo(int s);

	string getAsString()const;
	bool operator==(const Piloto& ob)const;

	virtual ~Piloto();
};

