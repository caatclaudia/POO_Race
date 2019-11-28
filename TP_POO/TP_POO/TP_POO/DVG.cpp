
#include "DVG.h"
#include "Carro.h"
#include "Piloto.h"

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
	for (auto ptr = carros.begin(); ptr != carros.end(); ++ptr) {
		if (*(ptr) == car)
			*carros.erase(ptr);
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
	for (auto ptr = pilotos.begin(); ptr != pilotos.end(); ++ptr) {
		if (*(ptr) == pil)
			*pilotos.erase(ptr);
	}
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

Piloto* DVG::pilotoNoCarro(char id) const
{
	for (auto ptr = pilotos.begin(); ptr != pilotos.end(); ptr++) {
		if ((*ptr)->getCarro()->getID() == id)
			return *ptr;
	}
	return nullptr;
}

string DVG::getAsString() const
{
	ostringstream oss;
	for (auto ptr = pilotos.begin(); ptr != pilotos.end(); ptr++)
		oss << (*ptr)->getAsString();
	for (auto ptr = carros.begin(); ptr != carros.end(); ptr++)
		oss << (*ptr)->getAsString();
	return oss.str();
}

DVG::~DVG()
{
	for (Carro* p : carros)
		delete p;
	for (Piloto* p : pilotos)
		delete p;
}
