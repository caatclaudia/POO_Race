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

class Simulacao
{
	DVG controlo;
	vector<Autodromo*> autodromos;
	vector<Corrida*> auxiliarCorrida;
public:
	static int NomeAutodromos;

	Simulacao();

	DVG& getControlo() ;
	vector<Autodromo*> getAutodromos() const;
	vector<Corrida*> getAuxiliarCorrida() const;
	Autodromo* getAutodromoN(int n) const;
	Corrida* getAuxiliarCorridaN(int n) const;
	int getAutodromosSize() const;

	void addAutodromos(int N, double comp, string nome);
	void addAuxiliarCorrida(Corrida* novo) ;

	~Simulacao();
};

