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
	vector<DVG> lista;
	vector<Autodromo*> autodromos;
	vector<Corrida*> auxiliarCorrida;
	vector<Autodromo*> campeonato;	
	vector<string> listaMensagens;

public:
	static int NomeAutodromos;

	Simulacao();

	DVG& getControlo();
	void addDVG(DVG& novo);
	bool deldgv(string nome);
	bool loaddgv(string nome);

	vector<Autodromo*> getAutodromos() const;
	vector<Corrida*> getAuxiliarCorrida() const;
	Autodromo* getAutodromoN(int n) const;
	Corrida* getAuxiliarCorridaN(int n) const;
	int getAutodromosSize() const;
	int getAuxiliarCorridaSize() const;

	vector<Autodromo*> getCampeonato() ;
	Autodromo* getCampeonatoN(int n) const;
	int getCampeonatoSize() const;
	void addCampeonato(Autodromo *novo);


	void addAutodromos(int N, double comp, string nome);
	void addAuxiliarCorrida(Corrida* novo) ;
	bool eliminaAutodromos(string nome);

	void atualizaDVG();

	void addMensagem(string s);
	void addMensagemAcidente(vector<Corrida*> c);
	vector<string> getListaMensagens()const;
	int nMensagens();

	~Simulacao();
};
