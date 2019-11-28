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
	const string nome,tipo;	
	Carro *carro;
	int pontuacao;

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
	/*Pode operar os mecanismos do carro que está a conduzir.
		Isto implica que o piloto tenha a capacidade de decidir o que vai fazer com o carro, e também
		a capacidade de receber ordens*/
	void travarCarro();
	void acelararCarro();


	string getAsString()const;
	bool operator==(const Piloto& ob)const;

	~Piloto();
};

