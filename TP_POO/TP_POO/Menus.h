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
#include "Simulacao.h"
using namespace std;

#define LINHAS_BASE 29
#define COLUNAS_BASE 118

class Menus
{
public:
	static int NomeAutodromos;

	Menus();

	void base()const;
	void limpaPista()const;

	void carregaP(DVG& controlo, string nome);
	void carregaC(DVG& controlo, string nome);
	void carregaA(Simulacao* simulacao, string nome);

	int modo2(vector<Autodromo*> campeonato, DVG *controlo);
	int modo1(Simulacao *simulacao, string comando);

	void movimentoCarros(Autodromo* autodromo, int seg);

	void associaCarros(Simulacao* simulacao, int num);

	~Menus();
};

