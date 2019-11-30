#pragma once
class Autodromo;
class Pista;
class Piloto;
class Carro;
class Garagem;
class Corrida;
#include "DVG.h"
#include <vector>
#include <string>
using namespace std;

#define LINHAS_BASE 29
#define COLUNAS_BASE 118

class Menus
{
	DVG controlo;
	vector<Autodromo*> autodromos;
	vector<Corrida*> auxiliarCorrida;
public:
	static int NomeAutodromos;
	Menus();

	void acrescentaAutodromo(int N, double comp, string nome);

	void base()const;
	void limpaPista()const;

	void carregaP(string nome);
	void carregaC(string nome);
	void carregaA(string nome);

	int modo2(Autodromo* autodromo);
	int modo1(string comando);

	void movimentoCarros(Autodromo* autodromo, int seg);

	void associaCarros(int num);

	virtual ~Menus();
};

