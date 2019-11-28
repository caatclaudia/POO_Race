
#include "DVG.h"
#include "Carro.h"
#include "Piloto.h"
#include "Consola.h"

DVG::DVG()
{

}

vector<Carro*> & DVG::getCarro()
{
	return carros;
}

int DVG::getNCarros() const
{
	return carros.size();
}

void DVG::novoCarro(string marca, double cInicial, double cMaxima, int vMaxima, string modelo)
{
	carros.push_back(new Carro(marca, cInicial, cMaxima, vMaxima, modelo));
}

void DVG::removeCarro(Carro* car)
{
	for (auto ptr = carros.begin(); ptr != carros.end(); ) {
		if (*(ptr) == car)
			ptr = carros.erase(ptr);
		else
			ptr++;
	}
}

vector<Piloto*> & DVG::getPiloto()
{
	return pilotos;
}

int DVG::getNPilotos() const
{
	return pilotos.size();
}

void DVG::novoPiloto(string n,string t) 
{
	bool igual=false;
	for (auto ptr = pilotos.begin(); ptr != pilotos.end(); ++ptr) {                
		if ((*ptr)->getNome() == n)
			igual = true;
	}
	if (igual) {
		n = n + to_string(Nome);
		pilotos.push_back(new Piloto(n,t));
	}
	else {
		pilotos.push_back(new Piloto (n,t));
	}
}

void DVG::removePiloto(Piloto* pil)
{
	for (auto ptr = pilotos.begin(); ptr != pilotos.end(); ) {
		if (*(ptr) == pil)
			ptr = pilotos.erase(ptr);
		else
			ptr++;
	}
}

int DVG::getNCarrosDisponiveis()
{
	int n = 0;
	for (auto ptr = carros.begin(); ptr != carros.end(); ++ptr) {
		if ((*ptr)->getAcidente() == 0 || (*ptr)->getCondutor() == false)
			n++;
	}
	return n;
}

int DVG::getNPilotosDisponiveis()
{
	int n = 0;
	for (auto ptr = pilotos.begin(); ptr != pilotos.end(); ++ptr) {
		if ((*ptr)->getCarro() == false)
			n++;
	}
	return n;
}

Carro* DVG::procuraCarro(char id) const
{
	for (auto ptr = carros.begin(); ptr != carros.end(); ++ptr) {
		if ((*ptr)->getID() == id)
			return *ptr;
	}
	return nullptr;
}

Piloto* DVG::procuraPiloto(string nome) const
{
	for (auto ptr = pilotos.begin(); ptr != pilotos.end(); ++ptr) {
		if ((*ptr)->getNome() == nome)
			return *ptr;
	}
	return nullptr;
}

Carro* DVG::procuraCarroN(int n) const
{
	return carros[n];
}

Piloto* DVG::procuraPilotoN(int n) const
{
	return pilotos[n];
}

Piloto* DVG::pilotoNoCarro(char id) const
{
	for (auto ptr = pilotos.begin(); ptr != pilotos.end(); ptr++) {
		if ((*ptr)->getCarro()->getID() == id)
			return *ptr;
	}
	return nullptr;
}

int DVG::getAsString() const
{
	int i = 1;
	for (auto ptr = pilotos.begin(); ptr != pilotos.end(); ptr++) {
		Consola::gotoxy(76, i);
		cout << (*ptr)->getAsString();
		i++;
	}
	for (auto ptr = carros.begin(); ptr != carros.end(); ptr++) {
		Consola::gotoxy(76, i);
		cout << (*ptr)->getAsString();
		i++;
	}
	return i;
}

void DVG::getAsStringPontPilotos() const
{
	int i = 1, max, indiceMax, l;
	vector<int> indiceUsado;
	
	for (int j = 0; (int)indiceUsado.size() != (int)pilotos.size(); ) {
		max = 0;
		for (l = 0; l < (int)pilotos.size(); l++) {
			bool EXISTE = false;
			if (pilotos[l]->getPontuacao() >= max) {
				for (int k = 0; k < (int)indiceUsado.size(); k++) {
					if (l == indiceUsado[k])
						EXISTE = true;
				}
				if (!EXISTE) {
					indiceMax = l;
					max = pilotos[l]->getPontuacao();
				}
			}
		}
		indiceUsado.push_back(indiceMax);
		if (pilotos[indiceMax]->getPontuacao() != 0) {
			Consola::gotoxy(76, i++);
			cout << (int)indiceUsado.size() << ": Piloto " << pilotos[indiceMax]->getNome() << " com " << pilotos[indiceMax]->getPontuacao() << " pontos!";
		}
		
	}
}

DVG::~DVG()
{
	for (Carro* p : carros)
		delete p;
	for (Piloto* p : pilotos)
		delete p;
}
