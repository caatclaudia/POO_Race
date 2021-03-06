#include "Autodromo.h"
#include "Pista.h"
#include "Piloto.h"
#include "Carro.h"
#include "Garagem.h"
#include "Corrida.h"
#include "Consola.h"


Autodromo::Autodromo(int N, double comprimento,  const string n):nome(n) 
{
	
	p = new Pista(N, comprimento);
	gar = new Garagem();
}

string Autodromo::getNome() const
{
	return nome;
}

Pista* Autodromo::getPista()const
{
	return p;
}

string Autodromo::getAsString() const
{
	ostringstream oss;
	oss << "Autodromo " << nome << p->getAsString();
	return oss.str();
}

Garagem* Autodromo::getGaragem() const
{
	return gar;
}

void Autodromo::carregaEnergia(int id, float n)
{
	for (int i = 0; i < (int)p->getCorridas().size(); i++)
		if(p->getCorridaN(i)->getCarro()->getID() == id)
			p->getCorridaN(i)->getCarro()->carregaEnergia(n);
}

void Autodromo::carregaEnergiaM()
{
	for (int i = 0; i < (int)p->getCorridas().size(); i++)
		p->getCorridaN(i)->getCarro()->carregaEnergiaM();
}

void Autodromo::avancaTempo()
{
	p->avancaTempo();
	p->carregaGrelha();
}

int Autodromo::comecarCorrida()
{
	return p->comecarCorrida();
}

void Autodromo::terminarCorrida()
{
	p->terminarCorrida();
}

int Autodromo::paresPista() const
{
	return p->atualizaPares();
}

void Autodromo::reverCarros()
{
	vector<Carro*> carrosARemover;
	for (auto ptr = p->getCorridas().begin(); ptr != p->getCorridas().end(); ptr++) {
		if ((*ptr)->getCarro()->getAcidente() != CARRO_BOMESTADO || (*ptr)->getCarro()->getEmergencia() == EMERGENCIA_ON) {
			gar->adicionaCarro((*ptr)->getCarro());
			carrosARemover.push_back((*ptr)->getCarro());
		}
	}
	for (auto pt = carrosARemover.begin(); pt!=carrosARemover.end(); pt++)
		p->removerCarro((*pt)->getID());
	carrosARemover.clear();
}

void Autodromo::tudoGaragem()
{
	for (auto ptr = p->getCorridas().begin(); ptr != p->getCorridas().end(); ptr++) {
		gar->adicionaCarro((*ptr)->getCarro());
	}
	p->limpaPista();
}

void Autodromo::limpaGaragem()
{
	gar->limpaCarros();
}

Autodromo::~Autodromo()
{
	for(auto ptr : p->getCorridas())
		ptr->getCarro()->acidenteDanoIrreparavel(ptr->getParticipante());
	for (auto ptr : gar->getCarros())
		ptr->acidenteDanoIrreparavel(nullptr);
	delete p;
	delete gar;
}
