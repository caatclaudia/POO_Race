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
class Pista;

class Piloto
{
	const string nome, tipo;	
	Carro *carro;
	int pontuacao, segundos;
	bool vivo, competicao;

public:
	Piloto(const string nome, const string t);
	string getNome()const;
	string getTipo()const;
	Carro* getCarro()const;
	void setCarro(Carro *ob);
	int getPontuacao()const;
	void acrescentaPontuacao(int n);
	int getSegundos() const;
	void setSegundos(int n=0);
	bool getVivo() const;
	void morreu();
	bool getCompeticao() const;
	void terminaCompeticao();
	void iniciaCompeticao();

	bool entraCarro(Carro* ob);
	bool saiCarro();

	void travarCarro();
	void acelararCarro();

	virtual int passouTempo(Pista *pista) =0;

	string getAsString()const;
	bool operator==(const Piloto& ob)const;

	virtual Piloto* duplica()const =0;

	virtual ~Piloto();
};

