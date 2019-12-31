#include "Simulacao.h"
#include "Menus.h"
#include "Autodromo.h"
#include "Carro.h"
#include "Pista.h"
#include "Piloto.h"
#include "Corrida.h"
#include "Consola.h"
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

bool Simulacao::deldgv(string nome)
{
	for (int i = 0; i < (int)lista.size(); i++)
		if (lista[i].getNomeDVG() == nome) {
			lista.erase(lista.begin() + i);
			return true;
		}
	return false;
}

bool Simulacao::loaddgv(string nome)
{
	for (int i = 0; i < (int)lista.size(); i++)
		if (lista[i].getNomeDVG() == nome) {
			addDVG(controlo);
			controlo = lista[i];
			return true;
		}
	return false;
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

void Simulacao::eliminaCampeonato()
{
	/*for (auto ptr = campeonato.begin(); ptr != campeonato.end(); ptr++){
		delete (*ptr);
	}*/
	campeonato.clear();

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
		NomeAutodromos++;
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

void Simulacao::atualizaAuxiliarCorrida()
{
	for (auto ptr = auxiliarCorrida.begin(); ptr != auxiliarCorrida.end(); ) {
		if (!(*ptr)->continuaDisponivel())
			ptr = auxiliarCorrida.erase(ptr);
		else
			ptr++;
	}
}

void Simulacao::getAsStringPilotos() {
	int i = 1;
	if (controlo.getNPilotos()==0) {
		Consola::gotoxy(76, i);
		cout << "Nao existe pilotos!";
		return;
	}
	for (auto ptr = controlo.getPiloto().begin(); ptr != controlo.getPiloto().end(); ptr++) {
		Consola::gotoxy(76, i);
		cout << (*ptr)->getAsString();
		if (i == 18) {
			Consola::getch();
			for (i = 76; i < COLUNAS_BASE; i++) {
				for (int j = 1; j < 19; j++) {
					Consola::gotoxy(i, j);
					cout << " ";
				}
			}
			i = 0;	
		}
		i++;
	}
}

void Simulacao::getAsStringCarros() {
	int i = 1;
	if (controlo.getNCarros()==0) {
		Consola::gotoxy(76, i);
		cout << "Nao existe carros!";
		return;
	}
	for (auto ptr = controlo.getCarro().begin(); ptr != controlo.getCarro().end(); ptr++) {
		Consola::gotoxy(76, i);
		cout << (*ptr)->getAsString();
		if (i == 18) {
			Consola::getch();
			for (i = 76; i < COLUNAS_BASE; i++) {
				for (int j = 1; j < 19; j++) {
					Consola::gotoxy(i, j);
					cout << " ";
				}
			}
			i = 0;
		}
		i++;
	}
}

void Simulacao::getAsStringAutodromos()
{
	int i = 1;
	if (autodromos.empty()) {
		Consola::gotoxy(76, i);
		cout << "Nao existe autodromos!";
	}
	else {
		for (int x = 0; x < autodromos.size(); x++) {
			Consola::gotoxy(76, i);
			cout << autodromos[x]->getAsString();
			if (i == 18) {
				Consola::getch();
				for (i = 76; i < COLUNAS_BASE; i++) {
					for (int j = 1; j < 19; j++) {
						Consola::gotoxy(i, j);
						cout << " ";
					}
				}
				i = 0;
			}
			i++;
		}
	}
}

Simulacao::~Simulacao()     
{
	campeonato.clear();
	lista.clear();
	for (auto p : autodromos)
		delete p;
	for (auto p : auxiliarCorrida)
		delete p;

}