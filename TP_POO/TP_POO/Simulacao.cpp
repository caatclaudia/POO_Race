#include "Simulacao.h"
#include "Menus.h"
#include "Autodromo.h"
#include "Carro.h"
#include "Pista.h"
#include "Piloto.h"
#include "Corrida.h"
#include <iostream>

Simulacao::Simulacao()
{
}

DVG& Simulacao::getControlo() 
{
	return controlo;
}

void Simulacao::addDVG(DVG& novo)
{
	lista.push_back(novo);
}
vector<Autodromo*> Simulacao::getAutodromos() const
{
	return autodromos;
}

vector<Corrida*> Simulacao::getAuxiliarCorrida() const
{
	return auxiliarCorrida;
}

Autodromo* Simulacao::getAutodromoN(int n) const
{
	if(n>=0 && n< (int)autodromos.size())
		return autodromos[n];
	return nullptr;
}

Corrida* Simulacao::getAuxiliarCorridaN(int n) const
{
	if (n >= 0 && n < (int)auxiliarCorrida.size())
		return auxiliarCorrida[n];
	return nullptr;
}

int Simulacao::getAutodromosSize() const
{
	return (int)autodromos.size();
}

int Simulacao::getAuxiliarCorridaSize() const
{
	return (int)auxiliarCorrida.size();
}

vector<Autodromo*> Simulacao::getCampeonato() 
{
	return campeonato;
}

Autodromo* Simulacao::getCampeonatoN(int n) const
{
	return campeonato[n];
}

int Simulacao::getCampeonatoSize() const
{
	return (int)campeonato.size();
}

void Simulacao::addCampeonato(Autodromo* novo)
{
	for (int i = 0; i < (int)campeonato.size(); i++)
		if (campeonato[i]->getNome() == novo->getNome())
			return ;
	campeonato.push_back(novo);
}

void Simulacao::addAutodromos(int N, double comp, string nome)
{
	bool igual = false;
	for (auto ptr = autodromos.begin(); ptr != autodromos.end(); ++ptr) {
		if ((*ptr)->getNome() == nome)
			igual = true;
	}
	if (igual) {
		nome = nome + to_string(NomeAutodromos);
		autodromos.push_back(new Autodromo(N, comp, nome));
	}
	else {
		autodromos.push_back(new Autodromo(N, comp, nome));
	}
}

void Simulacao::addAuxiliarCorrida(Corrida* novo) 
{
	auxiliarCorrida.push_back(novo);
}

bool Simulacao::eliminaAutodromos(string nome)
{
	for (auto ptr = autodromos.begin(); ptr != autodromos.end(); ptr++)
		if ((*ptr)->getNome() == nome) {
			delete (*ptr);
			ptr = autodromos.erase(ptr);
			return true;
		}
	return false;
}

void Simulacao::atualizaDVG()
{
	controlo.removeIrreparaveis();
	controlo.removeMortos();
}

Simulacao::~Simulacao()
{
	for (auto p : autodromos)
		delete p;
	for (auto p : auxiliarCorrida)
		delete p;
}
