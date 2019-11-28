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
	string nome,tipo;	//NAO PODE SER ALTERADO - static const ?
	Carro *carro;

public:
	Piloto(string nome, string t);
	string getNome()const;
	string getTipo()const;
	Carro* getCarro()const;
	void setCarro(Carro *ob);

	bool entraCarro(Carro* ob);
	bool saiCarro();
	/*Pode operar os mecanismos do carro que está a conduzir.
		Isto implica que o piloto tenha a capacidade de decidir o que vai fazer com o carro, e também
		a capacidade de receber ordens*/
	string getAsString()const;
	bool operator==(const Piloto& ob)const;

	~Piloto();
};

