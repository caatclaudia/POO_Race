#include "Simulacao.h"
#include "Menus.h"
#include "Autodromo.h"
#include "Carro.h"
#include "Pista.h"
#include "Piloto.h"
#include "Corrida.h"

Simulacao::Simulacao()
{
}

DVG& Simulacao::getControlo() 
{
	return controlo;
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
			ptr = autodromos.erase(ptr);
			return true;
		}
	return false;
}

Simulacao::~Simulacao()
{
	for (auto p : autodromos)
		delete p;
	for (auto p : auxiliarCorrida)
		delete p;
}
